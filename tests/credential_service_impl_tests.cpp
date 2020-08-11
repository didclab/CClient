/*
 * CredentialServiceImplTests.cpp
 * Andrew Mikalasen
 * 7/14/20
 */

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <simdjson/simdjson.h>

#include <onedatashare/ods_error.h>

#include <credential_service_impl.h>
#include <ods_rest_api.h>

#include "mocks.h"

namespace {

namespace Ods = One_data_share;

using One_data_share_mocks::Rest_mock;

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

constexpr std::array oauth_types {Ods::Oauth_endpoint_type::box,
                                  Ods::Oauth_endpoint_type::dropbox,
                                  Ods::Oauth_endpoint_type::gftp,
                                  Ods::Oauth_endpoint_type::google_drive};

constexpr std::array cred_types {Ods::Credential_endpoint_type::ftp,
                                 Ods::Credential_endpoint_type::http,
                                 Ods::Credential_endpoint_type::s3,
                                 Ods::Credential_endpoint_type::sftp};

constexpr std::array types {Ods::Endpoint_type::box,
                            Ods::Endpoint_type::dropbox,
                            Ods::Endpoint_type::gftp,
                            Ods::Endpoint_type::google_drive,
                            Ods::Endpoint_type::ftp,
                            Ods::Endpoint_type::http,
                            Ods::Endpoint_type::s3,
                            Ods::Endpoint_type::sftp};

class Credential_service_impl_test : public ::testing::Test {
};

/**
 * Tests that oauth_url throws an Connection_error when it recieves an Connection_error while trying to make a get
 * request.
 */
TEST_F(Credential_service_impl_test, OauthUrlThrowsConnectionErr)
{
    // set up mock throwing exception for every get
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get).Times(oauth_types.size()).WillRepeatedly(Throw(Ods::Connection_error {""}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    // check that every oauth endpoint type throws the correct exception
    for (auto type : oauth_types) {
        EXPECT_THROW(cred.oauth_url(type), Ods::Connection_error);
    }
}

/**
 * Tests that oauth_url throws an Unexpected_response_error when it recieves a status 500 from a get request.
 */
TEST_F(Credential_service_impl_test, OauthUrlThrowsUnexpectedResponse)
{
    // set up mock returning status 500 for every get
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get)
        .Times(oauth_types.size())
        .WillRepeatedly(
            Return(Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, "", 500}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    // check that every oauth endpoint type throws the correct exception
    for (auto type : oauth_types) {
        EXPECT_THROW(cred.oauth_url(type), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that oauth_url properly extracts the url from the response header.
 */
TEST_F(Credential_service_impl_test, OauthUrlGetsUrl)
{
    const std::string mock_oauth_url {"This is an oauth url"};
    const std::unordered_multimap headers {std::pair {std::string {"Location"}, mock_oauth_url}};

    // set up mock returning response redirecting to oauth url
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get)
        .Times(cred_types.size())
        .WillRepeatedly(Return(Ods::Internal::Response {headers, "", 303}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    // check every oauth endpoint correctly returns the oauth url
    for (auto type : oauth_types) {
        EXPECT_EQ(cred.oauth_url(type), mock_oauth_url);
    }
}

/**
 * Tests that register_credential throws an Connection_error when it recieves an Connection_error while trying to
 * make a post request.
 */
TEST_F(Credential_service_impl_test, RegisterCredentialThrowsConnectionErr)
{
    // set up mock throwing exception for every post
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post).Times(cred_types.size()).WillRepeatedly(Throw(Ods::Connection_error {""}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    // check that every credential endpoint type throws the correct exception
    for (auto type : cred_types) {
        EXPECT_THROW(cred.register_credential(type, "", "", nullptr, nullptr), Ods::Connection_error);
    }
}

/**
 * Tests that register_credential throws an Unexpected_response_error when it recieves a status 500 from a post
 * request.
 */
TEST_F(Credential_service_impl_test, RegisterCredentialThrowsUnexpectedResponse)
{
    // set up mock returning status 500 for every post
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post)
        .Times(cred_types.size())
        .WillRepeatedly(
            Return(Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, "", 500}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    // check that every credential endpoint type throws the correct exception
    for (auto type : cred_types) {
        EXPECT_THROW(cred.register_credential(type, "", "", nullptr, nullptr), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that regsiter_credential throws no exception when the response code is 200.
 */
TEST_F(Credential_service_impl_test, RegisterCredentialSucceeds)
{
    // set up mock returning status 200
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post)
        .Times(cred_types.size())
        .WillRepeatedly(
            Return(Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, "", 200}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    for (auto type : cred_types) {
        EXPECT_NO_THROW(cred.register_credential(type, "", "", nullptr, nullptr));
    }
}

/**
 * Tests that regsiter_credential sends the correct information to the server.
 */
TEST_F(Credential_service_impl_test, RegisterCredentialGivesCredentials)
{
    const std::string cred {"first value"};
    const std::string uri {"second value"};
    const std::string user {"third value"};
    const std::string pass {"fourth value"};

    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, post(_, _, _))
        .Times(cred_types.size())
        .WillRepeatedly([cred, uri, user, pass](const std::string& url,
                                                const std::unordered_multimap<std::string, std::string>& headers,
                                                const std::string& data) {
            simdjson::dom::parser parser {};
            auto json {parser.parse(data)};

            auto [cred_val, cred_err] {json[Ods::Internal::Api::endpoint_credential_account_id].get_c_str()};
            auto [uri_val, uri_err] {json[Ods::Internal::Api::endpoint_credential_uri].get_c_str()};
            auto [user_val, user_err] {json[Ods::Internal::Api::endpoint_credential_username].get_c_str()};
            auto [pass_val, pass_err] {json[Ods::Internal::Api::endpoint_credential_secret].get_c_str()};

            if (!cred_err && !uri_err && !user_err && !pass_err && cred_val == cred && uri_val == uri &&
                user_val == user && pass_val == pass) {
                return Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, "", 200};
            } else {
                return Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, "", 500};
            }
        });

    const Ods::Internal::Credential_service_impl cred_service {"", "", std::move(caller)};

    for (auto type : cred_types) {
        EXPECT_NO_THROW(cred_service.register_credential(type, cred, uri, &user, &pass));
    }
}

/**
 * Tests that regsiter_credential sends the correct information to the server when not giving a username.
 */
TEST_F(Credential_service_impl_test, RegisterCredentialGivesCredentialsNoUsername)
{
    FAIL();
}

/**
 * Tests that regsiter_credential sends the correct information to the server when not giving a password.
 */
TEST_F(Credential_service_impl_test, RegisterCredentialGivesCredentialsNoPassword)
{
    FAIL();
}

/**
 * Tests that regsiter_credential sends the correct information to the server when not giving a username nor password.
 */
TEST_F(Credential_service_impl_test, RegisterCredentialGivesCredentialsNoUsernamePassword)
{
    FAIL();
}

/**
 * Tests that list credential_id_list throws a connection error when it receives one.
 */
TEST_F(Credential_service_impl_test, CredentialIdListThrowsConnectionErr)
{
    // set up mock throwing exception
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get).Times(types.size()).WillRepeatedly(Throw(Ods::Connection_error {""}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    for (auto type : types) {
        EXPECT_THROW(cred.credential_id_list(type), Ods::Connection_error);
    }
}

/**
 * Tests that credential_id_list throws an exception when it receives a status 500.
 */
TEST_F(Credential_service_impl_test, CredentialIdListBadResponseCodeThrowsUnexpectedResponse)
{
    // set up mock returning response
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get)
        .Times(types.size())
        .WillRepeatedly(
            Return(Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, "", 500}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    for (auto type : types) {
        EXPECT_THROW(cred.credential_id_list(type), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that credential_id_list throws an exception when it receives an invalid response body.
 */
TEST_F(Credential_service_impl_test, CredentialIdListBadResponseBodyThrowsUnexpectedResponse)
{
    // set up mock returning response
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get)
        .Times(types.size())
        .WillRepeatedly(
            Return(Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, "", 200}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    for (auto type : types) {
        EXPECT_THROW(cred.credential_id_list(type), Ods::Unexpected_response_error);
    }
}

/**
 * Tests that credential_id_list returns the correct credential identifiers.
 */
TEST_F(Credential_service_impl_test, CredentialIdListReturnsListOfCredentialIds)
{
    const std::string cred1 {"my first credential"};
    const std::string cred2 {"my second credential"};
    const std::string cred3 {"my third credential"};

    const std::string json {"{\"credentialList\":[\"" + cred1 + "\",\"" + cred2 + "\",\"" + cred3 + "\"]}"};

    // set up mock returning response
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get)
        .Times(types.size())
        .WillRepeatedly(
            Return(Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, json, 200}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    for (auto type : types) {
        const auto list {cred.credential_id_list(type)};
        ASSERT_EQ(list.size(), 3);
        EXPECT_EQ(list[0], cred1);
        EXPECT_EQ(list[1], cred2);
        EXPECT_EQ(list[2], cred3);
    }
}

/**
 * Tests that credential_id_list returns an empty vector.
 */
TEST_F(Credential_service_impl_test, CredentialIdListReturnsEmptyList)
{
    const std::string json {"{\"credentialList\":[]}"};

    // set up mock returning response
    auto caller {std::make_unique<Rest_mock>()};
    EXPECT_CALL(*caller, get)
        .Times(types.size())
        .WillRepeatedly(
            Return(Ods::Internal::Response {std::unordered_multimap<std::string, std::string> {}, json, 200}));

    const Ods::Internal::Credential_service_impl cred {"", "", std::move(caller)};

    for (auto type : types) {
        const auto list {cred.credential_id_list(type)};
        EXPECT_EQ(list.size(), 0);
    }
}

} // namespace