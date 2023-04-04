#ifndef TERM_2_THREADPOOL_H
#define TERM_2_THREADPOOL_H

#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <unordered_set>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool(uint32_t num_threads);

    template<typename Func, typename ...Args>
    int64_t add_task(const Func &task_func, Args &&... args) {
        int64_t task_idx = m_lastId++;

        std::lock_guard<std::mutex> q_lock(m_mutex);
        m_tasks.emplace(std::async(std::launch::deferred, task_func, args...), task_idx);
        m_condition.notify_one();
        return task_idx;
    }

    void wait(int64_t task_id);

    void wait_all();

    bool calculated(int64_t task_id);

    ~ThreadPool();

private:

    void run();

    std::queue<std::pair<std::future<void>, int64_t>> m_tasks;  // очередь задач - хранит функцию(задачу), которую нужно исполнить и номер данной задачи
    std::mutex m_mutex;
    std::condition_variable m_condition;

    std::unordered_set<int64_t> m_completedTaskIds;             // помещаем в данный контейнер исполненные задачи
    std::condition_variable m_completedTaskIdsCondition;
    std::mutex m_completedTaskIdsMutex;

    std::vector<std::thread> m_threads;


    std::atomic<bool> m_quite{false};                         // флаг завершения работы thread_pool
    std::atomic<int64_t> m_lastId = 0;                          // переменная хранящая id который будет выдан следующей задаче
};

#endif //TERM_2_THREADPOOL_H
