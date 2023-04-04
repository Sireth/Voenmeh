#ifndef TERM_2_RENDERERWINDOW_H
#define TERM_2_RENDERERWINDOW_H

#pragma once

#include <SDL2/SDL.h>
#include <thread>
#include "../vector/Vector.hpp"
#include "GameObject.h"
#include "ThreadPool.h"


class RendererWindow {
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    Vector<GameObject *> m_objectsOnScene;

    std::thread m_mainRenderLoopThread;
    std::thread m_mainFixedLoopThread;
    ThreadPool m_objectsUpdateThreadPool{20};
    ThreadPool m_objectsFixedUpdateThreadPool{20};

    bool m_isRun;

    std::mutex m_objectsMutex;
    std::mutex m_instanceMutex;

public:
    ThreadPool m_objectsStartThreadPool{20};
    int m_windowWeight;
    int m_windowHeight;
    std::mutex m_rendererMutex{};
public:

    RendererWindow(const char *title, int weight, int height);

    SDL_Renderer *getRenderer();

    void startGameLoop();

    void finishGameLoop();

    void render(GameObject *object);

    void instantiateGameObject(GameObject &gameObject);

private:
    void update();

    void fixedUpdate();
};


#endif //TERM_2_RENDERERWINDOW_H
