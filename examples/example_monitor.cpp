/*
 * example_monitor.cpp
 * Andrew Mikalsen
 * 8/6/20
 */

#include <fstream>
#include <iostream>
#include <vector>

#include <onedatashare/onedatashare.h>

/**
 * Example of monitoring endpoint and performing transfers.
 */
int main()
{
    namespace Ods = One_data_share;

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
    const auto src_cred {""};
    const auto src_dir {"/"};

    const auto dest_type {Ods::Endpoint_type::ftp};
    const auto dest_cred {""};
    const auto dest_dir {"/"};

    const auto src_endpoint {Ods::Endpoint::create(src_type, src_cred, token, url)};
    const auto transfer {Ods::Transfer_service::create(token, url)};

    const Ods::Destination dest {dest_type, dest_cred, dest_dir};

    const auto target_file_name {""};

    try {
        while (true) {
            const auto resources {src_endpoint->list(src_dir).contained_resources};

            for (auto& r : *resources) {
                if (r.name == target_file_name) {
                    const Ods::Source src {src_type, src_cred, src_dir, std::vector {r.name}};
                    std::cout << "Starting transfer with id:" << transfer->transfer(src, dest, Ods::Transfer_options {})
                              << std::endl;
                }
            }
        }
    } catch (Ods::Unexpected_response_error e) {
        std::cout << "\nUnexpected response received from One Data Share.\n\nwhat(): " << e.what()
                  << "\n\nstatus: " << e.status << std::endl;
    } catch (Ods::Connection_error e) {
        std::cout << "\nError connecting to One Data Share.\n\nwhat(): " << e.what() << std::endl;
    }
}