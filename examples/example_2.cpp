/*
 * example_2.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include <fstream>
#include <iostream>

#include <credential_service_impl.h>
#include <curl_rest.h>

int main()
{
    namespace Ods = One_data_share;

    std::string url {};
    std::string token {};

    // open file containing url, token
    std::ifstream file {"token.txt"};
    if (!file.is_open()) {
        // print error message and exit
        std::cout << "Unable to open file \"token.txt\". Be sure to create a \"token.txt\" file in the project root. "
                     "See README.md for more information."
                  << std::endl;
        return -1;
    }

    // read url, token from file
    std::getline(file, url);   // read first line
    std::getline(file, token); // read second line

    file.close();

    std::unique_ptr<One_data_share::Rest> caller {std::make_unique<One_data_share::Curl_rest>()};

    auto cred {std::make_unique<One_data_share::Credential_service_impl>(token, url, std::move(caller))};

    std::cout << cred->oauth_url(One_data_share::Oauth_endpoint_type::googledrive) << std::endl;

    cred->register_credential(One_data_share::Credential_endpoint_type::ftp,
                              "this is a test",
                              "this is a test",
                              "this is a test",
                              "this is a test");
}