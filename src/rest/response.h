/*
 * response.h
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ONEDATASHARE_RESPONSE_H
#define ONEDATASHARE_RESPONSE_H

#include <string>
#include <unordered_map>

namespace One_data_share {
    /**
     * Class holding the response from a request made via the get or post
     * functions. Fields of this object live only as long as the object
     * itself.
     */
    class Response {
    public:
        /**
         * Creates a new Response object.
         * 
         * @param headers multi-map containing the response headers
         * @param body json string containing the response body
         * @param status integer corresponding to the http response
         * status
         */
        Response(std::unordered_multimap<std::string, std::string> headers, std::string body, int status);

        /**
         * Gets a reference to the response headers. The returned
         * reference lives only as long as the object itself.
         * 
         * @return a temporary reference to the response headers stored
         * as (key, value) pairs in an unordered multi-map
         */
        const std::unordered_multimap<std::string, std::string>& headers() const;

        /**
         * Gets a reference to the response body. The returned reference
         * lives only as long as the object itself.
         * 
         * @return a temporary reference to the json string containing
         * the response body
         */
        const std::string& body() const;

        /**
         * Gets a reference to the http response status. The returned
         * reference lives only as long as the object itself.
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
}

#endif // ONEDATASHARE_RESPONSE_H