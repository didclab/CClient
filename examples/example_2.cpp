/*
 * example_2.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include <fstream>
#include <iostream>

#include "../src/curl_rest.h"
#include "../src/internal/credential_service_impl.h"

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

    std::unique_ptr<One_data_share::Rest> caller(std::make_unique<One_data_share::Curl_rest>());

    auto cred(std::make_unique<One_data_share::Credential_service_impl>(token, url, std::move(caller)));

    std::cout << cred->oauth_url(One_data_share::Oauth_endpoint_type::googledrive) << std::endl;
    cred->register_credential(One_data_share::Credential_endpoint_type::ftp, "this is a test", "this is a test", "this is a test", "this is a test");
}