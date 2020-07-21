/*
 * CredentialServiceImplTests.cpp
 * Andrew Mikalasen
 * 7/14/20
 */

#include <array>
#include <memory>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <credential_service_impl.h>
#include <onedatashare/ods_error.h>

#include "mocks.h"

namespace {

    namespace Ods = One_data_share;

    using One_data_share_mocks::Rest_mock;

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

    class Credential_service_impl_test : public ::testing::Test {
    };

    /**
     * Tests that oauth_url throws an Connection_error when it recieves an Connection_error while trying to make a get
     * request.
     */
    TEST_F(Credential_service_impl_test, OauthUrlThrowsIO)
    {
        // set up mock throwing exception for every get
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).Times(oauth_types.size()).WillRepeatedly(Throw(Ods::Connection_error {""}));

        const Ods::Credential_service_impl cred {"", "", std::move(caller)};

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
            .WillRepeatedly(Return(Ods::Response {std::unordered_multimap<std::string, std::string> {}, "", 500}));

        const Ods::Credential_service_impl cred {"", "", std::move(caller)};

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
        std::string mock_oauth_url {"This is an oauth url"};
        std::unordered_multimap headers {std::pair {std::string {"Location"}, mock_oauth_url}};

        // set up mock returning response redirecting to oauth url
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, get).Times(cred_types.size()).WillRepeatedly(Return(Ods::Response {headers, "", 303}));

        const Ods::Credential_service_impl cred {"", "", std::move(caller)};

        // check every oauth endpoint correctly returns the oauth url
        for (auto type : oauth_types) {
            EXPECT_EQ(cred.oauth_url(type), mock_oauth_url);
        }
    }

    /**
     * Tests that register_credential throws an Connection_error when it recieves an Connection_error while trying to
     * make a post request.
     */
    TEST_F(Credential_service_impl_test, RegisterCredentialThrowsIO)
    {
        // set up mock throwing exception for every post
        auto caller {std::make_unique<Rest_mock>()};
        EXPECT_CALL(*caller, post).Times(cred_types.size()).WillRepeatedly(Throw(Ods::Connection_error {""}));

        const Ods::Credential_service_impl cred {"", "", std::move(caller)};

        // check that every credential endpoint type throws the correct exception
        for (auto type : cred_types) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), Ods::Connection_error);
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
            .WillRepeatedly(Return(Ods::Response {std::unordered_multimap<std::string, std::string> {}, "", 500}));

        const Ods::Credential_service_impl cred {"", "", std::move(caller)};

        // check that every credential endpoint type throws the correct exception
        for (auto type : cred_types) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), Ods::Unexpected_response_error);
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
            .WillRepeatedly(Return(Ods::Response(std::unordered_multimap<std::string, std::string> {}, "", 200)));

        const Ods::Credential_service_impl cred {"", "", std::move(caller)};

        for (auto type : cred_types) {
            EXPECT_NO_THROW(cred.register_credential(type, "", "", "", ""));
        }
    }
}