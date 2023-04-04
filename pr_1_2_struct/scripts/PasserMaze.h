#ifndef TERM_2_PASSERMAZE_H
#define TERM_2_PASSERMAZE_H

#pragma once

#include <chrono>
#include <SDL2/SDL.h>
#include "../engine/Component.h"
#include "../maze_generator/Cell.h"
#include "../vector/Vector.hpp"
#include "../stack/StackLinked.h"

class PasserMaze : public Component {
private:

    StackLinked<Cell *> m_backtrace;
    Cell *m_current;
    bool m_passing = true;
    SDL_Texture * m_texturePass;
    SDL_Texture * m_textureStd;

    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long,
            std::ratio<1, 1000000000>>> startTime;
public:

    int m_width;
    int m_height;

    GameObject **objects{};
    Vector<Cell> m_cells;


    void start() override;

    void update() override;

    void fixedUpdate() override;

private:
    Cell *findNextCell();

    Vector<Cell *> getAvailableNeighbors();

    [[nodiscard]] int calculateIndex(int row, int column) const;
};


#endif //TERM_2_PASSERMAZE_H
