#include <iostream>
#include <array>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iterator>

// Introsort is a hybrid sorting algorithm, uses three sorting algorithm to 
// minimise the running time, Quicksort, Heapsort and Insertion Sort. 

template<typename C, typename Cmp = std::greater<>>
void insertion_sort_iterative(C& cont, Cmp cp = Cmp{}){
    using elem_type = typename C::value_type;

    // start from the second element (the element at index 0 is already sorted)
    for (std::size_t i = 1; i < cont.size(); ++i)
    {
        elem_type temp = cont[i]; // elem_type can be replaced "auto".
        auto j = i;
 
        while ((j > 0) && cp(cont[j - 1], temp)){
            cont[j] = cont[j - 1];
            --j;
        }
 
        cont[j] = temp;
    }
}

int partition(int a[], int start, int end){
    int pivot = a[end];

    int pIndex = start;
 
    for (int i{start}; i < end; ++i){
        if (a[i] <= pivot){
            std::swap(a[i], a[pIndex]);
            ++pIndex;
        }
    }

    std::swap(a[pIndex], a[end]);

    return pIndex;
}

template<std::size_t N> // N: Size of Array
void introspective_sort_util(std::array<int, N>& i_arr, int begin, int end, int depthLimit) 
{ 
    auto size = end - begin + 1;
    if (size < 16) {
        insertion_sort_iterative(i_arr); 
        return; 
    }

    // If the depth is zero use heapsort 
    if (!depthLimit){
        std::make_heap(std::next(i_arr.begin(), begin), std::next(i_arr.begin(), end+1)); // end is not array.end(); thats why, add +1
        std::sort_heap(std::next(i_arr.begin(), begin), std::next(i_arr.begin(), end+1)); // end is not array.end(); thats why, add +1
        return;
    }
  
    int pivot = partition(i_arr.data(), begin, end);

    introspective_sort_util(i_arr, begin, pivot - 1, depthLimit - 1);
    introspective_sort_util(i_arr, pivot + 1, end, depthLimit - 1);
} 

 

template<std::size_t N> // N: Size of Array
void introspective_sort(std::array<int, N>& i_arr) { 
    int depthLimit = static_cast<int>(2 * std::log(N)); 
    introspective_sort_util(i_arr, 0, N-1, depthLimit); 
} 


int main() 
{
    std::array<int, 26> i_arr {3, 222, -11, 12322, -9, 2323, 23, 45, 67, 54, 34, 7, 90, 6, 45, 3, 23, 56, 7 - 2113, 32, -9, 167, 274, 222, 1236};

    introspective_sort(i_arr);
   
    std::cout << "Array after sort: ";
    std::copy(i_arr.begin(), i_arr.end(), std::ostream_iterator<int>{std::cout, " "});
} 