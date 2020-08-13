/*
 * example_transfer.cpp
 * Andrew Mikalsen
 * 7/27/20
 */

#include <fstream>
#include <iostream>
#include <vector>

#include <onedatashare/onedatashare.h>

/**
 * Example of performing transfers.
 */
int main()
{
    namespace Ods = Onedatashare;

    // read token from file
    std::ifstream token_file {"token.txt"};
    if (!token_file.is_open()) {
        // print error message and exit
        std::cout << "Unable to open file \"token.txt\". Be sure to create a \"token.txt\" file in the project root. "
                     "See README.md for more information."
                  << std::endl;
        return -1;
    }

    std::string token {};
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

    std::string url {};
    std::getline(url_file, url);

    url_file.close();

    const auto src_type {Ods::Endpoint_type::ftp};
    const auto src_credential {""};
    const auto src_directory {""};
    const std::vector<std::string> src_resources {"", "", ""};

    const auto dest_type {Ods::Endpoint_type::sftp};
    const auto dest_credential {""};
    const auto dest_directory {""};

    const auto transfer {Ods::Transfer_service::create(token, url)};

    Ods::Source src {src_type, src_credential, src_directory, src_resources};
    Ods::Destination dest {dest_type, dest_credential, dest_directory};
    Ods::Transfer_options opt {};

    try {
        const auto id {transfer->transfer(src, dest, opt)};
        std::cout << id << std::endl;

    } catch (Ods::Unexpected_response_error e) {
        std::cout << "\nUnexpected response received from One Data Share.\n\nwhat(): " << e.what()
                  << "\n\nstatus: " << e.status << std::endl;
    } catch (Ods::Connection_error e) {
        std::cout << "\nError connecting to One Data Share.\n\nwhat(): " << e.what() << std::endl;
    }
}