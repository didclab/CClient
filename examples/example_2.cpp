/*
 * example_2.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include <fstream>
#include <iostream>

#include <onedatashare/credential_service.h>
#include <onedatashare/ods_error.h>

/**
 * Example giving the user a link to use for registering an OAuth endpoint.
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

    auto cred {Ods::Credential_service::create(token)};

    try {
        std::cout << "Register Box Endpoint:" << std::endl
                  << cred->oauth_url(Ods::Oauth_endpoint_type::box) << "\n"
                  << std::endl;

        std::cout << "Register Dropbox Endpoint:" << std::endl
                  << cred->oauth_url(Ods::Oauth_endpoint_type::dropbox) << "\n"
                  << std::endl;

        std::cout << "Register GFTP Endpoint:" << std::endl
                  << cred->oauth_url(Ods::Oauth_endpoint_type::gftp) << "\n"
                  << std::endl;

        std::cout << "Register Google Drive Endpoint:" << std::endl
                  << cred->oauth_url(Ods::Oauth_endpoint_type::google_drive) << std::endl;

    } catch (Ods::Unexpected_response_error e) {
        std::cout << "\nUnexpected response received from One Data Share.\n\nwhat(): " << e.what()
                  << "\n\nstatus: " << e.status << std::endl;
    } catch (Ods::Connection_error e) {
        std::cout << "\nError connecting to One Data Share.\n\nwhat(): " << e.what() << std::endl;
    }
}