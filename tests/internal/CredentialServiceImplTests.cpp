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

namespace {

    using ::testing::Return;
    using ::testing::Throw;

    constexpr auto URL = "THIS IS A URL";
    constexpr auto TOKEN = "THIS IS A TOKEN";

    constexpr auto CONNECTION_ERROR_MSG = "Unable to connect";

    constexpr auto STATUS_500_ERROR_JSON = R"({"error":"Internal Server Error","message":"AN ERROR OCCURED"})";

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

    class CredentialServiceImplTest: public ::testing::Test {
        protected:
    };

    class MockRest: public ods::rest::Rest {
        using HeaderMap = std::unordered_multimap<std::string, std::string>;
        public:
            MOCK_METHOD(ods::rest::Response, get, (const std::string& url, const HeaderMap& headers), (const, override));
            MOCK_METHOD(ods::rest::Response, post, (const std::string& url, const HeaderMap& headers, const std::string& data), (const, override));
    };

    /**
     * Tests that trying to get an oauth url while unable to connect to One Data
     * Share throws an exception.
     */
    TEST_F(CredentialServiceImplTest, OauthUrlWithoutConnectionThrowsException) {
        // set up mock throwing an exception for every get
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, get).Times(OAUTH_TYPES.size()).WillRepeatedly(Throw(std::runtime_error(CONNECTION_ERROR_MSG)));

        const ods::internal::CredentialServiceImpl cred(TOKEN, URL, std::move(caller));

        // check that every oauth endpoint type throws the correct exception
        for (auto type : OAUTH_TYPES) {
            EXPECT_THROW(cred.oauth_url(type), ods::ODSConnectionException);
        }
    }

    /**
     * Tests that trying to get an oauth url using an invalid One Data Share 
     * token throws an exception.
     */
    TEST_F(CredentialServiceImplTest, OauthUrlUsingInvalidTokenThrowsException) {
        // set up mock returning status 500 for every get
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, get).Times(OAUTH_TYPES.size()).WillRepeatedly(Return(ods::rest::Response(std::unordered_multimap<std::string, std::string>(), STATUS_500_ERROR_JSON, 500)));

        const ods::internal::CredentialServiceImpl cred(TOKEN, URL, std::move(caller));
        
        // check that every oauth endpoint type throws the correct exception
        for (auto type : OAUTH_TYPES) {
            EXPECT_THROW(cred.oauth_url(type), ods::ODSInternalServerException);
        }
    }

    /**
     * Tests that trying to register a credential while unable to connect to One
     * Data Share throws an exception
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialWithoutConnectionThrowsException) {
        // set up mock throwing exception for every post
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Throw(std::exception()));

        const ods::internal::CredentialServiceImpl cred(TOKEN, URL, std::move(caller));

        // check that every credential endpoint type throws the correct exception
        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), ods::ODSConnectionException);
        }
    }

    /**
     * Tests that trying to register a credential while using an invalid One
     * Data Share token throws an exception.
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialUsingInvalidTokenThrowsException) {
        // set up mock returning status 500 for every post
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Return(ods::rest::Response(std::unordered_multimap<std::string, std::string>(), STATUS_500_ERROR_JSON, 500)));

        const ods::internal::CredentialServiceImpl cred(TOKEN, URL, std::move(caller));

        // check that every credential endpoint type throws the correct exception
        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), ods::ODSInternalServerException);
        }
    }
}