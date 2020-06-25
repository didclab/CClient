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
            std::string id() const;
            std::string path() const;
            long size() const;
            /**
             * Determines if two ItemInfo objects refer to the same object.
             * 
             * @param that ItemInfo to compare
             * 
             * @return true if both ItemInfo objects have the same id and path, false otherwise
             */
            bool operator==(const ItemInfo& that) const;
            /**
             * Class that determines how ItemInfo objects should be hashed.
             */
            class Hash {
                public:
                    /**
                     * Computes the hash of the specified ItemInfo object.
                     * 
                     * @param item_info ItemInfo object to compute the hash of
                     * 
                     * @return the hash of the specified ItemInfo object
                     */
                    size_t operator()(const ItemInfo& item_info) const;
            };
        private:
            ItemInfo(const std::string id, const std::string path, const long size);
            const std::string _id;
            const std::string _path;
            const long _size;
            friend class Source;
    };
}

#endif // ITEM_INFO_HPP_INCLUDED