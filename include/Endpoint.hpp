/*
 * Endpoint.hpp
 * Andrew Mikalsen
 * 6/29/20
 */

namespace ods {
    class Endpoint {
        Endpoint();
        Endpoint(const Endpoint&) = delete;
        Endpoint& operator=(const Endpoint&) = delete;
        virtual ~Endpoint();
    };
}