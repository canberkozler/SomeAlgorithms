#include <iostream>
#include <chrono>
#include <thread>

int main(){
    std::thread timer([](){
        std::this_thread::sleep_for(std::chrono::minutes(1));
        std::cout << "Time's up!\n";
    });

    std::cout << "Thread just started!\n";

    timer.join();
}