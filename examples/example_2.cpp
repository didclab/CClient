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

    // read token from file
    std::ifstream token_file {"token.txt"};
    if (!token_file.is_open()) {
        // print error message and exit
        std::cout << "Unable to open file \"token.txt\". Be sure to create a \"token.txt\" file in the project root. "
                     "See README.md for more information."
                  << std::endl;
        return -1;
    }
    std::getline(token_file, token);
    token_file.close();

    // read url from file
    std::ifstream url_file {"url.txt"};
    if (!url_file.is_open()) {
        // print error message and exit
        std::cout << "Unable to open file \"url.txt\". Be sure to create a \"url.txt\" file in the project root. "
                     "See README.md for more information."
                  << std::endl;
        return -1;
    }
    std::getline(url_file, url);
    url_file.close();

    std::unique_ptr<One_data_share::Rest> caller {std::make_unique<One_data_share::Curl_rest>()};

    auto cred {std::make_unique<One_data_share::Credential_service_impl>(token, url, std::move(caller))};

    std::cout << cred->oauth_url(One_data_share::Oauth_endpoint_type::googledrive) << std::endl;

    cred->register_credential(One_data_share::Credential_endpoint_type::ftp,
                              "this is a test",
                              "this is a test",
                              "this is a test",
                              "this is a test");
}