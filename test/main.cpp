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

    ods::curl::init();

    // use and print onedatashare::get with the ods /api/stork/cred api call

    const std::vector<std::string> headers = {
        "Authorization:Bearer " + token,
        "Content-Type:application/json"
    };

    ods::curl::Response r = ods::curl::get(url+"/api/stork/cred", headers);

    for (std::pair<std::string, std::string> h : r.headers()) {
		std::cout << "\"" << h.first << "\" -> \"" << h.second << "\"" << std::endl;
	}

	for (auto [key, val] : r.body()) {
		std::cout << key << " : " << val << std::endl;
	}

    std::cout << r.body()["6a0db95f-cbc6-43b9-8045-460286bfd0da"]["type"] << std::endl;

	std::cout << r.status() << std::endl;

    ods::curl::cleanup();

    return 0;
}
