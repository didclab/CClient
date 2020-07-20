/*
 * example_1.cpp
 * Andrew Mikalsen
 * 7/8/20
 */

#include <fstream>
#include <iostream>
#include <memory>

#include <onedatashare/credential_service.h>
#include <onedatashare/endpoint.h>
#include <onedatashare/endpoint_type.h>

/**
 * Registers a new FTP endpoint and lists the contents of its root directory.
 */
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

    const std::string my_cred_id {"my_endpoint"};

    // register new endpoint
    const auto cred_service {Ods::Credential_service::create(token)};
    cred_service->register_credential(Ods::Credential_endpoint_type::ftp,
                                      my_cred_id,
                                      "ftp://speedtest.tele2.net",
                                      "",
                                      "");

    // print oauth url for dropbox
    std::cout << cred_service->oauth_url(Ods::Oauth_endpoint_type::dropbox) << std::endl;

    // // print root of new endpoint
    // const auto my_endpoint(Ods::Endpoint::create(Ods::Endpoint_type::ftp, my_cred_id, token));
    // const auto root(my_endpoint->list("/"));
    // if (root->is_directory()) {
    //     for (auto r : *root->contained_resources()) {
    //         std::cout << r->name() << std::endl;
    //     }
    // }

    return 0;
}