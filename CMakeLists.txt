cmake_minimum_required(VERSION 3.10)

project(libonedatashare VERSION 0.1.0 LANGUAGES CXX DESCRIPTION "C++ Client for One Data Share")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find libcurl dependency
set(MIN_CURL_VERSION 7.47.0)
find_package(CURL ${MIN_CURL_VERSION} REQUIRED)

# add static library for onedatashare client
add_library(onedatashare
    external/simdjson/simdjson.cpp
    src/credential_service.cpp
    src/credential_service_impl.cpp
    src/curl_rest.cpp
    src/endpoint.cpp
    src/endpoint_impl.cpp
    src/ods_error.cpp
    src/rest.cpp
    src/transfer_service.cpp
    src/transfer_service_impl.cpp
    src/utils.cpp
)

add_library(OneDataShare::onedatashare ALIAS onedatashare)

target_include_directories(onedatashare
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(onedatashare
    PRIVATE
        ${CURL_LIBRARIES}
)

if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug")

    include(GNUInstallDirs)
    install(TARGETS onedatashare
        EXPORT onedatashare-export
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

    set_target_properties(onedatashare PROPERTIES EXPORT_NAME OneDataShare)

    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    set(INSTALL_CONFIG_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/OneDataShare)

    # create targets cmake file
    install(EXPORT onedatashare-export
        FILE OneDataShareTargets.cmake
        NAMESPACE OneDataShare::
        DESTINATION ${INSTALL_CONFIG_DIR}
    )

    # create version cmake file
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/OneDataShareConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # create config cmake file
    configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/OneDataShareConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/OneDataShareConfig.cmake
        INSTALL_DESTINATION  ${INSTALL_CONFIG_DIR}
    )

    export(EXPORT onedatashare-export
        FILE ${CMAKE_CURRENT_BINARY_DIR}/OneDataShareTargets.cmake
        NAMESPACE OneDataShare::
    )

    # add to package registry
    export(PACKAGE OneDataShare)

    install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/OneDataShareConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/OneDataShareConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIG_DIR}
    )

endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    # add unit tests
    add_subdirectory(tests)

    # add examples
    add_subdirectory(examples)
endif()
