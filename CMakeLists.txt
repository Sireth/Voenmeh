cmake_minimum_required(VERSION 3.23)
project(Term_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lncurses)
find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )

add_executable(Tests tests/main.cpp)
add_executable(pr_1 pr_1/Triangle.cpp pr_1/Triangle.h pr_1/main.cpp pr_1/funcs.h pr_1/funcs.cpp)
add_executable(pr_1_struct pr_1_struct/classes/LinkedList.hpp pr_1_struct/classes/Node.hpp pr_1_struct/main.cpp pr_1_struct/make.h pr_1_struct/structs/Person.cpp pr_1_struct/structs/Person.h pr_1_struct/unions/Sex.cpp pr_1_struct/unions/Sex.h pr_1_struct/unions/DataUnion.hpp pr_1_struct/classes/Data.hpp pr_1_struct/classes/Table.hpp)
target_link_libraries(pr_1_struct /usr/lib/x86_64-linux-gnu/libncursesw.so)

