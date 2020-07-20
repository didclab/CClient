/*
 * resource_impl.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include "resource_impl.h"

namespace One_data_share {
    Resource_impl Resource_impl::from(const std::string& json)
    {
        // TODO: implement
    }

    Resource_impl::Resource_impl(
        std::shared_ptr<const std::string>&& id,
        std::string&& name,
        long size,
        long time,
        bool is_directory,
        bool is_file,
        std::shared_ptr<const std::string>&& link,
        std::shared_ptr<const std::string>&& permissions,
        std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>>&& contained_resources)
        : id_(id),
          name_(name),
          size_(size),
          time_(time),
          is_directory_(is_directory),
          is_file_(is_file),
          link_(link),
          permissions_(permissions),
          contained_resources_(contained_resources)
    {}

    std::shared_ptr<const std::string> Resource_impl::id() const
    {
        // TODO: implement
        return nullptr;
    }

    std::string Resource_impl::name() const
    {
        // TODO: implement
        return nullptr;
    }

    long Resource_impl::size() const
    {
        // TODO: implement
        return 0;
    }

    long Resource_impl::time() const
    {
        // TODO: implement
        return 0;
    }

    bool Resource_impl::is_directory() const
    {
        // TODO: implement
        return false;
    }

    bool Resource_impl::is_file() const
    {
        // TODO: implement
        return false;
    }

    std::shared_ptr<const std::string> Resource_impl::link() const
    {
        // TODO: implement
        return nullptr;
    }

    std::shared_ptr<const std::string> Resource_impl::permissions() const
    {
        // TODO: implement
        return nullptr;
    }

    std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> Resource_impl::contained_resources() const
    {
        // TODO: implement
        return nullptr;
    }
}