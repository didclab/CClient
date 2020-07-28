cmake_minimum_required(VERSION 3.10)

project(onedatashare VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "C++ Client for One Data Share")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find libcurl
find_path(LCURL_DIR curl)
find_library(LCURL_LIB curl)

# add static library for onedatashare client
add_library(${PROJECT_NAME} STATIC
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
target_include_directories(${PROJECT_NAME} PRIVATE
    "${LCURL_DIR}"
    external
    include
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    "${LCURL_LIB}"
)

# add example 1 executable
add_executable(example_1
    examples/example_1.cpp
)
target_include_directories(example_1 PRIVATE
    include
)
target_link_libraries(example_1 PRIVATE
    onedatashare
)

# add example 2 executable
add_executable(example_2
    examples/example_2.cpp
)
target_include_directories(example_2 PRIVATE
    include
)
target_link_libraries(example_2 PRIVATE
    onedatashare
)

# add example 3 executable
add_executable(example_3
    examples/example_3.cpp
)
target_include_directories(example_3 PRIVATE
    include
)
target_link_libraries(example_3 PRIVATE
    onedatashare
)

# download google test
####################################################################################
# Start From https://github.com/google/googletest/blob/master/googletest/README.md #
####################################################################################

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

##################################################################################
# End From https://github.com/google/googletest/blob/master/googletest/README.md #
##################################################################################

# add unit tests
add_executable(tests
    tests/credential_service_impl_tests.cpp
    tests/endpoint_impl_tests.cpp
    tests/transfer_service_impl_tests.cpp
)
target_include_directories(tests PRIVATE
    include
    src
)
target_link_libraries(tests PRIVATE
    gtest_main
    gmock_main
    onedatashare
)

# install all executables
install(TARGETS example_1 example_2 example_3 tests DESTINATION "${CMAKE_INSTALL_PREFIX}")