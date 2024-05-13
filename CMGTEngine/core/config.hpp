#ifndef CONFIG_HPP
#define CONFIG_HPP

#pragma once
#include<string>
#include<iostream>
#include <format>

using namespace std;
namespace config {
    //const string CMGT_MODEL_PATH("");
    //const string CMGT_TEXTURE_PATH("");
    const string CMGT_SHADER_PATH ("shaders/");
    //const string CMGT_FONT_PATH("");
}

namespace cmgt {
    using id_t = uint32_t;
    template<typename T>
    class Singleton {
    public:
        static T& getInstance() {
            if (_instance == nullptr)
                throw runtime_error(format("{} is not initalized!", typeid(T).name()));
            return *_instance;
        }
    protected:
        Singleton() = default;
        static void assignInstance(T* pInstance) {
            if (_instance != nullptr) { 
                delete pInstance; 
                throw runtime_error(format("{} is already initalized!", typeid(T).name()));
            }
            else if (_instance == nullptr) {
                _instance = pInstance;
                cout << typeid(T).name() << " initalized successfuly!" << endl;
            }
        }
            static void deleteInstance() {
                if(_instance != nullptr)
                    delete _instance;
                _instance = nullptr;
            }
    private:
        inline static T* _instance = nullptr;
        Singleton(const Singleton&) = delete;
        Singleton& operator= (const Singleton) = delete;
    };
}
#endif //CONFIG_HPP