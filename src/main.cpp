#include "EagerSingleton.h"
#include "LazySingleton.h"
#include "MeyersSingleton.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

class DCLSingleton {
public:
    static DCLSingleton* GetInstance() {
        if (instance_ == nullptr) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (instance_ == nullptr) {
                instance_ = new DCLSingleton();
            }
        }
        return instance_;
    }

private:
    DCLSingleton() = default;
    ~DCLSingleton() = default;

    static DCLSingleton* instance_;
    static std::mutex mutex_;
};

DCLSingleton* DCLSingleton::instance_ = nullptr;
std::mutex DCLSingleton::mutex_;

static bool isSameAddress(const std::vector<LazySingleton*>& values) {
    for (size_t i = 1; i < values.size(); ++i) {
        if (values[0] != values[i]) {
            return false;
        }
    }
    return true;
}

static bool isSameAddressDCL(const std::vector<DCLSingleton*>& values) {
    for (size_t i = 1; i < values.size(); ++i) {
        if (values[0] != values[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    const int threadCount = 20;
    std::atomic<bool> start{false};

    // 1. 饿汉式：程序启动时创建实例，天然线程安全
    EagerSingleton* eager1 = EagerSingleton::GetInstance();
    EagerSingleton* eager2 = EagerSingleton::GetInstance();
    std::cout << "[EagerSingleton] same instance? " << (eager1 == eager2) << std::endl;

    // 2. 懒汉式：加锁后线程安全
    std::vector<LazySingleton*> lazyResults(threadCount);
    std::vector<std::thread> lazyThreads;
    lazyThreads.reserve(threadCount);

    for (int i = 0; i < threadCount; ++i) {
        lazyThreads.emplace_back([&lazyResults, &start, i]() {
            while (!start.load()) {
                std::this_thread::yield();
            }
            lazyResults[i] = LazySingleton::GetSingleton();
        });
    }

    start.store(true);
    for (auto& t : lazyThreads) {
        t.join();
    }

    std::cout << "[LazySingleton] same instance across threads? " << isSameAddress(lazyResults) << std::endl;

    // 3. 双重检查锁：线程安全的懒汉式实现
    std::vector<DCLSingleton*> dclResults(threadCount);
    std::vector<std::thread> dclThreads;
    dclThreads.reserve(threadCount);

    for (int i = 0; i < threadCount; ++i) {
        dclThreads.emplace_back([&dclResults, &start, i]() {
            while (!start.load()) {
                std::this_thread::yield();
            }
            dclResults[i] = DCLSingleton::GetInstance();
        });
    }

    start.store(true);
    for (auto& t : dclThreads) {
        t.join();
    }

    std::cout << "[DCLSingleton] same instance across threads? " << isSameAddressDCL(dclResults) << std::endl;

    // 4. Meyers 单例：C++11 局部静态变量，线程安全
    MeyersSingleton& meyers1 = MeyersSingleton::GetMayerSinglten();
    MeyersSingleton& meyers2 = MeyersSingleton::GetMayerSinglten();
    std::cout << "[MeyersSingleton] same instance? " << (&meyers1 == &meyers2) << std::endl;

    return 0;
}
