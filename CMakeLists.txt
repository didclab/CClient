cmake_minimum_required(VERSION 3.10)

project(onedatashare VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "C++ Client for One Data Share")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add static library for onedatashare client
add_library(${PROJECT_NAME}
    external/simdjson/simdjson.cpp
    src/credential_service.cpp
    src/credential_service_impl.cpp
    src/curl_rest.cpp
    src/endpoint.cpp
    src/endpoint_impl.cpp
    src/ods_error.cpp
    src/resource_impl.cpp
    src/rest.cpp
    src/transfer_service.cpp
    src/transfer_service_impl.cpp
    src/utils.cpp
)

# find libcurl
find_path(LCURL_DIR curl)
find_library(LCURL_LIB curl)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        "${LCURL_DIR}"
        external
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    "${LCURL_LIB}"
)

target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
target_compile_featureS(${PROJECT_NAME} PRIVATE cxx_std_17)

# add unit tests
add_subdirectory(tests)

# add examples
add_subdirectory(examples)
