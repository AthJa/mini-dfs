cmake_minimum_required(VERSION 3.10)

project(mini_dfs)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(client)
# add_subdirectory(metadata_server)
add_subdirectory(storage_node)
# add_subdirectory(common)