/*
 * TransferOptions.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef TRANSFER_OPTIONS_HPP_INCLUDED
#define TRANSFER_OPTIONS_HPP_INCLUDED

namespace ods {
    // TODO: define
    class TransferOptions {
        public:
            TransferOptions();
            TransferOptions(const TransferOptions&) = delete;
            TransferOptions& operator=(const TransferOptions&) = delete;
    };
}

#endif // TRANSFER_OPTIONS_HPP_INCLUDED