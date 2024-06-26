#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <functional>

using namespace std::chrono_literals;

template <typename Rep, typename Period>
std::future<void> timer(std::chrono::duration<Rep, Period> dur, std::function<void()> callback){
    return std::async(std::launch::async, [dur, callback](){
        std::this_thread::sleep_for(dur);
        callback();
    });
}

int main(){
    auto future = timer(1min, [](){std::cout << "Time's up!\n";});

    while(true){
        // do work...
        std::cout << "Counting...\n";
        std::this_thread::sleep_for(1ms);

        auto status = future.wait_for(1ms);
        if(status == std::future_status::ready)
            break;
    }
    std::cout << "Finito!\n";
}