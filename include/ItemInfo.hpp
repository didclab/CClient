/*
 * ItemInfo.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ITEM_INFO_HPP_INCLUDED
#define ITEM_INFO_HPP_INCLUDED

#include <string>

namespace ods {
    class ItemInfo {
        public:
            std::string id();
            std::string path();
            long size();
        private:
            ItemInfo(const std::string id, const std::string path, const std::string size);
            const std::string _id;
            const std::string _path;
            const long _size;
    };
}

#endif // ITEM_INFO_HPP_INCLUDED