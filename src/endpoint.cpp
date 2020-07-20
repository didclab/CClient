/*
 * endpoint.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <onedatashare/endpoint.h>

namespace One_data_share {

    Resource::Resource() = default;

    Resource::~Resource() = default;

    std::shared_ptr<const std::string> Resource::id() const
    {
        // TODO: implement
        return nullptr;
    }

    std::string Resource::name() const
    {
        // TODO: implement
        return nullptr;
    }

    long Resource::size() const
    {
        // TODO: implement
        return 0;
    }

    long Resource::time() const
    {
        // TODO: implement
        return 0;
    }

    bool Resource::is_directory() const
    {
        // TODO: implement
        return false;
    }

    bool Resource::is_file() const
    {
        // TODO: implement
        return false;
    }

    std::shared_ptr<const std::string> Resource::link() const
    {
        // TODO: implement
        return nullptr;
    }

    std::shared_ptr<const std::string> Resource::permissions() const
    {
        // TODO: implement
        return nullptr;
    }

    std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> Resource::contained_resources() const
    {
        // TODO: implement
        return nullptr;
    }

}