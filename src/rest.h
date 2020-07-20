/*
 * rest.h
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef ONEDATASHARE_REST_H
#define ONEDATASHARE_REST_H

#include <string>
#include <unordered_map>

namespace One_data_share {

    /**
     * Class holding the response from a request made via the get or post functions. Fields of this object live only as
     * long as the object itself.
     */
    class Response {
    public:
        /**
         * Creates a new Response object.
         *
         * @param headers borrowed reference to the multi-map containing the response headers
         * @param body borrowed reference to the json string containing the response body
         * @param status integer corresponding to the http response status
         */
        Response(const std::unordered_multimap<std::string, std::string>& headers, const std::string& body, int status);

        Response(const Response&) = default;

        Response& operator=(const Response&) = default;

        Response(Response&&) = default;

        Response& operator=(Response&&) = default;

        /**
         * Gets a reference to the response headers. The returned reference lives only as long as the object itself.
         *
         * @return a temporary reference to the response headers stored as (key, value) pairs in an unordered multi-map
         */
        const std::unordered_multimap<std::string, std::string>& headers() const;

        /**
         * Gets a reference to the response body. The returned reference lives only as long as the object itself.
         *
         * @return a temporary reference to the json string containing the response body
         */
        const std::string& body() const;

        /**
         * Gets a reference to the http response status. The returned reference lives only as long as the object itself.
         *
         * @return a temporary reference to the http response status
         */
        int status() const;

    private:
        /**
         * Multi-map storing headers as (key, value) pairs.
         */
        const std::unordered_multimap<std::string, std::string> headers_;

        /**
         * Json string containing the response body.
         */
        const std::string body_;

        /**
         * The http response status code.
         */
        const int status_;
    };

    /**
     * Class used to perform REST requests.
     */
    class Rest {
    public:
        virtual ~Rest() = 0;

        Rest(const Rest&) = delete;

        Rest& operator=(const Rest&) = delete;

        Rest(Rest&&) = default;

        Rest& operator=(Rest&&) = default;

        /**
         * Performs a GET request to the specified url with the specified headers.
         *
         * @param url borrowed reference to the string containing url to make the GET request to, ideally containing the
         * protocol
         * @param headers borrowed reference to the multi-map containing the headers for the GET request
         *
         * @return the Response object containing the response headers, body, and http status
         *
         * @exception Connection_error if unable to connect to the sepcified url
         */
        virtual Response get(const std::string& url,
                             const std::unordered_multimap<std::string, std::string>& headers) const = 0;

        /**
         * Performs a POST request to the specified url with the specified headers and data.
         *
         * @param url borrowed reference to the string containing the url to make the POST request to, ideally
         * containing the protocol
         * @param headers borrowed reference to the multi-map containing the headers for the POST request
         * @param data borrowed reference to the string containing the json data for the POST request
         *
         * @return the Response object containing the response headers, body, and http status
         *
         * @exception Connection_error if unable to connect to the sepcified url
         */
        virtual Response post(const std::string& url,
                              const std::unordered_multimap<std::string, std::string>& headers,
                              const std::string& data) const = 0;

    protected:
        Rest();
    };
}

#endif // ONEDATASHARE_REST_H
