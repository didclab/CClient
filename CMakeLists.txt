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
    include/CredentialService.hpp
    include/Destination.hpp
    include/Endpoint.hpp
    include/EndpointType.hpp
    include/Resource.hpp
    include/Source.hpp
    include/TransferOptions.hpp
    include/TransferService.hpp
    include/TransferStatus.hpp
    src/CredentialService.cpp
    src/Destination.cpp
    src/Endpoint.cpp
    src/Source.cpp
    src/TransferService.cpp
    src/internal/CredentialServiceImpl.cpp
    src/internal/CredentialServiceImpl.hpp
    src/rest/CurlRest.cpp
    src/rest/CurlRest.hpp
    src/rest/Response.cpp
    src/rest/Response.hpp
    src/rest/Rest.cpp
    src/rest/Rest.hpp
)
target_include_directories(odscclient PRIVATE "${LCURL_DIR}" ../simdjson/ include/ src/)
target_link_libraries(odscclient PRIVATE "${LCURL_LIB}" simd)

# add main executable
add_executable(main examples/main.cpp)
target_include_directories(main PRIVATE src/ include/)
target_link_libraries(main PRIVATE odscclient)

install(TARGETS main DESTINATION  ${CMAKE_INSTALL_PREFIX})

# add example 1 executable
# uncomment to test that example_1 compiles
#add_executable(example_1 examples/example_1.cpp)
#target_include_directories(example_1 PRIVATE include/)
#target_link_libraries(example_1 PRIVATE odscclient)

# add example 2 executable
add_executable(example_2 examples/example_2.cpp)
target_include_directories(example_2 PRIVATE include/)
target_link_libraries(example_2 PRIVATE odscclient)

install(TARGETS example_2 DESTINATION  ${CMAKE_INSTALL_PREFIX})

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
    tests/internal/CredentialServiceImplTests.cpp
    tests/rest/ResponseTests.cpp
)
target_include_directories(tests PRIVATE src/ include/)
target_link_libraries(tests PRIVATE gtest_main gmock_main odscclient)
install(TARGETS tests DESTINATION ${CMAKE_INSTALL_PREFIX})
