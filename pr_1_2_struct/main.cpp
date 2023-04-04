#include <iostream>
#include <vector>
#include "stack/interfaces/IStack.hpp"
#include "stack/interfaces/IStackFactory.h"
#include "stack/factories/StackLinkedFactory.h"
#include "stack/factories/StackVectorFactory.h"
#include "vector/Vector.hpp"
#include "maze_generator/Grid.h"
#include "engine/RendererWindow.h"
#include "scripts/GenCell.h"
#include "scripts/PasserMaze.h"

#define SIZE_X 22
#define SIZE_Y 22

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
    RendererWindow window("qwerty", 1280, 720);
    GameObject obj(&window);
    obj.m_position = Vector2(1280, 720);
    std::mutex cellMutex;
    Vector<Cell> cells = Grid(SIZE_X, SIZE_Y).generateMaze();

    auto **objects = new GameObject *[SIZE_Y];
    for (int i = 0; i < SIZE_Y; i++) {
        objects[i] = new GameObject[SIZE_X]{&window, &window, &window, &window, &window, &window, &window, &window,
                                            &window,
                                            &window, &window, &window, &window, &window, &window, &window, &window,
                                            &window,
                                            &window, &window, &window, &window};
    }
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            objects[x][y].m_position = Vector2(static_cast<float>(x) * 32 + 16, static_cast<float>(y) * 32 + 16);
            auto *genCell = new GenCell();
            genCell->m_cells = &cells;
            genCell->x = x;
            genCell->y = y;
            genCell->m_cellMutex = &cellMutex;
            objects[x][y].addComponent(genCell);
        }
    }
    for (int x = 0; x < SIZE_X; x++) {
        for (int y = 0; y < SIZE_Y; y++) {
            window.instantiateGameObject(objects[x][y]);
        }
    }
    auto passer = new PasserMaze();
    passer->objects = objects;
    passer->m_height = SIZE_Y;
    passer->m_width = SIZE_X;
    passer->m_cells = cells;
    obj.addComponent(passer);
    window.instantiateGameObject(obj);
    /*obj.m_position = Vector2(0, 0);
    obj.setActive(true);
    obj.addComponent(new Test());*/
/*
    std::cout << "main: " << &obj << std::endl;
    window.instantiateGameObject(obj);*/
    window.startGameLoop();

    return 0;
}

