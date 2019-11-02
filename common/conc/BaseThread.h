

#ifndef MICROMACHINES_BASETHREAD_H
#define MICROMACHINES_BASETHREAD_H

#include <pthread.h>
#include <thread>
#include <atomic>

class BaseThread {
    std::thread t;
    std::atomic<bool> alive;
    bool running;

protected:
    virtual void _run() = 0;
public:

    BaseThread();

    void run();

    bool isAlive();

    bool isRunning();

    //POS closes the thread and prepares to join
    //isAlive returns false
    virtual void close();

    void join();

    BaseThread(BaseThread&& other);

    BaseThread& operator=(BaseThread&& other);

};


#endif //MICROMACHINES_BASETHREAD_H
