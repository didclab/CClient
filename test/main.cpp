/*
 * main.cpp
 * Andrew Mikalsen
 * 6/5/20
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <curl_wrapper.hpp>

int main() {

    // open file containing url, token
    std::ifstream file("token.txt");    
    if (!file.is_open()) {
        // print error message and exit
        std::cout << "Unable to open file \"token.txt\". Be sure to create a \"token.txt\" file in the project root. "
                << "See README.md for more information."
                << std::endl;
        return -1;
    }

    // read url, token from file
    std::string url;
    std::string token;
    std::getline(file, url); // read first line
    std::getline(file, token); // read second line

    file.close();

    // use and print onedatashare::get with the ods /api/stork/cred api call
    const std::vector<std::string> headers = {
        "Authorization:Bearer " + token,
        "Content-Type:application/json"
    };
    std::cout << onedatashare::curl::get(url+"/api/stork/cred", headers) << std::endl;

    return 0;
}