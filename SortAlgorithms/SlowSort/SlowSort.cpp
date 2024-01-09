#include <iostream>
#include <vector>
#include <utility>
#include <iterator>

void slow_sort(std::vector<int>& ivec, std::size_t i, std::size_t j){
    if (i >= j) return;
 
    std::size_t m = (i + j) / 2; // mid
 
    // Recursively call with the first half
    slow_sort(ivec, i, m);
 
    // Recursively call with the right half
    slow_sort(ivec, m + 1, j);
 
    if (ivec[j] < ivec[m]) {
        std::swap(ivec[j], ivec[m]);
    }
 
    slow_sort(ivec, i, j - 1);
}

int main()
{
    std::vector<int> ivec{ 6, 8, 9, 4, 12, 1 };
 
    slow_sort(ivec, 0, ivec.size()-1);

    std::cout << "Sorted vector is: ";
    std::copy(begin(ivec), end(ivec), std::ostream_iterator<int>{std::cout, " "});
}