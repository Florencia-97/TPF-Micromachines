#ifndef MICROMACHINES_SAFEEVENTQUEUE_H
#define MICROMACHINES_SAFEEVENTQUEUE_H

#include <bits/stdc++.h>
#include <fstream>
#include <arpa/inet.h>
#include <condition_variable>
#include <queue>
#include <mutex>

#include "Event.h"

class SafeEventQueue {
    std::queue<Event> q;
    std::mutex m;
    std::condition_variable cv;

public:
    explicit SafeEventQueue();
    ~SafeEventQueue();
    void push(Event& event);
    Event pop();

};

#endif //MICROMACHINES_SAFEEVENTQUEUE_H
