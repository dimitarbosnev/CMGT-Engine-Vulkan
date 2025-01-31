#ifndef EVENTS_H
#define EVENTS_H
#pragma once
#include <list>
namespace cmgt {
    
    class Event{
    public:
        Event();
        ~Event();
        void add(void(*function)()){
            subscribers.push_back(function);
        }

        void remove(void(*function)()){
            subscribers.remove(function);
        }

        void trigger(){
            for(void(*function)() : subscribers){
                function();
            }
        }
    private:
        std::list<void(*)()> subscribers;
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