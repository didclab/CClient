/**
 * Resource.hpp
 * Andrew Mikalsen
 * 6/29/20
 */

#ifndef RESOURCE_HPP_INCLUDED
#define RESOURCE_HPP_INCLUDED

#include <memory>
#include <string>

namespace ods {
    /**
     * Resource from an endpoint's file system containing a directory, file, or
     * link. Resource objects cannot be copied by their copy constructor nor
     * their copy assignment operator.
     */
    class Resource {
        public:
            /**
             * Gets the id of the Resource if the Resource has an id. The
             * Resource will have an id if and only if the endpoint used
             * supports ids. The caller is expected to check for a null pointer
             * if they are not certain that the Resource has an id. The returned
             * pointer is reference counted, so the pointer is safe to use even
             * after the Resource is deallocated.
             * 
             * @return a shared pointer to the id of the Resource or a null
             * pointer if the Resource doesn't have an id
             */
            virtual const std::shared_ptr<std::string> id() const = 0;

            /**
             * Gets the name of the Resource.
             * 
             * @return a copy of the name of the Resource
             */
            virtual std::string name() const = 0;

            /**
             * Gets the size of the Resource. If size is called on a Resource
             * without a size, 0 is returned.
             * 
             * @return a copy of the size of the Resource
             */
            virtual long size() const = 0;

            /**
             * Gets the time of the Resource.
             * 
             * @return a copy of the time of the Resource
             */
            virtual long time() const = 0;

            /**
             * Determines whether or not the Resource is a directory.
             * 
             * @return true if and only if the Resource is a directory.
             */
            virtual bool is_directory() const = 0;

            /**
             * Determines whether or not the Resource is a file.
             * 
             * @return true if and only if the Resource is a file.
             */
            virtual bool is_file() const = 0;

            /**
             * Gets the link of the Resource if and only if the Resource is a
             * link. The caller is expected to check for a null pointer unless
             * they are absolutely certain that the Resource is a link. The
             * returned pointer is reference counted, so the pointer is safe to
             * use even after the Resource is deallocated.
             * 
             * @return a shared pointer to the link of the Resource or a null
             * pointer if the Resource isn't a link
             */
            virtual const std::shared_ptr<std::string> link() const = 0;

            /**
             * Gets the permissions of the Resource if the resource has
             * permissions. The caller is expected to check for a null pointer
             * unless they are absolutely certain the Resource has permissions.
             * The returned pointer is reference counted, so the pointer is safe
             * to use even after the Resource is deallocated.
             * 
             * @return a shared pointer to the permissions of the Resource or a
             * null pointer if the Resource isn't a link
             */
            virtual const std::shared_ptr<std::string> permissions() const = 0;

            /**
             * Gets the Resource objects contained in this Resource if and only
             * if this Resource is a directory. The caller is expected to check
             * for a null pointer unless they are absolutely certain the
             * Resource is a directory or they already checked via is_directory.
             * The returned pointer is reference counted, so the pointer is safe
             * to use even after the Resource is deallocated.
             * 
             * @return a shared pointer to the Resource objects contained in
             * this Resource or null if the Resource isn't a directory
             */
            virtual const std::shared_ptr<std::string> contained_resources() const = 0;

            Resource(const Resource&) = delete;
            Resource& operator=(const Resource&) = delete;

            virtual ~Resource() = 0;
        protected:
            Resource() = default;
    };
}

#endif // RESOURCE_HPP_INCLUDED