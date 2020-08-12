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

#include "mocks.h"

namespace {

namespace Ods = One_data_share;

using ::testing::Return;
using ::testing::Throw;

using One_data_share_mocks::Rest_mock;
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

    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post)
        .Times(types.size() * types.size())
        .WillRepeatedly([source_cred_id,
                         source_dir,
                         source_file_1,
                         source_file_2,
                         destination_cred_id,
                         destination_dir,
                         job_id](const std::string& url,
                                 const std::unordered_multimap<std::string, std::string>& headers,
                                 const std::string& data) {
            simdjson::dom::parser parser {};
            auto json {parser.parse(data)};

            // auto src {json[Ods::Internal::Api::transfer_job_request_source].get_object().value()};
            // auto dest {json[Ods::Internal::Api::transfer_job_request_destination].get_object().value()};

            // auto src_type {src[Ods::Internal::Api::source_type].get_c_str().value()};
            // auto src_cred {src[Ods::Internal::Api::source_cred_id].get_c_str().value()};
            // auto src_info {src[Ods::Internal::Api::source_info].get_object().value()};
            // auto src_info_list {src[Ods::Internal::Api::source_info_list].get_array().value()};

            // auto src_dir_id {src_info[Ods::Internal::Api::entity_info_id].get_c_str().value()};
            // auto src_dir_path {src_info[Ods::Internal::Api::entity_info_path].get_c_str().value()};

            // auto src_i1_id {src_info_list.at(0)[Ods::Internal::Api::entity_info_id].get_c_str().value()};
            // auto src_i1_path {src_info_list.at(0)[Ods::Internal::Api::entity_info_path].get_c_str().value()};

            // auto src_i2_id {
            //     src_info_list.at(1).get_object().value()[Ods::Internal::Api::entity_info_id].get_c_str().value()};
            // auto src_i2_path {
            //     src_info_list.at(1).get_object().value()[Ods::Internal::Api::entity_info_path].get_c_str().value()};

            // auto dest_type {src[Ods::Internal::Api::destination_type].get_c_str().value()};
            // auto dest_cred {src[Ods::Internal::Api::destination_cred_id].get_c_str().value()};
            // auto dest_info {src[Ods::Internal::Api::destination_info].get_object().value()};

            // auto dest_dir_id {dest_info[Ods::Internal::Api::entity_info_id].get_c_str().value()};
            // auto dest_dir_path {dest_info[Ods::Internal::Api::entity_info_path].get_c_str().value()};

            auto src_type {json[Api::transfer_job_request_source][Api::source_type].get_c_str().value()};
            auto src_cred {json[Api::transfer_job_request_source][Api::source_cred_id].get_c_str().value()};
            auto src_id {
                json[Api::transfer_job_request_source][Api::source_info][Api::entity_info_id].get_c_str().value()};
            auto src_path {
                json[Api::transfer_job_request_source][Api::source_info][Api::entity_info_path].get_c_str().value()};
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

            auto dest_type {json[Api::transfer_job_request_destination][Api::destination_type].get_c_str().value()};
            auto dest_cred {json[Api::transfer_job_request_destination][Api::destination_cred_id].get_c_str().value()};
            auto dest_id {json[Api::transfer_job_request_destination][Api::destination_info][Api::entity_info_id]
                              .get_c_str()
                              .value()};
            auto dest_path {json[Api::transfer_job_request_destination][Api::destination_info][Api::entity_info_path]
                                .get_c_str()
                                .value()};

            if (src_cred == source_cred_id && src_id == source_dir && src_path == source_dir &&
                src_f1_id == source_file_1 && src_f1_path == source_file_1 && src_f2_id == source_file_2 &&
                src_f2_path == source_file_2 && dest_cred == destination_cred_id && dest_id == destination_dir &&
                dest_path == destination_dir) {
                return Ods::Internal::Response {Header_map {}, job_id, 200};

            } else {
                return Ods::Internal::Response {Header_map {}, "", 500};
            }

            // if (src_cred == cred_id && src_dir_id == source_dir && src_dir_path == source_dir &&
            //     src_i1_id == source_file_1 && src_i1_path == source_file_1 && src_i2_id == source_file_2 &&
            //     src_i2_path == source_file_2 && dest_cred == cred_id && dest_dir_id == destination_dir &&
            //     dest_dir_path == destination_dir) {
            //     return Ods::Internal::Response {Header_map {}, job_id, 200};

            // } else {
            //     return Ods::Internal::Response {Header_map {}, "", 500};
            // }

            // return Ods::Internal::Response {Header_map {}, "", 500};

            // auto [src_val, src_err] {json[Ods::Internal::Api::transfer_job_request_source].get_object()};
            // auto [dest_val, dest_err] {json[Ods::Internal::Api::transfer_job_request_destination].get_object()};

            // if (!src_err && !dest_err) {
            //     auto [src_type_val, src_type_err] {src_val[Ods::Internal::Api::source_type].get_c_str()};
            //     auto [src_cred_val, src_cred_err] {src_val[Ods::Internal::Api::source_cred_id].get_c_str()};
            //     auto [src_info_val, src_info_list] {src_val[Ods::Internal::Api::source_info].get_object()};
            //     auto [src_info_list_val, src_info_list_err]
            //     {src_val[Ods::Internal::Api::source_info_list].get_array()};

            //     if (!src_info_err) {
            //         auto [src_id_val, src_id_err] {src_info_val[Ods::Internal::Api::entity_info_id].get_c_str()};
            //         auto [src_path_val, src_path_err]
            //         {src_info_val[Ods::Internal::Api::entity_info_path].get_c_str()};
            //     }
            // }
        });

    Ods::Internal::Transfer_service_impl transfer {"", "", std::move(caller)};

    for (auto src_type : types) {
        for (auto dest_type : types) {
            const Ods::Source src {src_type, source_cred_id, source_dir, Str_vec {source_file_1, source_file_2}};
            const Ods::Destination dest {dest_type, destination_cred_id, destination_dir};
            const Ods::Transfer_options opt {};

            ASSERT_EQ(transfer.transfer(src, dest, opt), job_id);
        }
    }
}

} // namespace