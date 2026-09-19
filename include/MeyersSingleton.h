#pragma once

#include <bits/stdc++.h>

class MeyersSingleton{
    public:
        MeyersSingleton(const MeyersSingleton& meyersSingleton) = delete;
        MeyersSingleton& operator=(const MeyersSingleton& meyersSingleton) =delete;

        // MeyersSingleton 模式的get
        static MeyersSingleton& GetMayerSinglten();

        void Business();

    private:
        MeyersSingleton();
        ~MeyersSingleton();
        int mdata ;
};