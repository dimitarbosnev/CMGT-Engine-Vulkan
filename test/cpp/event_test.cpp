#include "test/event_test.h"
#include "minimal/events.h"
#include <doctest/doctest.h>
#include <vector>
TEST_SUITE("Event Pattern Test") {
    TEST_CASE("Subscriber Test") {
        std::vector<Subscriber*> subscribers;
        cmgt::EventType<Subscriber,int> event;
        cmgt::Event<Subscriber> event2;

        for(int i = 0; i < 10; i++){
            Sub* sub = new Sub();
            subscribers.push_back(sub);
            event.subscribe(sub,&Subscriber::event);
            event2.subscribe(sub,&Subscriber::event2);
            cmgt::EventBus<Subscriber,int>::subscribe(sub,&Subscriber::event);
        }
        event.unsubscribe(subscribers[0],&Subscriber::event);
        event.call_event(10);
        event2.call_event();
        cmgt::EventBus<Subscriber,int>::call_event(5);
        CHECK(true);

        for(Subscriber* sub : subscribers){
            delete sub;
        }
        subscribers.clear();
    }
}
