cmake_minimum_required(VERSION 3.24)
project(deque)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined -std=c++20)
#add_compile_options(-pedantic -Werror -Wextra -fsanitize=undefined -std=c++20)

add_link_options(-pedantic -Werror -Wextra -fsanitize=address -fsanitize=undefined -std=c++20)
#add_link_options(-pedantic -Werror -Wextra -fsanitize=address -std=c++20)

add_executable(deque Deque.h
        stress_test.cpp
        #main.cpp
        #tests.cpp
        )

#find_package(GTest)

#include(GoogleTest)

#target_link_libraries(deque GTest::gtest_main)

#gtest_discover_tests(deque)

#cmake_minimum_required(VERSION 3.24)
#project(deque)

#set(CMAKE_CXX_STANDARD 20)

#add_executable(deque main.cpp Deque.h)
