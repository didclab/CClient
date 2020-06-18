/*
 * one_data_share.hpp
 * Andrew Mikalsen
 * 6/18/20
 */

#ifndef ONE_DATA_SHARE_INCLUDED
#define ONE_DATA_SHARE_INCLUDED

#include <string>
#include "transfer.hpp"

namespace ods {
    /**
     * Enables the instantiation of endpoints and initialization of transfers.
     * 
     * This class is the main entry point to the One Data Share client. Any available functionality from One Data Share
     * is provided through an instance of this class.
     */
    class OneDataShare {

        public:
            /**
             * Creates a new <code>OneDataShare</code> instance with the specified token. The token must be obtained from the One Data
             * Share website.
             * 
             * @param token JWT token used to authenticate with One Data Share
             */
            OneDataShare(std::string token);
            OneDataShare(const OneDataShare&) = delete;
            OneDataShare& operator=(const OneDataShare&) = delete;

            Transfer transfer();
    };
}

#endif // ONE_DATA_SHARE_INCLUDED