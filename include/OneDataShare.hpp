/*
 * OneDataShare.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ONE_DATA_SHARE_INCLUDED
#define ONE_DATA_SHARE_INCLUDED

#include <string>

namespace ods {
    class OneDataShare {
        public:
            OneDataShare(const std::string ods_auth_token);
            OneDataShare(const OneDataShare&) = delete;
            OneDataShare& operator=(const OneDataShare&) = delete;
            virtual ~OneDataShare() = 0;
        protected:
            const std::string _ods_auth_token;
    };
}

#endif // ONE_DATA_SHARE_INCLUDED