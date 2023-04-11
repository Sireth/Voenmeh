#ifndef TERM_2_GRAPHLIST_H
#define TERM_2_GRAPHLIST_H

#pragma once
#include "../../pr_1_2_struct/vector/Vector.hpp"
#include "../../pr_1_2_struct/List/List.hpp"

class GraphList {
public:
    explicit GraphList(int n);

    explicit GraphList(const char *filename);

    static bool isAdjMatrix(char **lines, int num_lines);

    static bool isAdjList(char **lines, int num_lines);

    void readAdjMatrix(char **lines, int num_lines);

    void readAdjList(char **lines, int num_lines);

    void readGraph(const char *filename);

    void addEdge(int u, int v);

    void addArc(int u, int v);

    void removeEdge(int u, int v);

    void removeArc(int u, int v);

    void addVertex();

    void removeVertex(int v);

    void printGraph();

    void dfs();

    void dfs(int v);

    Vector<int> findCommonElements();

    bool canRemoveVertexWithoutCycles();

private:
    List<List<int>> adjList;

    Vector<int> visited;
    Vector<Vector<int>> cycles;
    Vector<int> from;

    int n{};
};


#endif //TERM_2_GRAPHLIST_H
