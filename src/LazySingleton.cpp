#include "LazySingleton.h"
#include <iostream>
using namespace std;

LazySingleton::LazySingleton(){
    mdata = 0;
    instance = nullptr;
}

LazySingleton::~LazySingleton(){}

LazySingleton* LazySingleton::GetSingleton(){
    if(instance ==  nullptr){
        instance = new LazySingleton();
    }
    return instance;
}

void LazySingleton::Business(){
    mdata++;
    cout << "Lazy call" <<endl ;
}