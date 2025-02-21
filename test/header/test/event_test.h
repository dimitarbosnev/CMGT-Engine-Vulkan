#include <vector>
#include <string>
#include <map>
#include "minimal/log.h"


class Subscriber{
    private: 
        int value;
    public:
        virtual void event(int a){ 
            std::stringstream ss;
            ss << "Value is: " << a;
            cmgt::Log::msg(ss.str());
        }
        void event2(){ 
            std::stringstream ss;
            ss << "Value is: " << value;
            cmgt::Log::msg(ss.str());
        }
};

class Sub : public Subscriber{
    private: 
        int value;
    public:
        virtual void event(int a){ 
            std::stringstream ss;
            ss << " Virtual Value is: " << a;
            cmgt::Log::msg(ss.str());
        }

        void newEvent(int a){
            std::stringstream ss;
            ss << " New Value is: " << a;
            cmgt::Log::msg(ss.str());
        }
};