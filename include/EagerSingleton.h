#pragma once
#include <bits/stdc++.h>
using namespace std;


class EagerSingleton{
    public:
        EagerSingleton(const EagerSingleton& eagerSingleton) = delete ;
        EagerSingleton& operator=(const EagerSingleton& eagerSingleton) = delete;

        EagerSingleton* GetInstance();

        

    private:

        EagerSingleton();
        ~EagerSingleton();

        static EagerSingleton* instance ;
        int mdata = 0;
};
