/*
 * one_data_share.hpp
 * Andrew Mikalsen
 * 6/18/20
 */

#ifndef ONE_DATA_SHARE_INCLUDED
#define ONE_DATA_SHARE_INCLUDED

#include <string>
#include <unordered_set>
#include <vector>
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
            virtual ~Transfer() override = default;
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
            virtual ~Dropbox() override = default;
    };

    class Box: public Endpoint {
        public:
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~Box() override = default;
    };

    class GoogleDrive: public Endpoint {
        public:
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~GoogleDrive() override = default;
    };

    class GridFTP: public Endpoint {
        public:
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~GridFTP() override = default;
    };

    class FTP: public Endpoint {
        public:
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~FTP() override = default;
    };

    class SFTP: public Endpoint {
        public:
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~SFTP() override = default;
    };

    class HTTP: public Endpoint {
        public:
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~HTTP() override = default;
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

    //TODO: define members
    class TransferStatus {
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
            Item list() const;
            bool remove() const;
            void download() const;
            bool mkdir(const std::string directory_name);
        private:
            // TODO: write constructor
            Item();
            const std::string _item;
            const std::string _name;
            const long _size;
            const FileType _type;
            const std::string _link;
            const std::string _permissions;
            const std::vector<Item> _files_list;
    };

    class AccountEndpointCredential {
        public:
            AccountEndpointCredential(const std::string account_id, const std::string uri, const std::string username, const std::string secret);
            AccountEndpointCredential(const AccountEndpointCredential&) = delete;
            AccountEndpointCredential& operator=(const AccountEndpointCredential&) = delete;
            std::string account_id();
            std::string uri();
            std::string username();
            std::string secret();
        private:
            const std::string _account_id;
            const std::string _uri;
            const std::string _username;
            const std::string _secret;
    };

    class Source {
        public:
            Source(const EndpointType type, const std::string cred_id, const std::vector<Item> items);
            Source(const EndpointType type, const std::string cred_id, const Item item);
            Source(const Source&) = delete;
            Source& operator=(const Source&) = delete;
            EndpointType type();
            std::string cred_id();
            ItemInfo info();
            std::unordered_set<ItemInfo> info_list();
        private:
            const EndpointType _type;
            const std::string _cred_id;
            const ItemInfo _info;
            const std::unordered_set<ItemInfo> _info_list;
    };

    class Destination {
        public:
            Destination(const EndpointType type, const std::string cred_id, const Item item);
            Destination(const Destination&) = delete;
            Destination& operator=(const Destination&) = delete;
            EndpointType type();
            std::string cred_id();
            ItemInfo info();
        private:
            const EndpointType _type;
            const std::string _cred_id;
            const ItemInfo _info;
    };

    // TODO: define members
    class TransferOptions {
        public:
            TransferOptions();
            TransferOptions(const TransferOptions&) = delete;
            TransferOptions& operator=(const TransferOptions&) = delete;
        private:
    };

    // TODO: define members
    class ItemInfo {
        public:
            ItemInfo(const ItemInfo&) = delete;
            ItemInfo& operator=(const ItemInfo&) = delete;
            std::string id();
            std::string path();
            long size();
        private:
            ItemInfo(const std::string id, const std::string path, const std::string size);
            const std::string _id;
            const std::string _path;
            const long _size;
    };
    
    enum class FileType {
        LINK, FILE, DIRECTORY
    };

    enum class EndpointType {
        DROPBOX, GOOGLE_DRIVE, SFTP, FTP, BOX, GFTP, HTTP
    };
}

#endif // ONE_DATA_SHARE_INCLUDED