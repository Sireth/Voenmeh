#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "../pr_1_2_struct/vector/Vector.hpp"
#include "../pr_1_2_struct/stack/StackLinked.h"
#include "graph/GraphMatrix.h"
#include "graph/GraphList.h"

class Graph {

};


int main() {
    auto g = GraphList("/media/sireth/F0CE491ACE48DA8C/Projects/CppProjects/Term_2/pr_2_1_struct/matrix");

    g.printGraph();

    std::cout << g.canRemoveVertexWithoutCycles() << std::endl;

    g.printGraph();


    return 0;
}

