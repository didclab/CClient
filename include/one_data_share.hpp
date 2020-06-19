/*
 * one_data_share.hpp
 * Andrew Mikalsen
 * 6/18/20
 */

#ifndef ONE_DATA_SHARE_INCLUDED
#define ONE_DATA_SHARE_INCLUDED

namespace ods {
    class OneDataShare {
        public:
        private:
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