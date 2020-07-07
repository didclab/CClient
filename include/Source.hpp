/**
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
    class Source {
        public:
            static std::unique_ptr<Source> create(EndpointType tyope, std::string directory_identifier, std::vector<std::string> resource_identifiers);
            virtual ~Source() = 0;
        protected:
            Source() = default;
    };
}

#endif // SOURCE_HPP_INCLUDED