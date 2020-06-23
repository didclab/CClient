/*
 * GoogleDrive.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef GOOGLE_DRIVE_INCLUDED
#define GOOGLE_DRIVE_INCLUDED

#include <Endpoint.hpp>

namespace ods {
    class GoogleDrive: public Endpoint {
        public:
            GoogleDrive(const std::string ods_auth_token);
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~GoogleDrive() override = default;
    };
}

#endif // GOOGLE_DRIVE_INCLUDED