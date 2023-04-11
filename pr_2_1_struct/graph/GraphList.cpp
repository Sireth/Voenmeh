#include <iostream>
#include <sstream>
#include <cstring>
#include "GraphList.h"

GraphList::GraphList(int n) {
    for (int i = 0; i < n; i++)
        adjList.push_back(List<int>());
}

GraphList::GraphList(const char *filename) {
    readGraph(filename);
}

bool GraphList::isAdjMatrix(char **lines, int num_lines) {
    if (num_lines < 2) {
        return false;
    }

    const long num_cols = std::count(lines[0], lines[0] + strlen(lines[0]), ' ') +
                          1; // узнаем количество пробелов в строке тем самым находим количество значений
    if (num_cols != num_lines) {
        return false;
    }

    for (int i = 0; i < num_lines; i++) { // идем по каждой строке
        std::stringstream ss(lines[i]);
        int num;
        while (ss >> num) { // пытаемся считать значение
            if (ss.fail() || ss.bad() || (num != 0 && num != 1)) {
                return false;
            }
        }
        if (!ss.eof()) {
            return false;
        }
    }
    return true;
}

bool GraphList::isAdjList(char **lines, int num_lines) {
    if (num_lines == 0) {
        return false;
    }
    for (int i = 0; i < num_lines; i++) { // идем по каждой строке
        std::stringstream ss(lines[i]);
        int num;
        while (ss >> num) { // пытаемся считать значение
            if (ss.fail() || ss.bad()) {
                return false;
            }
        }
        if (!ss.eof()) {
            return false;
        }
    }
    return true;
}

void GraphList::readAdjMatrix(char **lines, int num_lines) {
    Vector<Vector<int>> adj_matrix; // временная матрица

    for (int i = 0; i < num_lines; i++) {
        adj_matrix.push_back(Vector<int>());
        std::stringstream ss(lines[i]);

        for (int j = 0; j < num_lines; j++) {
            adj_matrix[i].push_back(0);
            ss >> adj_matrix[i][j];
        }

        visited.push_back(0);
        from.push_back(-1);
    }

    for (int i = 0; i < n; i++) {
        adjList.push_back(List<int>());
        for (int j = 0; j < n; j++) {
            if (adj_matrix[i][j] == 1) {
                adjList.begin()[i].push_back(j);
            }
        }
    }

    this->n = num_lines;
}

void GraphList::readAdjList(char **lines, int num_lines) {
    List<List<int>> adj_list;

    for (int i = 0; i < num_lines; i++) {
        adj_list.push_back(List<int>());
        std::stringstream ss(lines[i]);
        int neighbor;
        while (ss >> neighbor) {
            adj_list.begin()[i].push_back(neighbor);
        }
        visited.push_back(0);
        from.push_back(-1);
    }

    adjList = adj_list;
    this->n = num_lines;
}

void GraphList::readGraph(const char *filename) {
    FILE *file = fopen(filename, "r"); // чтение файла
    if (file == nullptr) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    char **lines = nullptr; // строки из файла
    int num_lines = 0;
    int line_capacity = 0;
    long file_size = 0;
    if (fseek(file, 0, SEEK_END) == 0) { // пытаемся получить размер файла
        file_size = ftell(file);
    }
    if (file_size <= 0) {
        std::cerr << "Error getting file size: " << filename << std::endl;
        fclose(file);
        return;
    }
    if (fseek(file, 0, SEEK_SET) != 0) { // перемещаемся в начала файла
        std::cerr << "Error setting file position: " << filename << std::endl;
        fclose(file);
        return;
    }

    char *buffer = new char[file_size + 1]; // создаем буфер строк
    size_t bytes_read = fread(buffer, sizeof(char), file_size,
                              file); // читаем весь файл и записываем количество считанных символов

    if (bytes_read != static_cast<size_t>(file_size)) {
        std::cerr << "Error reading file: " << filename << std::endl;
        delete[] buffer;
        fclose(file);
        return;
    }

    buffer[file_size] = '\0'; // в конце файла ставим нуль-терминатор
    const char *delim = "\r\n"; // то, по чему будем разделять считанную строчку из файла
    char *token = strtok(buffer, delim);
    while (token != nullptr) {
        if (token[0] != '\0') { // проверяем дошли ли мы до конца файла

            if (lines == nullptr) { // система такая же как и в векторе, выделяем динамически память под строчки
                line_capacity = 1;
                lines = new char *[line_capacity];
            } else if (num_lines == line_capacity) {
                line_capacity *= 2;
                char **tmp_lines = new char *[line_capacity];
                memcpy(tmp_lines, lines, num_lines * sizeof(char *));
                delete[] lines;
                lines = tmp_lines;
            }

            const size_t len = strlen(token); // узнаем размер строки
            lines[num_lines] = new char[len + 1]; // выделяем память под строку
            memcpy(lines[num_lines], token, len + 1);
            num_lines++;
        }
        token = strtok(nullptr, delim);
    }

    delete[] buffer; // освобождаем память
    fclose(file);

    if (isAdjMatrix(lines, num_lines)) { //проверяем что находится в файле и считываем граф
        readAdjMatrix(lines, num_lines);
    } else if (isAdjList(lines, num_lines)) {
        readAdjList(lines, num_lines);
    } else {
        std::cerr << "Error: unsupported graph format" << std::endl;
    }

    for (int i = 0; i < num_lines; i++) { // освобождаем память
        delete[] lines[i];
    }
    delete[] lines;
}

void GraphList::addEdge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n) {
        throw std::out_of_range("Vertex index out of range");
    }

    adjList.begin()[u].push_back(v);
    adjList.begin()[v].push_back(u);
}

void GraphList::addArc(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n) {
        throw std::out_of_range("Vertex index out of range");
    }

    adjList.begin()[u].push_back(v);
}

void GraphList::removeEdge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n) {
        throw std::out_of_range("Vertex index out of range");
    }

    adjList.begin()[u].remove(v);
    adjList.begin()[v].remove(u);
}

void GraphList::removeArc(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n) {
        throw std::out_of_range("Vertex index out of range");
    }

    adjList.begin()[u].remove(v);
}

void GraphList::addVertex() {
    ++n;
    adjList.push_back(List<int>());
}

void GraphList::removeVertex(int v) {
    if (v < 0 || v >= n) {
        throw std::out_of_range("Vertex index out of range");
    }

    // удалить все ребра, связанные с вершиной v
    for (int i = 0; i < n; ++i) {
        adjList.begin()[i].remove(v);
    }

    // удалить саму вершину
    adjList.erase(adjList.begin() + v);
    --n;
}

void GraphList::printGraph() {
    for (int i = 0; i < n; ++i) {
        std::cout << i << ": ";
        for (int &it: adjList.begin()[i]) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
}

void GraphList::dfs() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    cycles.clear();
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}

void GraphList::dfs(int v) {
    visited[v] = 1;
    std::for_each(adjList.begin()[v].begin(), adjList.begin()[v].end(), [this, &v](int u) {
        if (visited[u] == 0) {
            from[u] = v;
            dfs(u);
        } else if (visited[u] == 1) {
            Vector<int> cycle;
            cycle.push_back(u);
            for (int j = v; j != u; j = from[j]) {
                cycle.push_back(j);
            }
            cycle.push_back(u);
            std::reverse(cycle.begin(), cycle.end());
            cycles.push_back(cycle);
        }
    });
    visited[v] = 2;
}

Vector<int> GraphList::findCommonElements() {
    if (cycles.empty()) return {};
    Vector<int> commonVec = cycles[0];
    for (size_t i = 1; i < cycles.size(); ++i) {
        Vector<int> tempVec;
        for (int j: cycles[i]) {
            if (std::find(commonVec.begin(), commonVec.end(), j) != commonVec.end()) {
                tempVec.push_back(j);
            }
        }
        commonVec = tempVec;
    }
    return commonVec;
}

bool GraphList::canRemoveVertexWithoutCycles() {
    dfs();

    auto vertex = findCommonElements();

    if (vertex.size() > 1 || vertex.empty()) {
        return false;
    } else {
        auto g = *this;
        g.removeVertex(vertex[0]);

        g.dfs();
        vertex = g.findCommonElements();

        if (vertex.empty())
            return true;
        else {
            return false;
        }
    }
}
