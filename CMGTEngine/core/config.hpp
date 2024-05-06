#pragma once
#include<string>
#include<iostream>

using namespace std;
namespace config {
    //const string CMGT_MODEL_PATH("");
    //const string CMGT_TEXTURE_PATH("");
    const string CMGT_SHADER_PATH ("shaders/");
    //const string CMGT_FONT_PATH("");
}

namespace cmgt {
    template<typename T>
    class Singleton {
    public:
        static Singleton<T>& instance() {
            if (_instance == nullptr)
                _instance = new Singleton<T>();
            return *_instance;
        }
    protected:
        Singleton() = default;
    private:
        inline static Singleton<T>* _instance = nullptr;
        Singleton(const Singleton&) = delete;
        Singleton& operator= (const Singleton) = delete;
    };
}