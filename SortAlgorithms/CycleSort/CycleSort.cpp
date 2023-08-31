#include <iostream>
#include <vector>
#include <utility>

// Warn: Cycle sort is an in-place, unstable sorting algorithm that is particularly 
// useful when sorting arrays containing elements with a small range of values.
void cycle_sort(std::vector<int>& cont){
    if(cont.empty())
        std::cerr << "Empty Container!\n";

    // Holds number of swapping.
    int writes{};
 
    // traverse container elements and put it to on the right place.
    for (std::size_t cycle_start{}; cycle_start < cont.size() - 1; ++cycle_start) {
        // Init item as starting point.
        int item = cont[cycle_start];
 
        // Find position where we put the item. We basically
        // count all smaller elements on right side of item.
        std::size_t pos{cycle_start};
        
        for (std::size_t i{cycle_start + 1}; i < cont.size(); ++i){
            if (cont[i] < item)
                ++pos;
        }
 
        // If item is already in correct position.
        if (pos == cycle_start)
            continue;
 
        // Ignore all duplicate  elements.
        while (item == cont[pos])
            ++pos;
 
        // Put the item to it's right position.
        if (pos != cycle_start){
            std::swap(item, cont[pos]);
            ++writes;
        }

        // Rotate rest of the cycle.
        while (pos != cycle_start){
            pos = cycle_start;

            // Find position where we put the element.
            for (std::size_t i{cycle_start + 1}; i < cont.size(); ++i)
                if (cont[i] < item)
                    ++pos;

            while (item == cont[pos])
                ++pos;

            // Put the item to it's right position.
            if (item != cont[pos]){
                std::swap(item, cont[pos]);
                ++writes;
            }
        }
    }

    std::cout << "Count of swaps: " << writes << "\n";
}

int main(){
    std::vector<int> ivec{ 1, 8, 3, 9, 10, 10, 2, 4 };
    std::cout << "Container : ";
    for (auto elem: ivec)
        std::cout << elem << " ";
    std::cout<<"\n";

    cycle_sort(ivec);

    std::cout << "After sort : ";
    for (auto elem: ivec)
        std::cout << elem << " ";
    std::cout<<"\n";
}