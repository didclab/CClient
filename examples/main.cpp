/*
 * main.cpp
 * Andrew Mikalsen
 * 6/5/20
 */

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <../simdjson/simdjson.h>

#include <onedatashare/ods_error.h>

#include <curl_rest.h>

int main()
{
    try {
        std::string url {};
        std::string token {};

        // read token from file
        std::ifstream token_file {"token.txt"};
        if (!token_file.is_open()) {
            // print error message and exit
            std::cout
                << "Unable to open file \"token.txt\". Be sure to create a \"token.txt\" file in the project root. "
                   "See README.md for more information."
                << std::endl;
            return -1;
        }
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
        std::getline(url_file, url);
        url_file.close();

        typedef std::pair<std::string, std::string> spair;

        std::unordered_multimap<std::string, std::string> headers {};
        headers.insert(spair {"Authorization", "Bearer " + token});
        headers.insert(spair {"Content-Type", "application/json"});

        std::string data {R"({
		"pageNo": 0,
		"pageSize": 10,
		"sortBy": "job_id",
		"sortOrder": "desc"
	})"};

        simdjson::dom::parser parser {};

        One_data_share::Curl_rest rest {};

        /*
         * Get Request
         */

        One_data_share::Response get_r {rest.get(url + "/api/oauth?type=box", headers)};

        std::cout << "[=== get request headers ===]" << std::endl;
        for (auto h : get_r.headers()) {
            std::cout << "\"" << h.first << "\" -> \"" << h.second << "\"" << std::endl;
        }

        auto [get_elm, get_err] {parser.parse(get_r.body())};

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

        std::cout << "[=== get request http status ===]" << std::endl;
        std::cout << get_r.status() << std::endl;

        /*
         * Post Request
         */

        One_data_share::Response post_r {rest.post(url + "/api/stork/q/user-jobs", headers, data)};

        std::cout << "[=== post request headers ===]" << std::endl;
        for (auto h : post_r.headers()) {
            std::cout << "\"" << h.first << "\" -> \"" << h.second << "\"" << std::endl;
        }

        auto [post_elm, post_err] {parser.parse(post_r.body())};

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

        std::cout << "[=== post request http status ===]" << std::endl;
        std::cout << post_r.status() << std::endl;
    } catch (One_data_share::Connection_error e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
