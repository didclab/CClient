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
 * Loads the token and url from a token.txt file.
 *
 * @param token mutably borrowed pointer to the token which is set to the token read from the file
 * @param url mutably borrowed pointer to the url which is set to the url read from the file
 */
bool load_from_file(std::string* token, std::string* url)
{
    std::ifstream file("token.txt");
    if (!file.is_open()) {
        std::cout << "Unable to open file \"token.txt\". Be sure to create a \"token.txt\" file in the project root. "
                     "See README.md for more information."
                  << std::endl;
        return false;
    }
    std::getline(file, *url);
    std::getline(file, *token);

    file.close();

    return true;
}

/**
 * Registers a new FTP endpoint and lists the contents of its root directory.
 */
int main()
{
    std::string token;
    std::string _;
    if (!load_from_file(&token, &_)) {
        return -1;
    }

    namespace Ods = One_data_share;

    const std::string my_cred_id("my_endpoint");

    // register new endpoint
    const auto cred_service(Ods::Credential_service::create(token));
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