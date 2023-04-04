#include <random>
#include "PasserMaze.h"
#include "../engine/GameObject.h"
#include "../engine/RendererWindow.h"


void PasserMaze::start() {
    startTime = std::chrono::high_resolution_clock::now();
    std::for_each(m_cells.begin(), m_cells.end(), [](Cell &cell) {
        cell.setVisited(false);
    });
    m_current = &m_cells[0];

    gameObject->m_rendererWindow->m_rendererMutex.lock();
//std Texture

    m_textureStd = SDL_CreateTexture(gameObject->m_rendererWindow->getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                     SDL_TEXTUREACCESS_TARGET, 32,
                                     32);
    SDL_SetRenderTarget(gameObject->m_rendererWindow->getRenderer(), m_textureStd);


    SDL_SetRenderDrawColor(gameObject->m_rendererWindow->getRenderer(), 150, 150, 150, 255);
    SDL_RenderClear(gameObject->m_rendererWindow->getRenderer());

    SDL_SetRenderTarget(gameObject->m_rendererWindow->getRenderer(), nullptr);
//pass Texture

    m_texturePass = SDL_CreateTexture(gameObject->m_rendererWindow->getRenderer(), SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET, 32,
                                      32);
    SDL_SetRenderTarget(gameObject->m_rendererWindow->getRenderer(), m_texturePass);


    SDL_SetRenderDrawColor(gameObject->m_rendererWindow->getRenderer(), 15, 247, 178, 255);
    SDL_RenderClear(gameObject->m_rendererWindow->getRenderer());

    SDL_SetRenderTarget(gameObject->m_rendererWindow->getRenderer(), nullptr);
//
    gameObject->m_rendererWindow->m_rendererMutex.unlock();

    m_backtrace = StackLinked<Cell *>(m_width * m_height);
}

void PasserMaze::update() {

}

void PasserMaze::fixedUpdate() {
    if (m_passing) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_ms =
                end - startTime;
        if (elapsed_ms.count() > 100) {
            startTime = end;

            m_current->setVisited(true);
            objects[m_current->getX()][m_current->getY()].m_mutex.lock();
            objects[m_current->getX()][m_current->getY()].m_texture = m_texturePass;
            objects[m_current->getX()][m_current->getY()].m_mutex.unlock();
            Cell *next = findNextCell();

            if (m_current->getX() == m_width - 1 && m_current->getY() == m_height - 1) {
                m_passing = false;
            } else if (next != nullptr) {
                next->setVisited(true);
                m_backtrace.push(m_current);
                m_current = next;
                objects[m_current->getX()][m_current->getY()].m_mutex.lock();
                objects[m_current->getX()][m_current->getY()].m_texture = m_texturePass;
                objects[m_current->getX()][m_current->getY()].m_mutex.unlock();

            } else if (m_backtrace.size() > 0) {
                objects[m_current->getX()][m_current->getY()].m_mutex.lock();
                objects[m_current->getX()][m_current->getY()].m_texture = m_textureStd;
                objects[m_current->getX()][m_current->getY()].m_mutex.unlock();
                m_current = m_backtrace.peek();
                m_backtrace.pop();
            } else if (m_backtrace.size() == 0) {
                m_passing = false;
            }

        }
    }
}

Cell *PasserMaze::findNextCell() {
    Vector<Cell *> availableNeighbors = getAvailableNeighbors();
    if (!availableNeighbors.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned long> index(0, availableNeighbors.size() - 1);
        return availableNeighbors.at(index(gen));
    }

    return nullptr;
}

Vector<Cell *> PasserMaze::getAvailableNeighbors() {
    Vector<Cell *> neighbors;

    int currentX = m_current->getX();
    int currentY = m_current->getY();

    int neighborIndexes[4] = {
            calculateIndex(currentX - 1, currentY),
            calculateIndex(currentX, currentY - 1),
            calculateIndex(currentX + 1, currentY),
            calculateIndex(currentX, currentY + 1),
    };


    if (neighborIndexes[0] != -1)
        if (m_current->m_walls[Cell::LEFT] == true) {
            neighborIndexes[0] = -1;
        }
    if (neighborIndexes[1] != -1)
        if (m_current->m_walls[Cell::BOTTOM] == true) {
            neighborIndexes[1] = -1;
        }
    if (neighborIndexes[2] != -1)
        if (m_current->m_walls[Cell::RIGHT] == true) {
            neighborIndexes[2] = -1;
        }
    if (neighborIndexes[3] != -1)
        if (m_current->m_walls[Cell::TOP] == true) {
            neighborIndexes[3] = -1;
        }

    for (int i: neighborIndexes) {
        if (i != -1 && !m_cells[i].isVisited()) {
            neighbors.push_back(&m_cells[i]);
        }
    }

    return neighbors;
}

int PasserMaze::calculateIndex(int row, int column) const {
    if (row < 0 || column < 0 || column > m_width - 1 || row > m_height - 1)
        return -1;
    else
        return row + column * m_width;
}