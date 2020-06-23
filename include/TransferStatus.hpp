/*
 * TransferStatus.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef TRANSFER_STATUS_INCLUDED
#define TRANSFER_STATUS_INCLUDED

namespace ods {
    //TODO: define
    class TransferStatus {
        public:
            TransferStatus(const TransferStatus&) = delete;
            TransferStatus& operator=(const TransferStatus&) = delete;
        private:
            TransferStatus();
    };
}

#endif // TRANSFER_STATUS_INCLUDED