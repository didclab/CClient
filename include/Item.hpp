/**
 * Item.hpp
 * Andrew Mikalsen
 * 6/29/20
 */

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

namespace ods {
    /**
     * Lazily-evaluated handle to a directory, file, or link found at an endpoint.
     */
    class Item {
        public:
            Item(const Item&) = delete;
            Item& operator=(const Item&) = delete;
            virtual ~Item() = 0;
        protected:
            Item() = default;
    };
}

#endif // ITEM_HPP_INCLUDED