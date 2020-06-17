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

# add main executable
add_executable(main examples/main.cpp)
target_include_directories(main PRIVATE src/)
target_link_libraries(main PRIVATE odscclient)

install(TARGETS main DESTINATION  ${CMAKE_INSTALL_PREFIX})

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
    tests/curl_wrapper_tests.cpp
)
target_include_directories(tests PRIVATE src/)
target_link_libraries(tests PRIVATE gtest_main odscclient)
install(TARGETS tests DESTINATION ${CMAKE_INSTALL_PREFIX})
