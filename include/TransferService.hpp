/*
 * TransferService.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef TRANSFER_SERVICE_HPP_INCLUDED
#define TRANSFER_SERVICE_HPP_INCLUDED

namespace ods {
    class TransferService{
        public:
            virtual ~TransferService() = 0;
        protected:
            TransferService() = default;
    };
}

#endif // TRANSFER_SERVICE_HPP_INCLUDED