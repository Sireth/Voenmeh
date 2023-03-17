cmake_minimum_required(VERSION 3.23)
project(Term_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lncurses)
find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )

add_executable(Tests tests/main.cpp)
add_executable(pr_1 pr_1/Triangle.cpp pr_1/Triangle.h pr_1/main.cpp pr_1/funcs.h pr_1/funcs.cpp)
add_executable(pr_1_struct pr_1_struct/classes/LinkedList.hpp pr_1_struct/classes/Node.hpp pr_1_struct/main.cpp pr_1_struct/make.h pr_1_struct/structs/Person.cpp pr_1_struct/structs/Person.h pr_1_struct/unions/Sex.cpp pr_1_struct/unions/Sex.h pr_1_struct/unions/DataUnion.hpp pr_1_struct/classes/Data.hpp pr_1_struct/classes/Table.hpp pr_1_struct/gen.cpp pr_1_struct/gen.h)
target_link_libraries(pr_1_struct /usr/lib/x86_64-linux-gnu/libncursesw.so)

add_executable(pr_2 pr_2/Tea/Interfaces/ITea.h pr_2/Tea/Factories/Interfaces/ITeaFactory.h pr_2/Tea/EarlGreyTea.cpp pr_2/Tea/EarlGreyTea.h pr_2/Tea/CeylonTea.cpp pr_2/Tea/CeylonTea.h pr_2/Tea/GreenTea.cpp pr_2/Tea/GreenTea.h pr_2/Tea/Interfaces/ITea.cpp pr_2/Tea/LapsangSouchongTea.cpp pr_2/Tea/LapsangSouchongTea.h pr_2/Tea/Factories/CeylonTeaFactory.cpp pr_2/Tea/Factories/CeylonTeaFactory.h pr_2/Tea/Factories/EarlGreyTeaFactory.cpp pr_2/Tea/Factories/EarlGreyTeaFactory.h pr_2/Tea/Factories/GreenTeaFactory.cpp pr_2/Tea/Factories/GreenTeaFactory.h pr_2/Tea/Factories/LapsangSouchongTeaFactory.cpp pr_2/Tea/Factories/LapsangSouchongTeaFactory.h pr_2/main.cpp pr_2/funcs.cpp pr_2/funcs.h)