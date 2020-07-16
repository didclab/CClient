/*
 * CredentialServiceImplTests.cpp
 * Andrew Mikalasen
 * 7/14/20
 */

#include <array>
#include <memory>
#include <stdexcept>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <internal/CredentialServiceImpl.hpp>
#include <rest/Rest.hpp>
#include <ODSException.hpp>
#include <IOException.hpp>
#include <UnexpectedResponseException.hpp>

namespace {

    using ::testing::Return;
    using ::testing::Throw;

    constexpr std::array OAUTH_TYPES {
        ods::OAuthEndpointType::BOX,
        ods::OAuthEndpointType::DROPBOX,
        ods::OAuthEndpointType::GFTP,
        ods::OAuthEndpointType::GOOGLE_DRIVE
    };

    constexpr std::array CREDENTIAL_TYPES {
        ods::CredentialEndpointType::FTP,
        ods::CredentialEndpointType::HTTP,
        ods::CredentialEndpointType::S3,
        ods::CredentialEndpointType::SFTP
    };

    class CredentialServiceImplTest : public ::testing::Test {
        protected:
    };

    class MockRest : public ods::rest::Rest {
        using HeaderMap = std::unordered_multimap<std::string, std::string>;
        public:
            MOCK_METHOD(ods::rest::Response, get, (const std::string& url, const HeaderMap& headers), (const, override));
            MOCK_METHOD(ods::rest::Response, post, (const std::string& url, const HeaderMap& headers, const std::string& data), (const, override));
    };

    /**
     * Tests that oauth_url throws an IOException when it recieves
     * an IOException while trying to make a get request.
     */
    TEST_F(CredentialServiceImplTest, OauthUrlThrowsIOException) {
        // set up mock throwing exception for every get
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, get).Times(OAUTH_TYPES.size()).WillRepeatedly(Throw(ods::IOException("")));

        const ods::internal::CredentialServiceImpl cred("", "", std::move(caller));

        // check that every oauth endpoint type throws the correct exception
        for (auto type : OAUTH_TYPES) {
            EXPECT_THROW(cred.oauth_url(type), ods::IOException);
        }
    }

    /**
     * Tests that oauth_url throws an UnexpectedResponseException when it
     * recieves a status 500 from a get request.
     */
    TEST_F(CredentialServiceImplTest, OauthUrlThrowsUnexpectedResponseException) {
        // set up mock returning status 500 for every get
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, get).Times(OAUTH_TYPES.size()).WillRepeatedly(Return(ods::rest::Response(std::unordered_multimap<std::string, std::string>(), "", 500)));

        const ods::internal::CredentialServiceImpl cred("", "", std::move(caller));
        
        // check that every oauth endpoint type throws the correct exception
        for (auto type : OAUTH_TYPES) {
            EXPECT_THROW(cred.oauth_url(type), ods::UnexpectedResponseException);
        }
    }

    /**
     * Tests that oauth_url properly extracts the url from the response header.
     */
    TEST_F(CredentialServiceImplTest, OauthUrlGetsUrl) {
        std::string mock_oauth_url("This is an oauth url");
        std::unordered_multimap headers{std::pair(std::string("Location"), std::string(mock_oauth_url))};

        // set up mock returning response redirecting to oauth url
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, get).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Return(ods::rest::Response(headers, "", 303)));

        const ods::internal::CredentialServiceImpl cred("", "", std::move(caller));

        // check every oauth endpoint correctly returns the oauth url
        for (auto type : OAUTH_TYPES) {
            EXPECT_EQ(cred.oauth_url(type), mock_oauth_url);
        }
    }

    /**
     * Tests that register_credential throws an IOException when it recieves an
     * IOException while trying to make a post request.
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialThrowsIOException) {
        // set up mock throwing exception for every post
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Throw(ods::IOException("")));

        const ods::internal::CredentialServiceImpl cred("", "", std::move(caller));

        // check that every credential endpoint type throws the correct exception
        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), ods::IOException);
        }
    }

    /**
     * Tests that register_credential throws an UnexpectedResponseException when
     * it recieves a status 500 from a post request.
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialThrowsUnexpectedResponseException) {
        // set up mock returning status 500 for every post
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Return(ods::rest::Response(std::unordered_multimap<std::string, std::string>(), "", 500)));

        const ods::internal::CredentialServiceImpl cred("", "", std::move(caller));

        // check that every credential endpoint type throws the correct exception
        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), ods::UnexpectedResponseException);
        }
    }

    /**
     * Tests that regsiter_credential throws no exception when the response code is 200.
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialSucceeds) {
        // set up mock returning status 200
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Return(ods::rest::Response(std::unordered_multimap<std::string, std::string>(), "", 200)));

        const ods::internal::CredentialServiceImpl cred("", "", std::move(caller));

        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_NO_THROW(cred.register_credential(type, "", "", "", ""));
        }
    }
}