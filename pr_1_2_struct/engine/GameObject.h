#ifndef TERM_2_GAMEOBJECT_H
#define TERM_2_GAMEOBJECT_H

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <mutex>
#include "Vector2.h"
#include "Component.h"
#include "../vector/Vector.hpp"
#include "../List/List.hpp"
#include "ThreadPool.h"
#include <shared_mutex>

class RendererWindow;

class GameObject {

public:
    Vector2 m_position;
    Vector2 m_scale;
    double m_angle{};
    List<Component *> components;
    SDL_Texture *m_texture;
    RendererWindow *m_rendererWindow;
    std::mutex m_mutex{};

private:
    SDL_Rect m_destinationTextureRect{};
    SDL_Rect m_sourceTextureRect{};
    bool m_activeSelf{true};

    ThreadPool m_startThreadPool{5};
    ThreadPool m_updateThreadPool{5};
    ThreadPool m_fixedUpdateThreadPool{5};
public:

    GameObject();

    GameObject(char *pathToTexture, RendererWindow *rendererWindow);

    GameObject(RendererWindow *rendererWindow);

    void setActive(bool active);

    SDL_Rect *getSourceRect();

    SDL_Rect *getDestRect();

    void updateDestRect();

    void updateSourceRect();

    SDL_Texture *getTexture();

    [[nodiscard]] bool isActive() const;

    void start();

    void update();

    void fixedUpdate();

    void addComponent(Component *component);

    ~GameObject();

private:
    SDL_Point getsize();
};


#endif //TERM_2_GAMEOBJECT_H
