/*
 * Destination.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef DESTINATION_HPP_INCLUDED
#define DESTINATION_HPP_INCLUDED

namespace ods {
    class Destination {
        public:

            virtual ~Destination() = 0;
        protected:
            Destination() = default;
    };
}

#endif // DESTINATION_HPP_INCLUDED