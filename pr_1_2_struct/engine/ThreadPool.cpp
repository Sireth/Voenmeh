#include "ThreadPool.h"

ThreadPool::ThreadPool(uint32_t num_threads) {
    m_threads.reserve(num_threads);

    for (uint32_t i = 0; i < num_threads; ++i) {
        m_threads.emplace_back(&ThreadPool::run, this);
    }
}

void ThreadPool::wait(int64_t task_id) {
    std::unique_lock<std::mutex> lock(m_completedTaskIdsMutex);
    m_completedTaskIdsCondition.wait(lock, [this, task_id]()->bool {
        return m_completedTaskIds.find(task_id) != m_completedTaskIds.end();
    });
}

void ThreadPool::wait_all() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_completedTaskIdsCondition.wait(lock, [this]()->bool {
        std::lock_guard<std::mutex> task_lock(m_completedTaskIdsMutex);
        return m_tasks.empty()/* && m_lastId == m_completedTaskIds.size()*/; // так как решили не жрать память
    });
}

bool ThreadPool::calculated(int64_t task_id) {
    std::lock_guard<std::mutex> lock(m_completedTaskIdsMutex);
    if (m_completedTaskIds.find(task_id) != m_completedTaskIds.end()) {
        return true;
    }
    return false;
}

ThreadPool::~ThreadPool() {
    m_quite = true;
    for (auto & m_thread : m_threads) {
        m_condition.notify_all();
        m_thread.join();
    }
}

void ThreadPool::run() {
    while (!m_quite) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this]()->bool { return !m_tasks.empty() || m_quite; });

        if (!m_tasks.empty()) {
            auto elem = std::move(m_tasks.front());
            m_tasks.pop();
            lock.unlock();

            elem.first.get();

            std::lock_guard<std::mutex> lock(m_completedTaskIdsMutex);
            //m_completedTaskIds.insert(elem.second); уменьшаем жор памяти

            m_completedTaskIdsCondition.notify_all();
        }
    }
}
