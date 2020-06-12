cmake_minimum_required(VERSION 3.10)

project(odscclient VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_path(LCURL_DIR curl)
find_library(LCURL_LIB curl)

# add simdjson library
add_library(simd
    simdjson/simdjson.h
    simdjson/simdjson.cpp
)

# add ods client library
add_library(odscclient
    src/curl_wrapper.hpp
    src/curl_wrapper.cpp
)
target_include_directories(odscclient PRIVATE "${LCURL_DIR}" ../simdjson/)
target_link_libraries(odscclient PRIVATE "${LCURL_LIB}" simd)
#target_include_directories(odscclient PRIVATE simdjson/)
#target_link_libraries(odscclient PRIVATE simd)

# add tests executable
add_executable(tests test/main.cpp)
target_include_directories(tests PRIVATE src/)
target_link_libraries(tests PRIVATE odscclient)

install(TARGETS tests DESTINATION bin)