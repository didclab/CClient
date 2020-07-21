/*
 * endpoint_impl_tests.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include <gtest/gtest.h>

#include <onedatashare/endpoint.h>
#include <onedatashare/endpoint_type.h>
#include <onedatashare/ods_error.h>

#include <endpoint_impl.h>

#include "mocks.h"

namespace {

namespace Ods = One_data_share;

using One_data_share_mocks::Rest_mock;

using ::testing::Return;
using ::testing::Throw;

using Header_map = std::unordered_multimap<std::string, std::string>;

constexpr std::array types {Ods::Endpoint_type::box,
                            Ods::Endpoint_type::dropbox,
                            Ods::Endpoint_type::gftp,
                            Ods::Endpoint_type::google_drive,
                            Ods::Endpoint_type::ftp,
                            Ods::Endpoint_type::http,
                            Ods::Endpoint_type::s3,
                            Ods::Endpoint_type::sftp};

class Endpoint_impl_tests : public ::testing::Test {
};

/**
 * Tests that list throws a Connection_error when it recieves a Connection_error while making a get request.
 */
TEST_F(Endpoint_impl_tests, ListThrowsConnectionErr)
{
    for (auto type : types) {
        // set up mock throwing exception for every get
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Throw(Ods::Connection_error {""}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Connection_error);
    }
}

TEST_F(Endpoint_impl_tests, ListThrowsUnexpectedResponse)
{
    for (auto type : types) {
        // set up mock returning status 500 for every get
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, "", 500}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
    }
}

TEST_F(Endpoint_impl_tests, ListResourceWithoutID)
{
    std::string stat {R"({
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "permissions": "string",
        "files": [
            null
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat without an id
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_NE(resource, nullptr);
        EXPECT_EQ(resource->id(), nullptr);
    }
}

TEST_F(Endpoint_impl_tests, ListResourceWithID)
{
    std::string id_value {R"("this is the id")"};

    std::string stat {R"({
        "id": )" + id_value +
                      R"(,
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "permissions": "string",
        "files": [
            null
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat without an id
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};
        ASSERT_NE(resource, nullptr);

        auto id {resource->id()};

        ASSERT_NE(id, nullptr);
        EXPECT_EQ(*id, id_value);
    }
}

} // namespace