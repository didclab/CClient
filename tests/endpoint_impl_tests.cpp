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

/**
 * Tests that list throws an Unexpected_response_error when the response has a 500 status code
 */
TEST_F(Endpoint_impl_tests, ListWithBadStatusCodeThrowsUnexpectedResponse)
{
    for (auto type : types) {
        // set up mock returning status 500 for every get
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, "", 500}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that list throws an Unexpected_response_error when the response body is not a valid stat object.
 */
TEST_F(Endpoint_impl_tests, ListWithBadResponseBodyThrowsUnexpectedResponse)
{
    std::string stat {""};

    for (auto type : types) {
        // set up mock returning status 500 for every get
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that the Resource returned from list returns null from id when the stat object recieved doesn't have an id.
 */
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
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_NE(resource, nullptr);
        EXPECT_EQ(resource->id(), nullptr);
    }
}

/**
 * Tests that the Resource returned from list returns the id from id when the stat object recieved has an id.
 */
TEST_F(Endpoint_impl_tests, ListResourceWithID)
{
    std::string id_value {"this is the id"};

    std::string stat {R"({
        "id": ")" + id_value +
                      R"(",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "permissions": "string",
        "files": [
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
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

TEST_F(Endpoint_impl_tests, ListResourceWithoutLink)
{
    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "permissions": "string",
        "files": [
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_NE(resource, nullptr);
        EXPECT_EQ(resource->link(), nullptr);
    }
}

TEST_F(Endpoint_impl_tests, ListResourceWithLink)
{
    std::string link_value {"this is the link"};

    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": ")" + link_value +
                      R"(",
        "permissions": "string",
        "files": [
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};
        ASSERT_NE(resource, nullptr);

        auto link {resource->link()};

        ASSERT_NE(link, nullptr);
        EXPECT_EQ(*link, link_value);
    }
}

TEST_F(Endpoint_impl_tests, ListResourceWithoutPermissions)
{
    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "files": [
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_NE(resource, nullptr);
        EXPECT_EQ(resource->permissions(), nullptr);
    }
}

TEST_F(Endpoint_impl_tests, ListResourceWithPermissions)
{
    std::string permissions_value {"these are the permissions"};

    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "permissions": ")" +
                      permissions_value +
                      R"(",
        "files": [
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};
        ASSERT_NE(resource, nullptr);

        auto permissions {resource->permissions()};

        ASSERT_NE(permissions, nullptr);
        EXPECT_EQ(*permissions, permissions_value);
    }
}

TEST_F(Endpoint_impl_tests, ListResourceWithoutContainedResources)
{
    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "permissions": "string",
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_NE(resource, nullptr);
        EXPECT_EQ(resource->contained_resources(), nullptr);
    }
}

TEST_F(Endpoint_impl_tests, ListResourceWithContainedResources)
{
    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "permissions": "string",
        "files": [
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};
        ASSERT_NE(resource, nullptr);

        auto files {resource->contained_resources()};

        ASSERT_NE(files, nullptr);
    }
}

/**
 * Tests that an Unexpected_response_error is thrown if a listed resource is a directory and it doesnt have contained
 * resources.
 */
TEST_F(Endpoint_impl_tests, ListDirectoryWithoutContainedResourcesThrowsUnexpectedResponse)
{
    // NOTE: this needs to be tested because it is one of the guaranties provided by the SDK

    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": false,
        "link": "string",
        "permissions": "string",
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that listing a resource always returns the correct name, size, and time.
 */
TEST_F(Endpoint_impl_tests, ListReturnsValues)
{
    std::string name_val {"this is the name"};
    auto size_val = 139;
    auto time_val = 24576;

    std::string stat {R"({
        "name": ")" + name_val +
                      R"(",
        "size": )" + std::to_string(size_val) +
                      R"(,
        "time": )" + std::to_string(time_val) +
                      R"(,
        "dir": true,
        "file": true,
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};
        ASSERT_NE(resource, nullptr);

        EXPECT_EQ(resource->name(), name_val);
        EXPECT_EQ(resource->size(), size_val);
        EXPECT_EQ(resource->time(), time_val);
    }
}

/**
 * Tests that list parses a stat object with all of the possible fields defined.
 */
TEST_F(Endpoint_impl_tests, ListParsesStat)
{
    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": true,
        "file": true,
        "link": "string",
        "permissions": "string",
        "files": [
        ],
        "filesList": [
            null
        ],
        "total_size": 0,
        "total_num": 0
    })"};

    for (auto type : types) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Response {Header_map {}, stat, 200}));

        const Ods::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto r {endpoint.list("")};
        ASSERT_NE(r, nullptr);

        auto id {r->id()};
        auto name {r->name()};
        auto size {r->size()};
        auto time {r->time()};
        auto dir {r->is_directory()};
        auto file {r->is_file()};
        auto link {r->link()};
        auto perm {r->permissions()};
        auto files {r->contained_resources()};

        ASSERT_NE(id, nullptr);
        ASSERT_NE(link, nullptr);
        ASSERT_NE(perm, nullptr);
        ASSERT_NE(files, nullptr);
    }
}

} // namespace