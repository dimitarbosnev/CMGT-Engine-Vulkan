#ifndef EVENTS_H
#define EVENTS_H
#pragma once
#include <list>
#include <map>
#include <functional>
namespace cmgt {
   
    template<typename C>
    class Event{
    private:
        std::multimap<C*,void(C::*)()> listeners;
    public:
        void subscribe(C* sub,void(C::*func)()){
            listeners.emplace(sub,func);
        }
    
        void unsubscribe(C* sub,void(C::*func)()){
            
            for (auto it = listeners.begin(); it != listeners.end(); it++){
                if(it->first == sub && it->second == func){
                    listeners.erase(it);
                    break;
                }
            }
        }
        
        void call_event(){
            for(auto sub : listeners){
                //TODO: Consider using smart pointers in your project for high level stuff such as this
                //probably forgot to unsubscribe something
                //or a lambda you used got out of scope
                (sub.first->*sub.second)();
            }
        }
    };
    
    template<typename C, typename T>
    class EventType{
    private:
        std::multimap<C*,void(C::*)(T)> listeners;
    public:
        void subscribe(C* sub,void(C::*func)(T)){
            listeners.emplace(sub,func);
        }
    
        void unsubscribe(C* sub,void(C::*func)(T)){
            
            for (auto it = listeners.begin(); it != listeners.end(); it++){
                if(it->first == sub && it->second == func){
                    listeners.erase(it);
                    break;
                }
            }
        }
    
        void call_event(T data){
            for(auto sub : listeners){
                //TODO: Consider using smart pointers in your project for high level stuff such as this
                //probably forgot to unsubscribe something
                //or a lambda you used got out of scope
                (sub.first->*sub.second)(data);
            }
        }
    };
    
    template<typename C, typename T>
    class EventBus{
    private:
        inline static std::multimap<C*,void(C::*)(T)> listeners;
    public:
        EventBus() = delete;
        ~EventBus() = delete;
    
        static void subscribe(C* sub,void(C::*func)(T)){
            listeners.emplace(sub,func);
        }
    
        static void unsubscribe(C* sub,void(C::*func)(T)){
            
            for (auto it = listeners.begin(); it != listeners.end(); it++){
                if(it->first == sub && it->second == func){
                    listeners.erase(it);
                    break;
                }
            }
        }
    
        static void call_event(T data){
            for(auto sub : listeners){
                (sub.first->*sub.second)(data);
            }
        }
    };

}
#endif //EVENTS_H