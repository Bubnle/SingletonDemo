#include "SafeSingleton.h"

SafeSingleton* SafeSingleton::instance_ = nullptr;
std::mutex SafeSingleton::mutex_;

SafeSingleton* SafeSingleton::GetInstance() {
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr) {
            instance_ = new SafeSingleton();
        }
    }
    return instance_;
}
