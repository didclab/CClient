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
        Resource_impl(std::shared_ptr<const std::string>&& id,
                      std::string&& name,
                      long size,
                      long time,
                      bool is_directory,
                      bool is_file,
                      std::shared_ptr<const std::string>&& link,
                      std::shared_ptr<const std::string>&& permissions,
                      std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>>&& contained_resources);

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
        /**
         * Id of the resource if the resource has an id, nullptr otherwise.
         */
        const std::shared_ptr<const std::string> id_;
        /**
         * Name of the resource.
         */
        const std::string name_;
        /**
         * Size of the resource.
         */
        const long size_;
        /**
         * Time of the resource
         */
        const long time_;
        /**
         * True if the resource is a directory, false otherwise.
         */
        const bool is_directory_;
        /**
         * True if the resource is a file, false otherwise.
         */
        const bool is_file_;
        /**
         * Link of the resource if the resource is a link, nullptr otherwise.
         */
        const std::shared_ptr<const std::string> link_;
        /**
         * Permissions of the resource if the resource has permissions, nullptr otherwise.
         */
        const std::shared_ptr<const std::string> permissions_;
        /**
         * Resources contained in this resource if this resource is a directory, nullptr otherwise.
         */
        const std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> contained_resources_;
    };

}

#endif // ONEDATASHARE_RESOURCE_IMPL_H