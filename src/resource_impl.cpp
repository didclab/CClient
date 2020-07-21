/*
 * resource_impl.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include "resource_impl.h"

namespace One_data_share {

Resource_impl::Resource_impl(std::shared_ptr<const std::string>&& id,
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
    return id_;
}

std::string Resource_impl::name() const
{
    return name_;
}

long Resource_impl::size() const
{
    return size_;
}

long Resource_impl::time() const
{
    return time_;
}

bool Resource_impl::is_directory() const
{
    return is_directory_;
}

bool Resource_impl::is_file() const
{
    return is_file_;
}

std::shared_ptr<const std::string> Resource_impl::link() const
{
    return link_;
}

std::shared_ptr<const std::string> Resource_impl::permissions() const
{
    return permissions_;
}

std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> Resource_impl::contained_resources() const
{
    return contained_resources_;
}

} // namespace One_data_share