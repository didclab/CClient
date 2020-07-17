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
#include <onedatashare/ods_error.h>
#include <credential_service_impl.h>


namespace {

    using ::testing::Return;
    using ::testing::Throw;

    constexpr std::array OAUTH_TYPES {
        One_data_share::Oauth_endpoint_type::box,
        One_data_share::Oauth_endpoint_type::dropbox,
        One_data_share::Oauth_endpoint_type::gftp,
        One_data_share::Oauth_endpoint_type::googledrive
    };

    constexpr std::array CREDENTIAL_TYPES {
        One_data_share::Credential_endpoint_type::ftp,
        One_data_share::Credential_endpoint_type::http,
        One_data_share::Credential_endpoint_type::s3,
        One_data_share::Credential_endpoint_type::sftp
    };

    class CredentialServiceImplTest : public ::testing::Test {
        protected:
    };

    class MockRest : public One_data_share::Rest {
        using HeaderMap = std::unordered_multimap<std::string, std::string>;
    public:
        MOCK_METHOD(One_data_share::Response, get, (const std::string& url, const HeaderMap& headers), (const, override));
        MOCK_METHOD(One_data_share::Response, post, (const std::string& url, const HeaderMap& headers, const std::string& data), (const, override));
};

    /**
     * Tests that oauth_url throws an Connection_error when it recieves
     * an Connection_error while trying to make a get request.
     */
    TEST_F(CredentialServiceImplTest, OauthUrlThrowsIO) {
        // set up mock throwing exception for every get
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, get).Times(OAUTH_TYPES.size()).WillRepeatedly(Throw(One_data_share::Connection_error("")));

        const One_data_share::Credential_service_impl cred("", "", std::move(caller));

        // check that every oauth endpoint type throws the correct exception
        for (auto type : OAUTH_TYPES) {
            EXPECT_THROW(cred.oauth_url(type), One_data_share::Connection_error);
        }
    }

    /**
     * Tests that oauth_url throws an Unexpected_response_error when it
     * recieves a status 500 from a get request.
     */
    TEST_F(CredentialServiceImplTest, OauthUrlThrowsUnexpectedResponse) {
        // set up mock returning status 500 for every get
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, get).Times(OAUTH_TYPES.size()).WillRepeatedly(Return(One_data_share::Response(std::unordered_multimap<std::string, std::string>(), "", 500)));

        const One_data_share::Credential_service_impl cred("", "", std::move(caller));
        
        // check that every oauth endpoint type throws the correct exception
        for (auto type : OAUTH_TYPES) {
            EXPECT_THROW(cred.oauth_url(type), One_data_share::Unexpected_response_error);
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
        EXPECT_CALL(*caller, get).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Return(One_data_share::Response(headers, "", 303)));

        const One_data_share::Credential_service_impl cred("", "", std::move(caller));

        // check every oauth endpoint correctly returns the oauth url
        for (auto type : OAUTH_TYPES) {
            EXPECT_EQ(cred.oauth_url(type), mock_oauth_url);
        }
    }

    /**
     * Tests that register_credential throws an Connection_error when it recieves an
     * Connection_error while trying to make a post request.
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialThrowsIO) {
        // set up mock throwing exception for every post
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Throw(One_data_share::Connection_error("")));

        const One_data_share::Credential_service_impl cred("", "", std::move(caller));

        // check that every credential endpoint type throws the correct exception
        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), One_data_share::Connection_error);
        }
    }

    /**
     * Tests that register_credential throws an Unexpected_response_error when
     * it recieves a status 500 from a post request.
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialThrowsUnexpectedResponse) {
        // set up mock returning status 500 for every post
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Return(One_data_share::Response(std::unordered_multimap<std::string, std::string>(), "", 500)));

        const One_data_share::Credential_service_impl cred("", "", std::move(caller));

        // check that every credential endpoint type throws the correct exception
        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_THROW(cred.register_credential(type, "", "", "", ""), One_data_share::Unexpected_response_error);
        }
    }

    /**
     * Tests that regsiter_credential throws no exception when the response code is 200.
     */
    TEST_F(CredentialServiceImplTest, RegisterCredentialSucceeds) {
        // set up mock returning status 200
        auto caller(std::make_unique<MockRest>());
        EXPECT_CALL(*caller, post).Times(CREDENTIAL_TYPES.size()).WillRepeatedly(Return(One_data_share::Response(std::unordered_multimap<std::string, std::string>(), "", 200)));

        const One_data_share::Credential_service_impl cred("", "", std::move(caller));

        for (auto type : CREDENTIAL_TYPES) {
            EXPECT_NO_THROW(cred.register_credential(type, "", "", "", ""));
        }
    }
}