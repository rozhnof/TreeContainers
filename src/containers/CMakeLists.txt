cmake_minimum_required(VERSION 3.16)

set(namespace "containers")
project("containers"
    LANGUAGES C CXX
    VERSION 0.1
    DESCRIPTION "Containers library for C++"
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # add_compile_options("-Wall" "-Weffc++" "-Wextra" "-Wsign-conversion" "-g" "-O0") #"-Werror"
    add_compile_options("-g" "-O0") #"-Werror"
else()
    message("WE NEED GCC FOR CODE COVERAGE AND COMPILE OPTIONS REQUIRED BY SCHOOL")
endif()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)



# FOR SCHOOL MAC'S HOMEBREW
list(APPEND CMAKE_SYSTEM_PREFIX_PATH /opt/goinfre/$ENV{USER}/homebrew/bin)
list(APPEND CMAKE_SYSTEM_PREFIX_PATH /opt/goinfre/$ENV{USER}/homebrew/sbin)


add_subdirectory(third_party)

# # CPPCHECK
# if(NOT WIN32)
# find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
# if(CMAKE_CXX_CPPCHECK)
# 	list(APPEND CMAKE_CXX_CPPCHECK
#     "--enable=style,performance,portability"
#     "--suppress=missingIncludeSystem")
# endif()
# endif()


add_subdirectory(includes)
add_subdirectory(tests)


# FORMATTING
set(CLANG_FORMAT_EXCLUDE_PATTERNS
        "../build/"
        "third_party/"
        ${CMAKE_BINARY_DIR}
)

find_package(ClangFormat)
