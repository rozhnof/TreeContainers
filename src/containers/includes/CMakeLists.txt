cmake_minimum_required(VERSION 3.12)
set(namespace "Containers")
project("containers"
    LANGUAGES C CXX
    VERSION 0.1
    DESCRIPTION "List container for C++"
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:includes>
)
