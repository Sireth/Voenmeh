#include <iostream>
#include "GameObject.h"
#include "RendererWindow.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"


GameObject::GameObject(char *pathToTexture, RendererWindow *rendererWindow) {

    m_rendererWindow = rendererWindow;

    m_rendererWindow->m_rendererMutex.lock();
    m_texture = IMG_LoadTexture(m_rendererWindow->getRenderer(), pathToTexture);
    m_rendererWindow->m_rendererMutex.unlock();

    if (m_texture == nullptr)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    m_position = Vector2::zero();
    m_scale = Vector2::one();
    m_sourceTextureRect.x = 0;
    m_sourceTextureRect.y = 0;
    SDL_Point size = getsize();
    m_sourceTextureRect.w = size.x;
    m_sourceTextureRect.h = size.y;
}

GameObject::GameObject(RendererWindow *rendererWindow) {
    m_rendererWindow = rendererWindow;

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 32;
    rect.h = 32;

    m_rendererWindow->m_rendererMutex.lock();
    m_texture = SDL_CreateTexture(rendererWindow->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32,
                                  32);
    SDL_SetRenderTarget(rendererWindow->getRenderer(), m_texture);


    SDL_SetRenderDrawColor(rendererWindow->getRenderer(), 0, 0, 0, 0);
    SDL_RenderClear(rendererWindow->getRenderer());

    SDL_SetRenderDrawColor(rendererWindow->getRenderer(), 214, 17, 212, 255);
    SDL_RenderDrawRect(rendererWindow->getRenderer(), &rect);
    SDL_RenderDrawLine(rendererWindow->getRenderer(), 0, 0, 32, 32);


    SDL_SetRenderTarget(rendererWindow->getRenderer(), nullptr);
    m_rendererWindow->m_rendererMutex.unlock();

    m_position = Vector2::zero();
    m_scale = Vector2::one();
    m_sourceTextureRect.x = 0;
    m_sourceTextureRect.y = 0;
    SDL_Point size = getsize();
    m_sourceTextureRect.w = size.x;
    m_sourceTextureRect.h = size.y;
}

GameObject::GameObject() {
    m_texture = nullptr;
    m_activeSelf = false;
    m_angle = 0;
    m_position = Vector2::zero();
    m_scale = Vector2::one();
    m_rendererWindow = nullptr;
}

void GameObject::setActive(bool active) {
    m_activeSelf = active;
}

SDL_Point GameObject::getsize() {
    SDL_Point size;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &size.x, &size.y);
    return size;
}

SDL_Rect *GameObject::getSourceRect() {
    return &m_sourceTextureRect;
}

SDL_Rect *GameObject::getDestRect() {
    updateDestRect();
    return &m_destinationTextureRect;
}

SDL_Texture *GameObject::getTexture() {
    return m_texture;
}

bool GameObject::isActive() const {
    return m_activeSelf;
}

void GameObject::start() {
    m_mutex.lock();
    std::for_each(components.begin(), components.end(), [this](Component *component) {
        m_startThreadPool.add_task([component] {
            component->start();
        });
    });
    m_mutex.unlock();
}

void GameObject::update() {
    m_mutex.lock();
    std::for_each(components.begin(), components.end(), [](Component *component) {
        if (component != nullptr)
            component->update();
    });
    m_mutex.unlock();
}

void GameObject::fixedUpdate() {
    m_mutex.lock();
    std::for_each(components.begin(), components.end(), [](Component *component) {
        component->fixedUpdate();
    });
    m_mutex.unlock();
}

void GameObject::addComponent(Component *component) {
    component->gameObject = this;
    components.push_back(component);
}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::updateDestRect() {
    updateSourceRect();
    m_destinationTextureRect.w = m_sourceTextureRect.w * static_cast<int>(m_scale.m_x);
    m_destinationTextureRect.h = m_sourceTextureRect.h * static_cast<int>(m_scale.m_y);
    m_destinationTextureRect.x = static_cast<int>(m_position.m_x) - m_destinationTextureRect.w / 2;
    std::unique_lock<std::mutex> lock(m_rendererWindow->m_rendererMutex);
    m_destinationTextureRect.y =
            m_rendererWindow->m_windowHeight - static_cast<int>(m_position.m_y) - m_destinationTextureRect.w / 2;
}

void GameObject::updateSourceRect() {
    m_sourceTextureRect.x = 0;
    m_sourceTextureRect.y = 0;
    SDL_Point size = getsize();
    m_sourceTextureRect.w = size.x;
    m_sourceTextureRect.h = size.y;
}




