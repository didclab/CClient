/*
 * TransferRequest.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef TRANSFER_REQUEST_HPP_INCLUDED
#define TRANSFER_REQUEST_HPP_INCLUDED

#include <Source.hpp>
#include <Destination.hpp>
#include <TransferOptions.hpp>

namespace ods {
    class TransferRequest {
        public:
            TransferRequest(const Source source, const Destination destination, const TransferOptions transfer_options, const int priority);
            TransferRequest(const TransferRequest&) = delete;
            TransferRequest& operator=(const TransferRequest&) = delete;
            Source source() const;
            Destination destination() const;
            TransferOptions options() const;
            int priority() const;
        private:
            const Source _source;
            const Destination _destination;
            const TransferOptions _options;
            const int _priority;
    };
}

#endif // TRANSFER_REQUEST_HPP_INCLUDED