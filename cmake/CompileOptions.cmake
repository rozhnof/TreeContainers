set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -g)
# add_compile_options(-Werror)

message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")