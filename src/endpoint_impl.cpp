/*
 * endpoint_impl.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include "endpoint_impl.h"

namespace One_data_share {
    std::unique_ptr<Resource> Endpoint_impl::list(const std::string& identifier) const
    {
        // TODO: implement
        return nullptr;
    }

    void Endpoint_impl::remove(const std::string& identifier, const std::string& to_delete) const
    {
        // TODO: implement
    }

    void Endpoint_impl::mkdir(const std::string& identifier, const std::string& folder_to_create) const
    {
        // TODO: implement
    }

    void Endpoint_impl::download(const std::string& identifier, const std::string& file_to_download) const
    {
        // TODO: implement
    }
}