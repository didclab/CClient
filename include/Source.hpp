/**
 * Source.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef SOURCE_HPP_INCLUDED
#define SOURCE_HPP_INCLUDED

namespace ods {
    class Source {
        public:
            virtual ~Source() = 0;
        protected:
            Source() = default
    };
}

#endif // SOURCE_HPP_INCLUDED