/*
 * Endpoint.hpp
 * Andrew Mikalsen
 * 6/29/20
 */

#ifndef ENDPOINT_HPP_INCLUDED
#define ENDPOINT_HPP_INCLUDED

namespace ods {
    /**
     * Connection to a One Data Share endpoint.
     */
    class Endpoint {
        Endpoint() = default;
        Endpoint(const Endpoint&) = delete;
        Endpoint& operator=(const Endpoint&) = delete;
        virtual ~Endpoint() = 0;
    };
}

#endif // ENDPOINT_HPP_INCLUDED