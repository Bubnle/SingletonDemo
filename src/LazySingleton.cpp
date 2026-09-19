#include "LazySingleton.h"
#include <iostream>
#include <mutex>
using namespace std;

LazySingleton* LazySingleton::instance = nullptr;

LazySingleton::LazySingleton(){
    mdata = 0;
}

LazySingleton::~LazySingleton(){}

LazySingleton* LazySingleton::GetSingleton(){
    if (instance == nullptr) {
        instance = new LazySingleton();
    }
    return instance;
}

void LazySingleton::Business(){
    mdata++;
    cout << "Lazy call" <<endl ;
}