/*
 * Destination.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef DESTINATION_HPP_INCLUDED
#define DESTINATION_HPP_INCLUDED

#include <memory>
#include <string>
#include <EndpointType.hpp>

namespace ods {
    /**
     * indicates the destination endpoint of a transfer.
     */
    class Destination {
        public:
            /**
             * Creates a new Destination object with the specified endpoint and
             * directory.
             * 
             * @param type the endpoint type to transfer to
             * @param cred_id the credential identifier of the endpoint to
             * transfer to
             * @param directory_identifier the path or id, depending on the
             * endpoint type, that is needed in order to locate the directory
             * in which the transfered resources should be placed
             * 
             * @return a unique pointer to the Destination object
             */
            static std::unique_ptr<Destination> create(EndpointType type, std::string cred_id, std::string directory_identifier);

            virtual ~Destination() = 0;
        protected:
            Destination() = default;
    };
}

#endif // DESTINATION_HPP_INCLUDED