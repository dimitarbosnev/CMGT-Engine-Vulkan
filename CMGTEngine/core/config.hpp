#ifndef CONFIG_HPP
#define CONFIG_HPP

#pragma once
#include<string>
#include<iostream>
#include <format>
#include<cassert>
using namespace std;
namespace cmgt {
	using id_t = uint32_t;
	template<typename T>
	class Singleton {
	public:
		static T& getInstance() {
			assert(_instance != nullptr && format("{} is not initalized!", typeid(T).name()).c_str());
			return *_instance;
		}
		static void destroyInstance() {
			assert(_instance != nullptr && format("{} is not initalized!", typeid(T).name()).c_str());
				delete _instance;
			_instance = nullptr;
		}
	protected:
		Singleton() = default;
		static void assignInstance(T* pInstance) {
			assert(_instance == nullptr && format("{} is already initalized!", typeid(T).name()).c_str());
			_instance = pInstance;
			cout << typeid(T).name() << " initalized successfuly!" << endl;
		}
	private:
		inline static T* _instance = nullptr;
		Singleton(const Singleton&) = delete;
		Singleton& operator= (const Singleton) = delete;
	};
}
#endif //CONFIG_HPP