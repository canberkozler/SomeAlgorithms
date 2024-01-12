#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void count_sort(std::vector<int>& ivec, int exp) {
    std::vector<int> output(ivec.size());
    std::vector<int> count(10,0);

    for (std::size_t i = 0; i < ivec.size(); ++i)
        count[(ivec[i] / exp) % 10]++;

    for (std::size_t i = 1; i < 10; ++i)
        count[i] += count[i - 1];

    for (std::size_t i{ivec.size()}; i-- > 0;) {
        output[count[(ivec[i] / exp) % 10] - 1] = ivec[i];
        --count[(ivec[i] / exp) % 10];
    }

    // Copy the output to the original array
    for (std::size_t i{}; i < ivec.size(); ++i)
        ivec[i] = output[i];
}

void radix_sort(std::vector<int>& ivec) {
    auto max_value = *std::max_element(ivec.begin(), ivec.end());
    for (int exp = 1; max_value / exp > 0; exp *= 10) {
        count_sort(ivec, exp);
    }
}

int main(){
    std::vector<int> ivec = { 543, 986, 217,312 , 23123, 2323111, 2};

    radix_sort(ivec);

    std::cout << "The sorted vector is: ";
    std::copy(ivec.begin(), ivec.end(), std::ostream_iterator<int>{std::cout, " "});
}