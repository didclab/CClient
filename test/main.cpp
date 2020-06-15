/*
 * main.cpp
 * Andrew Mikalsen
 * 6/5/20
 */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <curl_wrapper.hpp>

int main() {

    /*
    Read token.txt
    */

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

    /*
    Test code
    */

    ods::rest::init();

    // use and print onedatashare::get with the ods /api/stork/cred api call

    typedef std::pair<std::string, std::string> spair;
    
    std::unordered_multimap<std::string, std::string> headers;
    headers.insert(spair("Authorization", "Bearer " + token));
    headers.insert(spair("Content-Type","application/json"));

    ods::rest::Response r = ods::rest::get(url+"/api/stork/cred", headers);

    for (std::pair<std::string, std::string> h : r.headers()) {
		std::cout << "\"" << h.first << "\" -> \"" << h.second << "\"" << std::endl;
	}

    if (r.body().has_value()) {
        for (auto [key, val] : r.body().value()) {
            std::cout << key << " : " << val << std::endl;
        }
    }

	std::cout << r.status() << std::endl;

    ods::rest::cleanup();

    return 0;
}
