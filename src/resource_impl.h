/*
 * resource_impl.h
 * Andrew Mikalsen
 * 7/20/20
 */

#ifndef ONEDATASHARE_RESOURCE_IMPL_H
#define ONEDATASHARE_RESOURCE_IMPL_H

#include <memory>
#include <string>
#include <vector>

#include <onedatashare/endpoint.h>

namespace One_data_share {

    class Resource_impl : public Resource {
    public:
        static Resource_impl from(const std::string& json);

        virtual ~Resource_impl() = default;

        Resource_impl(const Resource_impl&) = delete;

        Resource_impl& operator=(const Resource_impl&) = delete;

        Resource_impl(Resource_impl&&) = default;

        Resource_impl& operator=(Resource_impl&&) = default;

        virtual std::shared_ptr<const std::string> id() const;

        virtual std::string name() const;

        virtual long size() const;

        virtual long time() const;

        virtual bool is_directory() const;

        virtual bool is_file() const;

        virtual std::shared_ptr<const std::string> link() const;

        virtual std::shared_ptr<const std::string> permissions() const;

        virtual std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> contained_resources() const;

    private:
        Resource_impl(std::shared_ptr<const std::string>&& id,
                      std::string&& name,
                      long size,
                      long time,
                      bool is_directory,
                      bool is_file,
                      std::shared_ptr<const std::string>&& link,
                      std::shared_ptr<const std::string>&& permissions,
                      std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>>&& contained_resources);

        const std::shared_ptr<const std::string> id_;
        const std::string name_;
        const long size_;
        const long time_;
        const bool is_directory_;
        const bool is_file_;
        const std::shared_ptr<const std::string> link_;
        const std::shared_ptr<const std::string> permissions_;
        const std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> contained_resources_;
    };

}

#endif // ONEDATASHARE_RESOURCE_IMPL_H