#include <iostream>
#include <chrono>

void count(std::chrono::nanoseconds s){
    const auto start = std::chrono::high_resolution_clock::now();

    while(std::chrono::high_resolution_clock::now() - start < s);
    std::cout << "Time's up!\n";
}

int main() {
    count(std::chrono::seconds(3));
}