#ifndef TERM_2_GENCELL_H
#define TERM_2_GENCELL_H

#pragma once

#include <SDL2/SDL.h>
#include <mutex>
#include "../engine/Component.h"
#include "../maze_generator/Cell.h"
#include "../vector/Vector.hpp"

class GenCell : public Component {
public:
    Vector<Cell> *m_cells{};
    std::mutex *m_cellMutex;
    int x = 0;
    int y = 0;

    void start() override;

    void update() override;

    void fixedUpdate() override;
};


#endif //TERM_2_GENCELL_H
