#ifndef _THREAD_
#define _THREAD_

#include <thread>

class Thread {
    std::thread thread;

    public:
    Thread();
    void start();
    void join();
    virtual void run() = 0; 
    virtual bool isAlive() = 0;
    virtual void stop() = 0;
    virtual ~Thread() {}                                             
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
};

#endif
