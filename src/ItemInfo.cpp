/*
 * ItemInfo.cpp
 * Andrew Mikalsen
 * 6/24/20
 */

#include <functional>
#include <ItemInfo.hpp>

namespace ods {
    // TODO: implement ItemInfo
    ItemInfo::ItemInfo(const std::string id, const std::string path, const long size) :
        _id(id),
        _path(path),
        _size(size) {
    }

    std::string ItemInfo::id() const {
        return _id;
    }

    std::string ItemInfo::path() const {
        return _path;
    }

    long ItemInfo::size() const {
        return _size;
    }

    bool ItemInfo::operator==(const ItemInfo& that) const {
        return _id == that._id && _path == that._path;
    }

    /**
     * Computes the hash of the specified ItemInfo object by concatenating its size, path, and id.
     * 
     * @param item_info ItemInfo object to compute the hash of
     * 
     * @return the hash of the string produced by concatenating the object's size, path, and id
     */
    size_t ItemInfo::Hash::operator()(const ItemInfo& item_info) const {
        return std::hash<std::string>()(item_info._path + item_info._id + std::to_string(item_info._size));
    }
}