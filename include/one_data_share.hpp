/*
 * one_data_share.hpp
 * Andrew Mikalsen
 * 6/18/20
 */

#ifndef ONE_DATA_SHARE_INCLUDED
#define ONE_DATA_SHARE_INCLUDED

#include <string>

namespace ods {
    class OneDataShare {
        public:
            /**
             * Create a new object with the specified authentication token.
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
        private:
    };

    class Endpoint: public OneDataShare {
        public:
        private:
    };

    class Dropbox: public Endpoint {
        public:
        private:
    };

    class Box: public Endpoint {
        public:
        private:
    };

    class GoogleDrive: public Endpoint {
        public:
        private:
    };

    class GridFTP: public Endpoint {
        public:
        private:
    };

    class FTP: public Endpoint {
        public:
        private:
    };

    class SFTP: public Endpoint {
        public:
        private:
    };

    class HTTP: public Endpoint {
        public:
        private:
    };
}

#endif // ONE_DATA_SHARE_INCLUDED