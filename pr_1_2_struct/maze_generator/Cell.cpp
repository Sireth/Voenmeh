#include "Cell.h"


Cell::Cell(int x, int y) {
    this->m_x = x;
    this->m_y = y;
    m_visited = false;
    setWalls();
}

void Cell::setWalls() {
    for (bool &wall: m_walls) wall = true;
}

void Cell::setVisited(bool b) {
    m_visited = b;
}

bool Cell::isVisited() const {
    return m_visited;
}

int Cell::getX() const {
    return m_x;
}

int Cell::getY() const {
    return m_y;
}

void Cell::removeWalls(Cell &next) {
    int x = m_x - next.m_x;
    int y = m_y - next.m_y;

    if (x == 1) {
        m_walls[LEFT] = false;
        next.m_walls[RIGHT] = false;
    } else if (x == -1) {
        m_walls[RIGHT] = false;
        next.m_walls[LEFT] = false;
    } else if (y == -1) {
        m_walls[TOP] = false;
        next.m_walls[BOTTOM] = false;
    } else if (y == 1) {
        m_walls[BOTTOM] = false;
        next.m_walls[TOP] = false;
    }
}