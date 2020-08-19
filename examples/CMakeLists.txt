# add example register executable
add_executable(example_register
example_register.cpp
)
target_include_directories(example_register PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_register PRIVATE
    onedatashare
)

# add example oauth executable
add_executable(example_oauth
    example_oauth.cpp
)
target_include_directories(example_oauth PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_oauth PRIVATE
    onedatashare
)

# add example transfer executable
add_executable(example_transfer
    example_transfer.cpp
)
target_include_directories(example_transfer PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_transfer PRIVATE
    onedatashare
)

# add example monitor executable
add_executable(example_monitor
    example_monitor.cpp
)
target_include_directories(example_monitor PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_monitor PRIVATE
    onedatashare
)

# install all executables
install(TARGETS example_register example_oauth example_transfer example_monitor DESTINATION "${CMAKE_INSTALL_PREFIX}")
