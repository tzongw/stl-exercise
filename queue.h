//
//  queue.h
//

#ifndef queue_h
#define queue_h

#include <queue>
#include <optional>
#include <mutex>
#include <condition_variable>


template <typename T>
class Queue {
public:
    T poll() {
        std::unique_lock<std::mutex> lock(mtx_);
        while (queue_.empty()) {
            cond_.wait(lock);
        }
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }
    std::optional<T> peek() {
        std::unique_lock<std::mutex> lock(mtx_);
        if (queue_.empty()) {
            return std::nullopt;
        } else {
            T value = std::move(queue_.front());
            queue_.pop();
            return value;
        }
    }
    size_t push(T&& value) {
        std::unique_lock<std::mutex> lock(mtx_);
        queue_.push(std::forward<T>(value));
        cond_.notify_all();
        return queue_.size();
    }
private:
    std::mutex mtx_;
    std::condition_variable cond_;
    std::queue<T> queue_;
};


#endif /* queue_h */
