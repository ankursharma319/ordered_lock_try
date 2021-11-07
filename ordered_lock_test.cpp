
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <future>
#include <chrono>
#include <cmath>
#include <unistd.h>

class ordered_lock {
    std::condition_variable  cvar;
    std::mutex               cvar_lock;
    unsigned int             next_ticket, counter;
public:
    ordered_lock() : next_ticket(0), counter(0) {}
    void lock() {
        /*std::unique_lock<std::mutex> acquire(cvar_lock);
        unsigned int ticket = next_ticket++;
        while (ticket != counter)
            cvar.wait(acquire);*/
    }
    void unlock() {
        /*std::unique_lock<std::mutex> acquire(cvar_lock);
        counter++;
        cvar.notify_all();*/
    }
};

//ordered_lock lock;

float task(int n_iters) {
    float number = 1.00001;
    for (int i=0; i<pow(10, n_iters); i++) {
        number*=number;
        usleep(1*1000);
    }
    return number;
}

void test1() {
    //lock.lock();
    std::cout<<"test1 start"<<std::endl;
    std::cout<<task(6)<<std::endl;
    std::cout<<"test1 end"<<std::endl;
    //lock.unlock();
}

void test2() {
    //lock.lock();
    std::cout<<"test2 start"<<std::endl;
    std::cout<<task(3)<<std::endl;
    std::cout<<"test2 end"<<std::endl;
    //lock.unlock();
}

void test3() {
    //lock.lock();
    std::cout<<"test3 start"<<std::endl;
    std::cout<<task(4)<<std::endl;
    std::cout<<"test3 end"<<std::endl;
    //lock.unlock();
}

void test4() {
    //lock.lock();
    std::cout<<"test4 start"<<std::endl;
    std::cout<<task(2)<<std::endl;
    std::cout<<"test4 end"<<std::endl;
    //lock.unlock();
}

int main()
{
    std::cout<<"Hello ordered_lock_test"<<std::endl;
    using milli = std::chrono::milliseconds;
    auto start = std::chrono::high_resolution_clock::now();

    test1();
    test2();
    test3();
    test4();

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Synchronous Work took "
              << std::chrono::duration_cast<milli>(finish - start).count()
              << " milliseconds\n";
    
    start = std::chrono::high_resolution_clock::now();

    std::async(test1);
    std::async(test2);
    std::async(test3);
    std::async(test4);

    finish = std::chrono::high_resolution_clock::now();
    std::cout << "Async Work took "
            << std::chrono::duration_cast<milli>(finish - start).count()
            << " milliseconds\n";
    return 0;
}

// need to test if std::async() works with ordered_lock and its performance
// compare with synchronous calls
// maybe test the producer consumer pattern also
