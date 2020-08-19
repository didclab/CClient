/*
 * transfer_service_impl_tests.cpp
 * Andrew Mikalsen
 * 7/23/20
 */

#include <string>
#include <unordered_map>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <simdjson/simdjson.h>

#include <onedatashare/ods_error.h>

#include <ods_rest_api.h>
#include <transfer_service_impl.h>
#include <util.h>

#include "mocks.h"

namespace {

namespace Ods = Onedatashare;

using ::testing::Return;
using ::testing::Throw;

using Onedatashare_mocks::Rest_mock;
using Header_map = std::unordered_multimap<std::string, std::string>;
using Str_vec = std::vector<std::string>;

constexpr std::array types {Ods::Endpoint_type::box,
                            Ods::Endpoint_type::dropbox,
                            Ods::Endpoint_type::gftp,
                            Ods::Endpoint_type::google_drive,
                            Ods::Endpoint_type::ftp,
                            Ods::Endpoint_type::http,
                            Ods::Endpoint_type::s3,
                            Ods::Endpoint_type::sftp};

class Transfer_service_impl_tests : public ::testing::Test {
};

/**
 * Tests that transfer throws a Connection_error when it receives one.
 */
TEST_F(Transfer_service_impl_tests, TransferThrowsConnectionErr)
{
    // set up mock
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post).Times(types.size() * types.size()).WillRepeatedly(Throw(Ods::Connection_error {""}));

    Ods::Internal::Transfer_service_impl transfer {"", "", std::move(caller)};

    for (auto src_type : types) {
        for (auto dest_type : types) {
            Ods::Source src {src_type, "", "", Str_vec {}};
            Ods::Destination dest {dest_type, "", ""};
            Ods::Transfer_options opt {};

            ASSERT_THROW(transfer.transfer(src, dest, opt), Ods::Connection_error);
        }
    }
}

/**
 * Tests that transfer throws an exception when it receives a 500 status.
 */
TEST_F(Transfer_service_impl_tests, TransferThrowsUnexpectedResponse)
{
    // set up mock
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post)
        .Times(types.size() * types.size())
        .WillRepeatedly(Return(Ods::Internal::Response {Header_map {}, "", 500}));

    Ods::Internal::Transfer_service_impl transfer {"", "", std::move(caller)};

    for (auto src_type : types) {
        for (auto dest_type : types) {
            Ods::Source src {src_type, "", "", Str_vec {}};
            Ods::Destination dest {dest_type, "", ""};
            Ods::Transfer_options opt {};

            ASSERT_THROW(transfer.transfer(src, dest, opt), Ods::Unexpected_response_error);
        }
    }
}

/**
 * Tests that transfer returns the correct job id.
 */
TEST_F(Transfer_service_impl_tests, TransferReturnsJobId)
{
    std::string job_id {"this is the job id"};

    // set up mock
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post)
        .Times(types.size() * types.size())
        .WillRepeatedly(Return(Ods::Internal::Response {Header_map {}, job_id, 200}));

    Ods::Internal::Transfer_service_impl transfer {"", "", std::move(caller)};

    for (auto src_type : types) {
        for (auto dest_type : types) {
            Ods::Source src {src_type, "", "", Str_vec {}};
            Ods::Destination dest {dest_type, "", ""};
            Ods::Transfer_options opt {};

            ASSERT_EQ(transfer.transfer(src, dest, opt), job_id);
        }
    }
}

/**
 * Tests that transfer sends the correct data to the server.
 */
TEST_F(Transfer_service_impl_tests, TransferSendsData)
{
    namespace Api = Ods::Internal::Api;

    const std::string source_cred_id {"source_cred_id string"};
    const std::string source_dir {"source_dir string"};
    const std::string source_file_1 {"source_file_1 string"};
    const std::string source_file_2 {"source_file_2 string"};
    const std::string destination_cred_id {"destination_cred_id string"};
    const std::string destination_dir {"destination_dir string"};

    const std::string job_id {"job_id string"};

    for (auto source_type : types) {
        for (auto destination_type : types) {
            const Ods::Source src {source_type, source_cred_id, source_dir, Str_vec {source_file_1, source_file_2}};
            const Ods::Destination dest {destination_type, destination_cred_id, destination_dir};
            const Ods::Transfer_options opt {};

            auto caller {std::make_unique<Rest_mock>()};
            EXPECT_CALL(*caller, post)
                .WillOnce([source_cred_id,
                           source_dir,
                           source_file_1,
                           source_file_2,
                           destination_cred_id,
                           destination_dir,
                           job_id,
                           source_type,
                           destination_type](const std::string& url,
                                             const std::unordered_multimap<std::string, std::string>& headers,
                                             const std::string& data) {
                    simdjson::dom::parser parser {};
                    auto json {parser.parse(data)};

                    auto src_type {json[Api::transfer_job_request_source][Api::source_type].get_c_str().value()};
                    auto src_cred {json[Api::transfer_job_request_source][Api::source_cred_id].get_c_str().value()};
                    auto src_id {json[Api::transfer_job_request_source][Api::source_info][Api::entity_info_id]
                                     .get_c_str()
                                     .value()};
                    auto src_path {json[Api::transfer_job_request_source][Api::source_info][Api::entity_info_path]
                                       .get_c_str()
                                       .value()};
                    auto src_f1_id {json[Api::transfer_job_request_source][Api::source_info_list]
                                        .at(0)[Ods::Internal::Api::entity_info_id]
                                        .get_c_str()
                                        .value()};
                    auto src_f1_path {json[Api::transfer_job_request_source][Api::source_info_list]
                                          .at(0)[Ods::Internal::Api::entity_info_path]
                                          .get_c_str()
                                          .value()};
                    auto src_f2_id {json[Api::transfer_job_request_source][Api::source_info_list]
                                        .at(1)[Ods::Internal::Api::entity_info_id]
                                        .get_c_str()
                                        .value()};
                    auto src_f2_path {json[Api::transfer_job_request_source][Api::source_info_list]
                                          .at(1)[Ods::Internal::Api::entity_info_path]
                                          .get_c_str()
                                          .value()};

                    auto dest_type {
                        json[Api::transfer_job_request_destination][Api::destination_type].get_c_str().value()};
                    auto dest_cred {
                        json[Api::transfer_job_request_destination][Api::destination_cred_id].get_c_str().value()};
                    auto dest_id {
                        json[Api::transfer_job_request_destination][Api::destination_info][Api::entity_info_id]
                            .get_c_str()
                            .value()};
                    auto dest_path {
                        json[Api::transfer_job_request_destination][Api::destination_info][Api::entity_info_path]
                            .get_c_str()
                            .value()};

                    if (src_type == Ods::Internal::Util::as_string(source_type) && src_cred == source_cred_id &&
                        src_id == source_dir && src_path == source_dir && src_f1_id == source_file_1 &&
                        src_f1_path == source_file_1 && src_f2_id == source_file_2 && src_f2_path == source_file_2 &&
                        dest_type == Ods::Internal::Util::as_string(destination_type) &&
                        dest_cred == destination_cred_id && dest_id == destination_dir &&
                        dest_path == destination_dir) {
                        return Ods::Internal::Response {Header_map {}, job_id, 200};

                    } else {
                        return Ods::Internal::Response {Header_map {}, "", 500};
                    }
                });

            Ods::Internal::Transfer_service_impl transfer {"", "", std::move(caller)};

            ASSERT_EQ(transfer.transfer(src, dest, opt), job_id);
        }
    }
}

} // namespace