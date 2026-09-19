#include "MeyersSingleton.h"

#include <bits/stdc++.h>
using namespace std;



MeyersSingleton::MeyersSingleton(){
    mdata = 0;
}

MeyersSingleton::~MeyersSingleton(){}


MeyersSingleton& MeyersSingleton::GetMayerSinglten(){
    static MeyersSingleton instance;
    return instance;
}


void MeyersSingleton::Business(){
    mdata++;
    cout << "MeyersSingleton call" <<endl;
}