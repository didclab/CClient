/*
 * GridFTP.spp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef GRID_FTP_INCLUDED
#define GRID_FTP_INCLUDED

#include <Endpoint.hpp>

namespace ods {
    class GridFTP: public Endpoint {
        public:
            GridFTP(const std::string ods_auth_token);
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~GridFTP() override = default;
    };
}

#endif // GRID_FTP_INCLUDED