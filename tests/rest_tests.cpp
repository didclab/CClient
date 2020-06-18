/*
 * rest_tests.cpp
 * Andrew Mikalasen
 * 6/17/20
 */

#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <rest.hpp>

namespace {
    /*
     * Test that the headers get copied properly when creating a new Response.
     */
    TEST(Response, ConstructorCopiesHeaders) {
        typedef std::pair<std::string, std::string> spair;

        // key, value pairs
        spair pair_1("foo_key", "foo_val_1");
        spair pair_2("foo_key", "foo_val_2");
        spair pair_3("bar_key", "bar_val");
        spair pair_4("baz_key", "baz_val");
        spair pair_5("qux_key", "qux_val");
        
        // initialize map
        std::unordered_multimap<std::string, std::string> map;
        map.insert(pair_1);
        map.insert(pair_2);
        map.insert(pair_3);
        map.insert(pair_4);
        map.insert(pair_4); // insert pair 4 twice
        map.insert(pair_5);

        ods::rest::Response r(map, "", 0);

        for (spair p : map) {
            EXPECT_EQ(map.count(p.first), r.headers().count(p.first));
        }
        EXPECT_EQ(map, r.headers());
        EXPECT_NE(&map, &r.headers());
    }

    /*
     * Test that body gets copied properly when creating a new Response.
     */
    TEST(Response, ConstructorCopiesBody) {
        std::string body = "This is the body.";

        ods::rest::Response r(std::unordered_multimap<std::string, std::string>(), body, -1);

        EXPECT_STREQ(body.c_str(), r.body().c_str());
        EXPECT_NE(&body, &r.body());
    }

    /*
     * Test that status gets copied properly when creating a new Response.
     */
    TEST(Response, ConstructorCopiesStatus) {
        int status = 123;

        ods::rest::Response r(std::unordered_multimap<std::string, std::string>(), "", status);

        EXPECT_EQ(status, r.status());
        EXPECT_NE(&status, &r.status());
    }
}