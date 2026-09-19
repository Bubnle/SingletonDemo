#include "LazySingleton.h"
#include <iostream>
#include <mutex>
using namespace std;

LazySingleton* LazySingleton::instance = nullptr;
std::mutex LazySingleton::mutex_;

LazySingleton::LazySingleton(){
    mdata = 0;
}

LazySingleton::~LazySingleton(){}

LazySingleton* LazySingleton::GetSingleton(){
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance == nullptr) {
        instance = new LazySingleton();
    }
    return instance;
}

void LazySingleton::Business(){
    mdata++;
    cout << "Lazy call" <<endl ;
}