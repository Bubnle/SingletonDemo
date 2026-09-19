#include "EagerSingleton.h"
#include "LazySingleton.h"
#include "MeyersSingleton.h"
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

// =========================================================
// 测试 1：饿汉式单例（不考虑线程锁）
// =========================================================

int testEagerSingleton() {
    EagerSingleton* a = EagerSingleton::GetInstance();
    EagerSingleton* b = EagerSingleton::GetInstance();

    std::cout << "\n=========================" << std::endl;
    std::cout << "测试1 饿汉式单例" << std::endl;
    std::cout << "a == b ? " << (a == b) << std::endl;
    std::cout << "地址：" << a << " | " << b << std::endl;
    std::cout << "=========================" << std::endl;

    return 0;
}

// =========================================================
// 测试 1.1：饿汉式单例多线程测试（线程安全）
// =========================================================

int testEagerSingletonThreadSafe() {
    const int threadCount = 20;
    std::vector<EagerSingleton*> results(threadCount);
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    // 多线程同时调用 GetInstance()，这里不做任何额外加锁
    // 因为饿汉式在程序启动时已经创建了对象，所以它本身是线程安全的
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back([&results, i]() {
            results[i] = EagerSingleton::GetInstance();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    bool same = true;
    for (int i = 1; i < threadCount; ++i) {
        if (results[0] != results[i]) {
            same = false;
            break;
        }
    }

    std::cout << "\n=========================" << std::endl;
    std::cout << "测试1.1：饿汉式单例多线程安全性" << std::endl;
    std::cout << "多线程下是否仍然是同一个实例：" << same << std::endl;
    for (int i = 0; i < threadCount; ++i) {
        std::cout << "线程 " << i << " 地址：" << results[i] << std::endl;
    }
    std::cout << "=========================" << std::endl;

    return 0;
}

// =========================================================
// 测试 2：懒汉式单例（无锁版本，直接测试是否会出现多个实例）
// =========================================================

int testLazySingletonWithoutLock() {
    const int threadCount = 20;
    std::vector<LazySingleton*> results(threadCount);
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    // 多线程同时调用 GetSingleton()，每个线程都尝试获取单例对象
    // 这里不加锁，用来观察是否会产生多个不同的实例
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back([&results, i]() {
            results[i] = LazySingleton::GetSingleton();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    bool same = true;
    for (int i = 1; i < threadCount; ++i) {
        if (results[0] != results[i]) {
            same = false;
            break;
        }
    }

    std::cout << "\n=========================" << std::endl;
    std::cout << "测试2 懒汉式单例 无锁 " << std::endl;
    std::cout << "多线程下是否仍然是同一个实例：" << same << std::endl;
    for (int i = 0; i < threadCount; ++i) {
        std::cout << "线程 " << i << " 地址：" << results[i] << std::endl;
    }
    std::cout << "=========================" << std::endl;

    return 0;
}

// =========================================================
// 测试 3：双重检查锁单例（线程安全版本）
// =========================================================

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

int testDCLSingleton() {
    const int threadCount = 20;
    std::vector<DCLSingleton*> results(threadCount);
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    // 多线程同时调用 GetInstance()，观察是否所有线程拿到的是同一个对象
    // 这里使用双重检查锁机制，属于线程安全实现
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back([&results, i]() {
            results[i] = DCLSingleton::GetInstance();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    bool same = true;
    for (int i = 1; i < threadCount; ++i) {
        if (results[0] != results[i]) {
            same = false;
            break;
        }
    }

    std::cout << "\n=========================" << std::endl;
    std::cout << "测试3 双重检查锁单例（线程安全）" << std::endl;
    std::cout << "多线程下是否仍然是同一个实例：" << same << std::endl;
    for (int i = 0; i < threadCount; ++i) {
        std::cout << "线程 " << i << " 地址：" << results[i] << std::endl;
    }
    std::cout << "=========================" << std::endl;

    return 0;
}

// =========================================================
// 测试 4：Meyers 单例多线程测试（线程安全）
// =========================================================

int testMeyersSingletonThreadSafe() {
    const int threadCount = 20;
    std::vector<MeyersSingleton*> results(threadCount);
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    // 多线程同时调用 GetMayerSinglten()，观察所有线程是否拿到同一个对象
    // Meyers 单例使用局部静态变量，C++11 后在多线程环境下是线程安全的
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back([&results, i]() {
            results[i] = &MeyersSingleton::GetMayerSinglten();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    bool same = true;
    for (int i = 1; i < threadCount; ++i) {
        if (results[0] != results[i]) {
            same = false;
            break;
        }
    }

    std::cout << "\n=========================" << std::endl;
    std::cout << "测试4：Meyers 单例多线程安全性" << std::endl;
    std::cout << "多线程下是否仍然是同一个实例：" << same << std::endl;
    for (int i = 0; i < threadCount; ++i) {
        std::cout << "线程 " << i << " 地址：" << results[i] << std::endl;
    }
    std::cout << "=========================" << std::endl;

    return 0;
}

int main() {
    testEagerSingleton();
    testEagerSingletonThreadSafe();
    testLazySingletonWithoutLock();
    testDCLSingleton();
    testMeyersSingletonThreadSafe();

    return 0;
}
