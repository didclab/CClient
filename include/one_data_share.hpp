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
            OneDataShare(std::string ods_auth_token);
            OneDataShare(const OneDataShare&) = delete;
            OneDataShare& operator=(const OneDataShare&) = delete;
            virtual ~OneDataShare() = 0;
        private:
            /**
             * Authentication token used to make requests to One Data Share.
             */
            std::string ods_auth_token;
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
            std::string transfer(TransferRequest request);
            /**
             * Retrieves the status of the transfer with the specified id.
             * 
             * @return a <code>TransferStatus<code> object with the status of the specified transfer
             */
            TransferStatus get_transfer_status(std::string id);
            virtual ~Transfer() override;
    };

    class Endpoint: public OneDataShare {
        public:
            /**
             * Returns an <code>Item</code> corresponding to the item found at the root of the endpoint.
             */
            virtual Item resolve() = 0;
            /**
             * Returns an <code>Item</code> corresponding to the item found at the specified path.
             */
            virtual Item resolve(std::string path) = 0;
    };

    class Dropbox: public Endpoint {
        public:
            void add();
            virtual Item resolve() override;
            virtual Item resolve(std::string path) override;
            virtual ~Dropbox() override;
    };

    class Box: public Endpoint {
        public:
            void add();
            virtual Item resolve() override;
            virtual Item resolve(std::string path) override;
            virtual ~Box() override;
    };

    class GoogleDrive: public Endpoint {
        public:
            void add(AccountEndpointCredential cred);
            virtual Item resolve() override;
            virtual Item resolve(std::string path) override;
            virtual ~GoogleDrive() override;
    };

    class GridFTP: public Endpoint {
        public:
            void add();
            virtual Item resolve() override;
            virtual Item resolve(std::string path) override;
            virtual ~GridFTP() override;
    };

    class FTP: public Endpoint {
        public:
            void add(AccountEndpointCredential cred);
            virtual Item resolve() override;
            virtual Item resolve(std::string path) override;
            virtual ~FTP() override;
    };

    class SFTP: public Endpoint {
        public:
            void add(AccountEndpointCredential cred);
            virtual Item resolve() override;
            virtual Item resolve(std::string path) override;
            virtual ~SFTP() override;
    };

    class HTTP: public Endpoint {
        public:
            virtual Item resolve() override;
            virtual Item resolve(std::string path) override;
            virtual ~HTTP() override;
    };

    class TransferRequest {
        public:
            TransferRequest(Source source, Destination destination, TransferOptions transfer_options, int priority);
            TransferRequest(const TransferRequest&) = delete;
            TransferRequest& operator=(const TransferRequest&) = delete;
            Source source();
            Destination destination();
            TransferOptions options();
            int priority();
        private:
            Source _source;
            Destination _destination;
            TransferOptions _options;
            int _priority;
    };

    class TransferStatus {
        public:
        private:
    };

    class Item {
        public:
        private:
    };

    class AccountEndpointCredential {
        public:
        private:
    };

    class Source {

    };

    class Destination {

    };

    class TransferOptions {

    };
}

#endif // ONE_DATA_SHARE_INCLUDED