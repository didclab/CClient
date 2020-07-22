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
#include <onedatashare/ods_error.h>

/**
 * Example registering a new FTP endpoint and listing the contents of the root directory of that endpoint.
 */
int main()
{
    namespace Ods = One_data_share;

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

    const auto my_cred_id {"my_endpoint"};
    const auto cred_service {Ods::Credential_service::create(token)};

    try {
        // register new endpoint
        std::cout << "Registering new endpoint with credential id " << my_cred_id << " ..." << std::endl;

        cred_service->register_credential(Ods::Credential_endpoint_type::ftp,
                                          my_cred_id,
                                          "ftp://speedtest.tele2.net",
                                          nullptr,
                                          nullptr);

        std::cout << "Endpoint registered.\n" << std::endl;

        std::cout << "Printing root of " << my_cred_id << " ...\n" << std::endl;

        // print root of new endpoint
        const auto root_path {"/"};
        const auto my_endpoint {Ods::Endpoint::create(Ods::Endpoint_type::ftp, my_cred_id, token)};
        const auto root {my_endpoint->list(root_path)};
        if (root->is_directory()) {
            for (auto r : *root->contained_resources()) {
                std::cout << r->name() << std::endl;
            }
        }

        std::cout << "\nRoot printed." << std::endl;

    } catch (Ods::Unexpected_response_error e) {
        std::cout << "\nUnexpected response received from One Data Share.\n\nwhat(): " << e.what()
                  << "\n\nstatus: " << e.status << std::endl;
    } catch (Ods::Connection_error e) {
        std::cout << "\nError connecting to One Data Share.\n\nwhat(): " << e.what() << std::endl;
    }

    return 0;
}