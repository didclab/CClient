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

#include <onedatashare/ods_error.h>

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
            auto src {Ods::Source(src_type, "", "", Str_vec {})};
            auto dest {Ods::Destination(dest_type, "", "")};
            auto opt {Ods::Transfer_options::create()};

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
            auto src {Ods::Source(src_type, "", "", Str_vec {})};
            auto dest {Ods::Destination(dest_type, "", "")};
            auto opt {Ods::Transfer_options::create()};

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
            auto src {Ods::Source(src_type, "", "", Str_vec {})};
            auto dest {Ods::Destination(dest_type, "", "")};
            auto opt {Ods::Transfer_options::create()};

            ASSERT_EQ(transfer.transfer(src, dest, opt), job_id);
        }
    }
}

} // namespace