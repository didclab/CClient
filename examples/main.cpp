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
#include <../simdjson/simdjson.h>

int main() {
    // parse token.txt

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

    // test code

    ods::rest::init();

    // use and print onedatashare::get with the ods /api/stork/cred api call

    typedef std::pair<std::string, std::string> spair;

    std::unordered_multimap<std::string, std::string> headers;
    headers.insert(spair("Authorization", "Bearer " + token));
    headers.insert(spair("Content-Type","application/json"));

	std::string data = R"({
		"pageNo": 0,
		"pageSize": 10,
		"sortBy": "job_id",
		"sortOrder": "desc"
	})";

    simdjson::dom::parser parser_1;
    simdjson::dom::parser parser_2;

    // get request

    ods::rest::Response get_r = ods::rest::get(url+"/api/stork/cred", headers);

    std::cout << "[=== get request headers ===]" << std::endl;
    for (auto h : get_r.headers()) {
        std::cout << "\"" << h.first << "\" -> \"" << h.second << "\"" << std::endl;
    }
    
{
    auto [get_elm, get_err] = parser_1.parse(get_r.body());

    std::cout << "[=== get request body ===]" << std::endl;
    if (!get_err) {
        if (get_elm.is<simdjson::dom::object>()) {
            for (auto [key, val] : get_elm.get<simdjson::dom::object>()) {
                std::cout << "\"" << key << "\" : \"" << val << "\"" << std::endl;
            }
        } else {
            std::cout << "Returned json not an object." << std::endl;
        }
    } else {
        std::cout << "Error parsing json: " << get_err << std::endl;
    }

    std::cout << "[=== get request http status ===]"<< std::endl;
    std::cout  << get_r.status() << std::endl;
}
    // post request

    ods::rest::Response post_r = ods::rest::post(url+"/api/stork/q/user-jobs", headers, data);

    std::cout << "[=== post request headers ===]" << std::endl;
    for (auto h : post_r.headers()) {
        std::cout << "\"" << h.first << "\" -> \"" << h.second << "\"" << std::endl;
    }

    auto [post_elm, post_err] = parser_1.parse(post_r.body());

    std::cout << "[=== post request body ===]" << std::endl;
    if (!post_err) {
        if (post_elm.is<simdjson::dom::object>()) {
            for (auto [key, val] : post_elm.get<simdjson::dom::object>()) {
                std::cout << "\"" << key << "\" : \"" << val << "\"" << std::endl;
            }
        } else {
            std::cout << "Returned json not an object." << std::endl;
        }
    } else {
        std::cout << "Error parsing json: " << post_err << std::endl;
    }

    ods::rest::cleanup();

    return 0;
}
