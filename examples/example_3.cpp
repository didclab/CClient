/*
 * example_3.cpp
 * Andrew Mikalsen
 * 7/27/20
 */

#include <fstream>
#include <iostream>
#include <vector>

#include <onedatashare/endpoint_type.h>
#include <onedatashare/transfer_service.h>

#include <onedatashare/ods_error.h>

/**
 * Example of performing transfers.
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

    const auto src_type {Ods::Endpoint_type::ftp};
    const auto src_credential {""};
    const auto src_directory {""};
    const std::vector<std::string> src_resources {"", "", ""};

    const auto dest_type {Ods::Endpoint_type::sftp};
    const auto dest_credential {""};
    const auto dest_directory {""};

    const auto transfer {Ods::Transfer_service::create(token)};

    const auto src {Ods::Source::create(src_type, src_credential, src_directory, src_resources)};
    const auto dest {Ods::Destination::create(dest_type, dest_credential, dest_directory)};
    const auto opt {Ods::Transfer_options::create()};

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