#ifndef TERM_2_CELL_H
#define TERM_2_CELL_H


class Cell {
private:
    int m_x, m_y;
    bool m_visited;

public:
    enum direction {
        TOP=0, RIGHT=1, BOTTOM=2, LEFT=3
    };
    bool m_walls[4]{};
public:
    explicit Cell(int x = 0, int y = 0);

    void setWalls();

    void setVisited(bool b);

    [[nodiscard]] bool isVisited() const;

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    void removeWalls(Cell &next);

};


#endif //TERM_2_CELL_H
