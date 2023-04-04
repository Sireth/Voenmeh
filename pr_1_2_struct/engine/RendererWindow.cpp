#include <iostream>
#include "RendererWindow.h"

RendererWindow::RendererWindow(const char *title, int weight, int height) : m_isRun(false), m_windowWeight(weight), m_windowHeight(height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, weight, height,
                                SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return;
    }
    std::unique_lock<std::mutex> lock(m_rendererMutex);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

void RendererWindow::startGameLoop() {
    m_isRun = true;
    m_mainRenderLoopThread = std::thread(&RendererWindow::update, this);
    m_mainFixedLoopThread = std::thread(&RendererWindow::fixedUpdate, this);
    m_mainRenderLoopThread.join();
    m_mainFixedLoopThread.join();
}

void RendererWindow::finishGameLoop() {
    m_isRun = false;

    m_objectsUpdateThreadPool.wait_all();
    m_objectsFixedUpdateThreadPool.wait_all();
    m_objectsStartThreadPool.wait_all();
    m_objectsMutex.lock();
    m_objectsOnScene.clear();
    m_objectsMutex.unlock();
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void RendererWindow::update() {
    int fps =0;
    auto startFps = std::chrono::high_resolution_clock::now(); // запоминаем начальное время для подсчета FPS

    while (m_isRun) {
        auto start = std::chrono::high_resolution_clock::now(); // запоминаем начальное время

        std::chrono::duration<double, std::milli> elapsed_fps =
                start - startFps; // вычисляем прошедшее время
        if(elapsed_fps.count() >= 1000){ // если прошла одна секунда
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
            startFps = start;
        }
        m_rendererMutex.lock();
        SDL_RenderClear(m_renderer); //Очистка рендера

        SDL_SetRenderDrawColor(m_renderer, 200, 200, 200, SDL_ALPHA_OPAQUE); // фон (временно)


        m_rendererMutex.unlock();
        m_objectsMutex.lock();
        std::for_each(m_objectsOnScene.begin(), m_objectsOnScene.end(),
                      [this](GameObject *object) {
                          render(object);
                      }); // запускаем рендер всех объектов
        m_objectsMutex.unlock();
        m_rendererMutex.lock();
        SDL_RenderPresent(m_renderer); //Погнали!!
        m_objectsUpdateThreadPool.wait_all();// ожидаем окончание всех задач
        m_rendererMutex.unlock();
        auto end = std::chrono::high_resolution_clock::now(); // узнаем конечное время
        std::chrono::duration<double, std::milli> elapsed_ms =
                end - start; // рассчитываем разницу в времени (сколько времени работал код)
        std::chrono::duration<double, std::milli> sleep_ms(
                (1000./120) - elapsed_ms.count()); // узнаем какую задержку нужно сделать


        if (sleep_ms.count() > 0) {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(sleep_ms)); // задержка
        }

        fps++; // счетчик кадров
    }
}

void RendererWindow::render(GameObject *object) {
    if (object->isActive()) { // проверяем активен ли объект

        this->m_objectsUpdateThreadPool.add_task([object] { // добавляем функцию update у каждого объекта в пул потоков
            object->update();
        });
        object->m_mutex.lock();
        SDL_Rect *s = object->getSourceRect();
        SDL_Rect *d = object->getDestRect();
        object->m_mutex.unlock();
        m_rendererMutex.lock();
        SDL_RenderCopyEx(m_renderer, object->getTexture(), s,d,object->m_angle, nullptr, SDL_FLIP_NONE); //Копируем в рендер объект
        m_rendererMutex.unlock();
    }
}

void RendererWindow::fixedUpdate() {
    SDL_Event event;
    while (m_isRun) {
        auto start = std::chrono::high_resolution_clock::now(); // запоминаем начальное время


            m_objectsMutex.lock();
            std::for_each(m_objectsOnScene.begin(), m_objectsOnScene.end(), //перебираем все объекты на сцене
                          [this](GameObject *object) {

                              if (object->isActive()) { // проверяем активен ли объект
                                  this->m_objectsFixedUpdateThreadPool.add_task(
                                          [object] { // добавляем функцию fixedUpdate у каждого объекта в пул потоков

                                              object->fixedUpdate();

                                          });
                              }

                          });
            m_objectsMutex.unlock();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_isRun = false;
                SDL_Delay(100);
                return finishGameLoop();
            }

        }

        // m_objectsFixedUpdateThreadPool.wait_all(); // ожидаем окончание всех задач

        auto end = std::chrono::high_resolution_clock::now(); // узнаем конечное время

        std::chrono::duration<double, std::milli> elapsed_ms =
                end - start; // рассчитываем разницу в времени (сколько времени работал код)
        std::chrono::duration<double, std::milli> sleep_ms(
                20 - elapsed_ms.count()); // узнаем какую задержку нужно сделать

        if (sleep_ms.count() > 0) {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(sleep_ms)); // задержка
        }
    }
}

void RendererWindow::instantiateGameObject(GameObject &gameObject) {
    m_instanceMutex.lock();
    m_objectsMutex.lock();
    m_objectsOnScene.push_back(&gameObject);
    m_objectsMutex.unlock();
    m_objectsStartThreadPool.add_task([&gameObject] {
        gameObject.start();
    });


    m_instanceMutex.unlock();
}

SDL_Renderer *RendererWindow::getRenderer() {
    return m_renderer;
}

