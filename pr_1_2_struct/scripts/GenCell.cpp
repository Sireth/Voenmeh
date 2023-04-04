#include "GenCell.h"
#include "../engine/GameObject.h"
#include "../engine/RendererWindow.h"

void GenCell::start() {

    gameObject->m_mutex.lock();
    gameObject->m_rendererWindow->m_rendererMutex.lock();
    gameObject->m_texture = SDL_CreateTexture(gameObject->m_rendererWindow->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 32,
                                  32);
    SDL_SetRenderTarget(gameObject->m_rendererWindow->getRenderer(), gameObject->m_texture);


    SDL_SetRenderDrawColor(gameObject->m_rendererWindow->getRenderer(), 150, 150, 150, 255);
    SDL_RenderClear(gameObject->m_rendererWindow->getRenderer());

    SDL_SetRenderTarget(gameObject->m_rendererWindow->getRenderer(), nullptr);
    gameObject->m_rendererWindow->m_rendererMutex.unlock();
    gameObject->m_mutex.unlock();

    m_cellMutex->lock();
    Cell cell = (*m_cells)[y*22+x];
    m_cellMutex->unlock();

    if(cell.m_walls[Cell::TOP]){
        auto obj = new GameObject("/home/sireth/rect8400.png",gameObject->m_rendererWindow);
        obj->m_position = gameObject->m_position;
        obj->m_angle = 90;
        gameObject->m_rendererWindow->instantiateGameObject(*obj);
    }
    if(cell.m_walls[Cell::BOTTOM]){
        auto obj = new GameObject("/home/sireth/rect8400.png",gameObject->m_rendererWindow);
        obj->m_position = gameObject->m_position;
        obj->m_angle = 270;
        gameObject->m_rendererWindow->instantiateGameObject(*obj);
    }
    if(cell.m_walls[Cell::LEFT]){
        auto obj = new GameObject( "/home/sireth/rect8400.png",gameObject->m_rendererWindow);
        obj->m_position = gameObject->m_position;
        obj->m_angle = 0;
        gameObject->m_rendererWindow->instantiateGameObject(*obj);
    }
    if(cell.m_walls[Cell::RIGHT]){
        auto obj = new GameObject( "/home/sireth/rect8400.png",gameObject->m_rendererWindow);
        obj->m_position = gameObject->m_position;
        obj->m_angle = 180;
        gameObject->m_rendererWindow->instantiateGameObject(*obj);
    }
}

void GenCell::update() {

}

void GenCell::fixedUpdate() {

}
