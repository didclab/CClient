/*
 * Source.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef SOURCE_HPP_INCLUDED
#define SOURCE_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include <EndpointType.hpp>

namespace ods {
    /**
     * Indicates the source endpoint of a transfer.
     */
    class Source {
        public:
            /**
             * Creates a new Source object with the specified endpoint and
             * resources.
             * 
             * @param type the endpoint type to transfer from
             * @param cred_id the credential identifier of the endpoint to
             * transfer from
             * @param directory_identifier the path or id, depending on the
             * endpoint type, that is needed in order to locate the directory
             * containing the resources to transfer
             * @param resource_identifiers the names or ids, depending on the
             * endpoint type, that are needed in order to locate the resources
             * to transfer from within the specified directory
             * 
             * @return a unique pointer to a new Source object
             */
            static std::unique_ptr<Source> create(const EndpointType type, const std::string cred_id, const std::string directory_identifier, const std::vector<std::string> resource_identifiers);

            virtual ~Source() = 0;
        protected:
            Source() = default;
    };
}

#endif // SOURCE_HPP_INCLUDED