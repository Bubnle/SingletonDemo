#pragma once

#include <mutex>

class SafeSingleton {
public:
    static SafeSingleton* GetInstance();

    SafeSingleton(const SafeSingleton&) = delete;
    SafeSingleton& operator=(const SafeSingleton&) = delete;

private:
    SafeSingleton() = default;
    ~SafeSingleton() = default;

    static SafeSingleton* instance_;
    static std::mutex mutex_;
};
