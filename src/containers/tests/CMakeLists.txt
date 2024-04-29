set(namespace "Containers")
project("tests"
    LANGUAGES C CXX
    VERSION 0.1
    DESCRIPTION "Tests for containers"
)

file(GLOB_RECURSE
    TEST_FILES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/src/*.cc
)

add_executable(${PROJECT_NAME}
    ${TEST_FILES}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        containers
        gtest
        gtest_main
)


target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/includes
        ${CMAKE_CURRENT_SOURCE_DIR}/includes

    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT WIN32)
include(CodeCoverage)


append_coverage_compiler_flags_to_target(${PROJECT_NAME})
setup_target_for_coverage_lcov(
            NAME tests_coverage
            EXECUTABLE ${PROJECT_NAME}
            EXCLUDE "${CMAKE_BINARY_DIR}/*" "/Applications/*" "/usr/local/*" "/usr/include/*"
            DEPENDENCIES ${PROJECT_NAME}
    )
endif()
