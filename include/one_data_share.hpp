/*
 * one_data_share.hpp
 * Andrew Mikalsen
 * 6/18/20
 */

#ifndef ONE_DATA_SHARE_INCLUDED
#define ONE_DATA_SHARE_INCLUDED

#include <string>
#include <rest.hpp>

namespace ods {
    class OneDataShare {
        public:
            /**
             * Creates a new object with the specified authentication token.
             * 
             * @param ods_auth_token authentication token used to make requests to One Data Share
             */
            OneDataShare(const std::string ods_auth_token);
            OneDataShare(const OneDataShare&) = delete;
            OneDataShare& operator=(const OneDataShare&) = delete;
            virtual ~OneDataShare() = 0;
        private:
            /**
             * Authentication token used to make requests to One Data Share.
             */
            const std::string _ods_auth_token;
    };

    class Transfer: public OneDataShare {
        public:
            /**
             * Performs the specified transfer request.
             * 
             * @param request the transfer request to perform
             * 
             * @return string corresponding to the id of the request
             */
            std::string transfer(const TransferRequest request) const;
            /**
             * Retrieves the status of the transfer with the specified id.
             * 
             * @return a <code>TransferStatus<code> object with the status of the specified transfer
             */
            TransferStatus get_transfer_status(const std::string id) const;
            virtual ~Transfer() override;
    };

    class Endpoint: public OneDataShare {
        public:
            /**
             * Returns an <code>Item</code> corresponding to the item found at the root of the endpoint.
             */
            virtual Item resolve() const = 0;
            /**
             * Returns an <code>Item</code> corresponding to the item found at the specified path.
             */
            virtual Item resolve(const std::string path) const = 0;
    };

    class Dropbox: public Endpoint {
        public:
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~Dropbox() override;
    };

    class Box: public Endpoint {
        public:
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~Box() override;
    };

    class GoogleDrive: public Endpoint {
        public:
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~GoogleDrive() override;
    };

    class GridFTP: public Endpoint {
        public:
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~GridFTP() override;
    };

    class FTP: public Endpoint {
        public:
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~FTP() override;
    };

    class SFTP: public Endpoint {
        public:
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~SFTP() override;
    };

    class HTTP: public Endpoint {
        public:
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~HTTP() override;
    };

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

    class TransferStatus {
        //TODO: define members
        public:
            TransferStatus(const TransferStatus&) = delete;
            TransferStatus& operator=(const TransferStatus&) = delete;
        private:
            TransferStatus();
    };

    class Item {
        public:
            Item(const Item&) = delete;
            Item& operator=(const Item&) = delete;
        private:
            Item();
    };

    class AccountEndpointCredential {
        public:
            AccountEndpointCredential();
            AccountEndpointCredential(const AccountEndpointCredential&) = delete;
            AccountEndpointCredential& operator=(const AccountEndpointCredential&) = delete;
        private:
    };

    class Source {
        public:
            Source();
            Source(const Source&) = delete;
            Source& operator=(Source&) = delete;
        private:
    };

    class Destination {
        public:
            Destination();
            Destination(const Destination&) = delete;
            Destination& operator=(const Destination&) = delete;
        private:
    };

    class TransferOptions {
        public:
            TransferOptions();
            TransferOptions(const TransferOptions&) = delete;
            TransferOptions& operator=(const TransferOptions&) = delete;
    };
}

#endif // ONE_DATA_SHARE_INCLUDED