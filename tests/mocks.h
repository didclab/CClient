/*
 * mocks.h
 * Andrew Mikalsen
 * 7/20/20
 */

#ifndef ONEDATASHARE_MOCKS_H
#define ONEDATASHARE_MOCKS_H

#include <gmock/gmock.h>

#include <rest.h>

namespace One_data_share_mocks {
    namespace Ods = One_data_share;

    class Rest_mock : public Ods::Rest {
        using Header_map = std::unordered_multimap<std::string, std::string>;

    public:
        MOCK_METHOD(Ods::Response, get, (const std::string& url, const Header_map& headers), (const, override));
        MOCK_METHOD(Ods::Response,
                    post,
                    (const std::string& url, const Header_map& headers, const std::string& data),
                    (const, override));
    };
}

#endif // ONEDATASHARE_MOCKS_H