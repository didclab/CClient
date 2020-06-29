/**
 * Item.hpp
 * Andrew Mikalsen
 * 6/29/20
 */

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

namespace ods {
    /**
     * Lazily-evaluated handle to an item found at an endpoint.
     */
    class Item {
        Item() = default;
        Item(const Item&) = delete;
        Item& operator=(const Item&) = delete;
        virtual ~Item() = 0;
    };
}

#endif // ITEM_HPP_INCLUDED