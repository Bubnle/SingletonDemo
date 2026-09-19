#pragma once
#include <bits/stdc++.h>
using namespace std;

class LazySingleton {
    
    public:
        // 获取全局唯一的singlenton函数
        LazySingleton* GetSingleton();

        // 单例模式不支持赋值构造和拷贝构造
        LazySingleton(const LazySingleton& Singleton) = delete;
        LazySingleton& operator=(const LazySingleton) = delete;
        
        // 业务函数
        void Business();
    private:
        // 构造函数
        LazySingleton();
        ~LazySingleton();

        // 单例的singleton 
        static LazySingleton* instance;
        // 测试的数据
        int mdata ;
    
};