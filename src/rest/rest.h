/*
 * rest.h
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef ONEDATASHARE_REST_H
#define ONEDATASHARE_REST_H

#include <unordered_map>
#include <string>
#include "response.h"

namespace One_data_share {
	/**
	 * Class used to perform REST requests.
	 */
	class Rest {
	public:
		/**
		 * Performs a GET request to the specified url with the
		 * specified headers.
		 * 
		 * @param url borrowed reference to the string containing url to
		 * make the GET request to. Should ideally contain the protocol
		 * @param headers borrowed reference to the multi-map containing
		 * the headers for the GET request
		 * 
		 * @return the Response object containing the response headers,
		 * body, and http status
		 * 
		 * @exception IO_error if unable to connect to the sepcified
		 * url
		 */
		virtual Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers) const = 0;

		/**
		 * Performs a POST request to the specified url with the
		 * specified headers and data.
		 * 
		 * @param url borrowed reference to the string containing the
		 * url to make the POST request to, ideally containing the
		 * protocol
		 * @param headers borrowed reference to the multi-map containing
		 * the headers for the POST request
		 * @param data borrowed reference to the string containing the
		 * json data for the POST request
		 * 
		 * @return the Response object containing the response headers,
		 * body, and http status
		 * 
		 * @exception IO_error if unable to connect to the sepcified
		 * url
		 */
		virtual Response post(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers, const std::string& data) const = 0;

		virtual ~Rest() = 0;

		Rest(const Rest&) = delete;
		Rest& operator=(const Rest&) = delete;

	protected:
		Rest();
	};
}

#endif // ONEDATASHARE_REST_H
