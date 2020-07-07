/*
 * TransferOptions.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef TRANSFER_OPTIONS_HPP_INCLUDED
#define TRANSFER_OPTIONS_HPP_INCLUDED

namespace ods {

    // TODO: define
    class TransferOptions {
        public:
            virtual ~TransferOptions() = 0;
        protected:
            TransferOptions() = default;
    };
}

#endif // TRANSFER_OPTIONS_HPP_INCLUDED