#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <iostream> 
#include <functional>
#include <unordered_map>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

class EventManager {
public:
    using Callback = std::function<void(int)>;

    static EventManager& getInstance() {
        static EventManager instance;
        return instance;
    }

    void subscribe(const std::string& event, Callback callback) {
        std::lock_guard<std::mutex> lock(mutex_);
        listeners[event].push_back(callback);
    }

    void queueEvent(const std::string& event, int value) {
        std::lock_guard<std::mutex> lock(mutex_);
        eventQueue.push({event, value});
        cv.notify_one();
    }

    void processEvents() {
        while (running) {
            std::unique_lock<std::mutex> lock(mutex_);
            cv.wait(lock, [this] { return !eventQueue.empty() || !running; });

            while (!eventQueue.empty()) {
                auto [event, value] = eventQueue.front();
                eventQueue.pop();

                if (listeners.find(event) != listeners.end()) {
                    for (auto& callback : listeners[event]) {
                        callback(value);
                    }
                }
            }
        }
    }

    void start() {
        running = true;
        eventThread = std::thread(&EventManager::processEvents, this);
    }

    void stop() {
        running = false;
        cv.notify_all();
        if (eventThread.joinable()) {
            eventThread.join();
        }
    }

private:
    std::unordered_map<std::string, std::vector<Callback>> listeners;
    std::queue<std::pair<std::string, int>> eventQueue;
    std::mutex mutex_;
    std::condition_variable cv;
    std::thread eventThread;
    bool running = false;
};

#endif // EVENTMANAGER_H
