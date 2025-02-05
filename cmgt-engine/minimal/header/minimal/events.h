#ifndef EVENTS_H
#define EVENTS_H
#pragma once
#include <list>
#include <map>
#include <functional>
namespace cmgt {
    template<typename Class>
    class Event{
    public:
        Event() = default;
        ~Event() = default;
        inline void add(void(Class::*function)(), Class* sub){
            subscribers.emplace(function,sub);
        }

        inline void remove(void(Class::*function)(), Class* sub){
            subscribers.erase(function);
        }

        inline void trigger(){
            for(std::pair<void(Class::*)(),Class*> event : subscribers){
                (event.second->*event.first)();
            }
        }
    private:
        std::map<void(Class::*)(),Class*> subscribers;
    };

    template<typename Class, typename Type>
    class EventType{
    public:
        EventType() = default;
        ~EventType() = default;
        inline void add(Class* sub, void(Class::*function)(Type)){
            auto pair = std::pair<Class*,void(Class::*)(Type)>(sub,function);
            subscribers.push_back(pair);
        }

        //TODO: Figure out how to remove it
        //inline void remove(Class* sub, void(Class::*function)(Type)){
        //    subscribers.erase(sub);
        //}

        inline void trigger(Type type){
            for(auto event : subscribers){
                (event.first->*event.second)(type);
            }
        }
    private:
        std::list<std::pair<Class*,void(Class::*)(Type)>> subscribers;
    };

    template<typename T>
    class EventBus{
    public:
        EventBus() = delete;
        ~EventBus() = delete;
        inline static void add(void(*function)(T)){
            subscribers.push_back(function);
        }

        inline static void remove(void(*function)(T)){
            subscribers.remove(function);
        }

        inline static void trigger(T data){
            for(void(*function)(T) : subscribers){
                function(data);
            }
        }
    private:
        inline static std::list<void(*)(T)> subscribers;
    };

}
#endif //EVENTS_H