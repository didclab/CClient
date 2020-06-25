/*
 * Item.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

#include <string>
#include <EndpointType.hpp>

namespace ods {
    enum class ItemType {
        LINK, FILE, DIRECTORY
    };

    // TODO: define
    class Item {
        public:
            std::string path() const;
            std::string id() const;
            long size() const;
        private:
            const std::string _path;
            const std::string _id;
            const long _size;
    };
}

#endif // ITEM_HPP_INCLUDED