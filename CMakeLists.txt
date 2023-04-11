cmake_minimum_required(VERSION 3.23)
project(Term_2)

set(CMAKE_CXX_STANDARD 17)



#ncurses
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lncurses)
find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )
#

add_executable(Tests tests/main.cpp tests/Node1.hpp tests/Node2.hpp)
add_executable(pr_1 pr_1/Triangle.cpp pr_1/Triangle.h pr_1/main.cpp pr_1/funcs.h pr_1/funcs.cpp)
add_executable(pr_1_struct pr_1_struct/classes/LinkedList.hpp pr_1_struct/classes/Node.hpp pr_1_struct/main.cpp pr_1_struct/make.h pr_1_struct/structs/Person.cpp pr_1_struct/structs/Person.h pr_1_struct/unions/Sex.cpp pr_1_struct/unions/Sex.h pr_1_struct/unions/DataUnion.hpp pr_1_struct/classes/Data.hpp pr_1_struct/classes/Table.hpp pr_1_struct/gen.cpp pr_1_struct/gen.h)
target_link_libraries(pr_1_struct /usr/lib/x86_64-linux-gnu/libncursesw.so)

add_executable(pr_2 pr_2/Tea/Interfaces/ITea.h pr_2/Tea/Factories/Interfaces/ITeaFactory.h pr_2/Tea/EarlGreyTea.cpp pr_2/Tea/EarlGreyTea.h pr_2/Tea/CeylonTea.cpp pr_2/Tea/CeylonTea.h pr_2/Tea/GreenTea.cpp pr_2/Tea/GreenTea.h pr_2/Tea/Interfaces/ITea.cpp pr_2/Tea/LapsangSouchongTea.cpp pr_2/Tea/LapsangSouchongTea.h pr_2/Tea/Factories/CeylonTeaFactory.cpp pr_2/Tea/Factories/CeylonTeaFactory.h pr_2/Tea/Factories/EarlGreyTeaFactory.cpp pr_2/Tea/Factories/EarlGreyTeaFactory.h pr_2/Tea/Factories/GreenTeaFactory.cpp pr_2/Tea/Factories/GreenTeaFactory.h pr_2/Tea/Factories/LapsangSouchongTeaFactory.cpp pr_2/Tea/Factories/LapsangSouchongTeaFactory.h pr_2/main.cpp pr_2/funcs.cpp pr_2/funcs.h)


add_executable(pr_1_2_struct pr_1_2_struct/stack/interfaces/IStack.hpp pr_1_2_struct/main.cpp pr_1_2_struct/stack/StackLinked.h pr_1_2_struct/stack/NodeStack.hpp pr_1_2_struct/stack/StackVector.hpp pr_1_2_struct/stack/interfaces/IStackFactory.h pr_1_2_struct/stack/factories/StackLinkedFactory.h pr_1_2_struct/stack/factories/StackVectorFactory.h pr_1_2_struct/maze_generator/Cell.cpp pr_1_2_struct/maze_generator/Cell.h pr_1_2_struct/maze_generator/Grid.cpp pr_1_2_struct/maze_generator/Grid.h pr_1_2_struct/vector/Vector.hpp pr_1_2_struct/engine/RendererWindow.cpp pr_1_2_struct/engine/RendererWindow.h pr_1_2_struct/engine/GameObject.cpp pr_1_2_struct/engine/GameObject.h pr_1_2_struct/engine/Vector2.cpp pr_1_2_struct/engine/Vector2.h pr_1_2_struct/engine/Component.h pr_1_2_struct/List/List.hpp pr_1_2_struct/engine/ThreadPool.cpp pr_1_2_struct/engine/ThreadPool.h pr_1_2_struct/scripts/GenCell.cpp pr_1_2_struct/scripts/GenCell.h pr_1_2_struct/scripts/PasserMaze.cpp pr_1_2_struct/scripts/PasserMaze.h)

target_link_libraries(pr_1_2_struct -lSDL2_image -lSDL2)

add_executable(pr_2_1_struct pr_2_1_struct/main.cpp pr_2_1_struct/main.cpp pr_2_1_struct/graph/GraphMatrix.cpp pr_2_1_struct/graph/GraphMatrix.h pr_2_1_struct/graph/GraphList.cpp pr_2_1_struct/graph/GraphList.h)