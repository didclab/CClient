/*
 * example_2.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include <fstream>
#include <iostream>
#include "../src/rest/CurlRest.hpp"
#include "../src/internal/CredentialServiceImpl.hpp"

int main() {
    std::string url;
    std::string token;

    std::ifstream file("token.txt");    
    if (!file.is_open()) {
        std::cout << "Unable to open file \"token.txt\". Be sure to create a \"token.txt\" file in the project root. "
                << "See README.md for more information."
                << std::endl;
        return false;
    }
    std::getline(file, url);
    std::getline(file, token);

    file.close();

    std::unique_ptr<ods::rest::Rest> caller(std::make_unique<ods::rest::CurlRest>());

    auto cred(std::make_unique<ods::internal::CredentialServiceImpl>(token, url, std::move(caller)));

    std::cout << cred->oauth_url(ods::OAuthEndpointType::GOOGLE_DRIVE) << std::endl;
    std::cout << cred->register_credential(ods::CredentialEndpointType::FTP, "this is a test", "this is a test", "this is a test", "this is a test") << std::endl;
}