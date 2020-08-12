/*
 * endpoint_impl_tests.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <array>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <gtest/gtest.h>
#include <simdjson/simdjson.h>

#include <onedatashare/endpoint.h>
#include <onedatashare/endpoint_type.h>
#include <onedatashare/ods_error.h>

#include <endpoint_impl.h>
#include <ods_rest_api.h>

#include "mocks.h"

namespace {

namespace Ods = One_data_share;

using One_data_share_mocks::Rest_mock;

using ::testing::_;
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

const std::unordered_set id_types {Ods::Endpoint_type::box, Ods::Endpoint_type::google_drive};

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

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, "", 500}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that the Resource returned from list has no id when the stat object recieved doesn't have an id.
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        if (id_types.count(type) > 0) {
            EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
        } else {
            auto resource {endpoint.list("")};
            EXPECT_FALSE(resource.id);
        }
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_TRUE(resource.id);
        EXPECT_EQ(resource.id.value(), id_value);
    }
}

/**
 * Tests that the returned Resource has no link when the received Stat has no link.
 */
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        EXPECT_FALSE(resource.link);
    }
}

/**
 * Tests that the returned Resource has a link when the received Stat has a link.
 */
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_TRUE(resource.link);
        EXPECT_EQ(resource.link.value(), link_value);
    }
}

/**
 * Tests that the returned Resource has no permissions when the received Stat has no permissions.
 */
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        EXPECT_FALSE(resource.permissions);
    }
}

/**
 * Tests that the returned Resource has permissions when the received Stat has permissions.
 */
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_TRUE(resource.permissions);
        EXPECT_EQ(resource.permissions.value(), permissions_value);
    }
}

/**
 * Tests that the returned Resource has no contained resources when the received Stat has no contained resources.
 */
TEST_F(Endpoint_impl_tests, ListResourceWithoutContainedResources)
{
    std::string stat {R"({
        "id": "string",
        "name": "string",
        "size": 0,
        "time": 0,
        "dir": false,
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        EXPECT_FALSE(resource.contained_resources);
    }
}

/**
 * Tests that the returned Resource has contained resources when the received Stat has contained resources.
 */
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        ASSERT_TRUE(resource.contained_resources);
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that listing a resource returns the correct name, size, time, is_directory, and is_file.
 */
TEST_F(Endpoint_impl_tests, ListReturnsValues)
{
    std::string name_val {"this is the name"};
    auto size_val = 139;
    auto time_val = 24576;

    std::string stat {R"({
        "id": "",
        "name": ")" + name_val +
                      R"(",
        "size": )" + std::to_string(size_val) +
                      R"(,
        "time": )" + std::to_string(time_val) +
                      R"(,
        "dir": false,
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto resource {endpoint.list("")};

        EXPECT_EQ(resource.name, name_val);
        EXPECT_EQ(resource.size, size_val);
        EXPECT_EQ(resource.time, time_val);
        EXPECT_FALSE(resource.is_directory);
        EXPECT_TRUE(resource.is_file);
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
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        auto r {endpoint.list("")};

        auto id {r.id};
        auto name {r.name};
        auto size {r.size};
        auto time {r.time};
        auto dir {r.is_directory};
        auto file {r.is_file};
        auto link {r.link};
        auto perm {r.permissions};
        auto files {r.contained_resources};

        ASSERT_TRUE(id);
        ASSERT_TRUE(link);
        ASSERT_TRUE(perm);
        ASSERT_TRUE(files);
    }
}

/**
 * Tests that an exception is thrown when listing an id endpoint that returns a resource without an id.
 */
TEST_F(Endpoint_impl_tests, ListIdEndpointHasId)
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

    for (auto type : std::array {Ods::Endpoint_type::box, Ods::Endpoint_type::google_drive}) {
        // set up mock returning stat
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).WillOnce(Return(Ods::Internal::Response {Header_map {}, stat, 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        EXPECT_THROW(endpoint.list(""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that remove throws a Connection_error when it receives a Connection_error.
 */
TEST_F(Endpoint_impl_tests, RemoveThrowsConnectionErr)
{
    for (auto type : types) {
        // set up mock throwing exception
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Throw(Ods::Connection_error {""}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_THROW(endpoint.remove("", ""), Ods::Connection_error);
    }
}

/**
 * Tests that remove throws an Unexpected_response_error when it receives a response with status 500.
 */
TEST_F(Endpoint_impl_tests, RemoveThrowsUnexpectedResponse)
{
    for (auto type : types) {
        // set up mock returning response
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Return(Ods::Internal::Response {Header_map {}, "", 500}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_THROW(endpoint.remove("", ""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that remove returns when it receives a response with status 200.
 */
TEST_F(Endpoint_impl_tests, RemoveReturns)
{
    for (auto type : types) {
        // set up mock returning response
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Return(Ods::Internal::Response {Header_map {}, "", 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_NO_THROW(endpoint.remove("", ""));
    }
}

/**
 * Tests that remove sends the correct data to the server.
 */
TEST_F(Endpoint_impl_tests, RemoveGivesData)
{
    const std::string cred_id {"cred_id string"};
    const std::string identifier {"identifier string"};
    const std::string to_remove {"to_remove string"};

    auto execute_post {
        [cred_id, identifier, to_remove](const std::string& url, const Header_map headers, const std::string& data) {
            simdjson::dom::parser parser {};
            auto json {parser.parse(data)};

            auto [cred_val, cred_err] {json[Ods::Internal::Api::delete_operation_cred_id].get_c_str()};
            auto [path_val, path_err] {json[Ods::Internal::Api::delete_operation_path].get_c_str()};
            auto [id_val, id_err] {json[Ods::Internal::Api::delete_operation_id].get_c_str()};
            auto [del_val, del_err] {json[Ods::Internal::Api::delete_operation_to_delete].get_c_str()};

            if (!cred_err && !path_err && !id_err && !del_err && cred_val == cred_id && path_val == identifier &&
                id_val == identifier && del_val == to_remove) {
                return Ods::Internal::Response {Header_map {}, "", 200};
            } else {
                return Ods::Internal::Response {Header_map {}, "", 500};
            }
        }};

    for (auto type : types) {
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post(_, _, _)).WillOnce(execute_post);

        const Ods::Internal::Endpoint_impl endpoint {type, cred_id, "", "", std::move(caller)};

        ASSERT_NO_THROW(endpoint.remove(identifier, to_remove));
    }
}

/**
 * Tests that mkdir throws a Connection_err when it receives one.
 */
TEST_F(Endpoint_impl_tests, MkdirThrowsConnectionErr)
{
    for (auto type : types) {
        // set up mock throwing exception
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Throw(Ods::Connection_error {""}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_THROW(endpoint.mkdir("", ""), Ods::Connection_error);
    }
}

/**
 * Tests that mkdir throws an Unexpected_response_err when it receives a 500 response.
 */
TEST_F(Endpoint_impl_tests, MkdirThrowsUnexpectedResponse)
{
    for (auto type : types) {
        // set up mock returning response
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Return(Ods::Internal::Response {Header_map {}, "", 500}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_THROW(endpoint.mkdir("", ""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that mkdir returns without throwing when it receives a 200 response.
 */
TEST_F(Endpoint_impl_tests, MkdirReturns)
{
    for (auto type : types) {
        // set up mock returning response
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Return(Ods::Internal::Response {Header_map {}, "", 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_NO_THROW(endpoint.mkdir("", ""));
    }
}

/**
 * Tests that mkdir sends the correct data to the server.
 */
TEST_F(Endpoint_impl_tests, MkdirSendsData)
{
    FAIL();
}

/**
 * Tests that donwload throws a Connection_err when it receives one.
 */
TEST_F(Endpoint_impl_tests, DownloadThrowsConnectionErr)
{
    for (auto type : types) {
        // set up mock throwing exception
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Throw(Ods::Connection_error {""}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_THROW(endpoint.download("", ""), Ods::Connection_error);
    }
}

/**
 * Tests that Download throws an Unexpected_response_err when it receives a 500 status.
 */
TEST_F(Endpoint_impl_tests, DownloadThrowsUnexpectedResponse)
{
    for (auto type : types) {
        // set up mock returning response
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Return(Ods::Internal::Response {Header_map {}, "", 500}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_THROW(endpoint.download("", ""), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that download returns without throwing when it receives a 200 status.
 */
TEST_F(Endpoint_impl_tests, DownloadReturns)
{
    for (auto type : types) {
        // set up mock returning response
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).WillOnce(Return(Ods::Internal::Response {Header_map {}, "", 200}));

        const Ods::Internal::Endpoint_impl endpoint {type, "", "", "", std::move(caller)};

        ASSERT_NO_THROW(endpoint.download("", ""));
    }
}

/**
 * Tests that download sends the correct data to the server.
 */
TEST_F(Endpoint_impl_tests, DownloadSendsData)
{
    FAIL();
}

} // namespace