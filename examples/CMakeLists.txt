# add example 1 executable
add_executable(example_1
    example_1.cpp
)
target_include_directories(example_1 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_1 PRIVATE
    onedatashare
)

# add example 2 executable
add_executable(example_2
    example_2.cpp
)
target_include_directories(example_2 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_2 PRIVATE
    onedatashare
)

# add example 3 executable
add_executable(example_3
    example_3.cpp
)
target_include_directories(example_3 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(example_3 PRIVATE
    onedatashare
)

# install all executables
install(TARGETS example_1 example_2 example_3 DESTINATION "${CMAKE_INSTALL_PREFIX}")
