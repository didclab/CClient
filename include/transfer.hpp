/*
 * transfer.hpp
 * Andrew Mikalsen
 * 6/18/20
 */

#ifndef TRANSFER_INCLUDED
#define TRANSFER_INCLUDED

namespace ods {
    /**
     * Used to initialize and check the status of transfers.
     */
    class Transfer {
        public:
            /**
             * Creates a new <code>Transfer</code> object.
             */
            Transfer();
            Transfer(const Transfer&) = delete;
            Transfer& operator=(const Transfer&) = delete;

            // TODO: finish definition
    };
}

#endif // TRANSFER_INCLUDED