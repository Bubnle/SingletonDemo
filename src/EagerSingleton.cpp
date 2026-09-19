#include "EagerSingleton.h"

#include <iostream>
using namespace std;

// 定义这个在头文件当中声明过的 instance
EagerSingleton* EagerSingleton::instance = new EagerSingleton();

EagerSingleton::EagerSingleton(){}