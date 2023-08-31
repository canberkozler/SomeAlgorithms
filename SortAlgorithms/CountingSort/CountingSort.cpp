#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>

// Version 1
void counting_sort(std::vector<int>& ivec){
    // create an integer vector of size `n` to store the sorted array
    std::vector<int> output(ivec.size());
 
    // create an integer vector of size `MAX_ELEM+1`, initialized by all zero
    std::vector<int> freq(*max_element(begin(ivec),end(ivec))+1, 0);
 
    // 1. Using the value of each item in the input array as an index,
    // store each integer's count in `freq[]`
    for (size_t i{}; i < ivec.size(); ++i) {
        ++freq[ivec[i]];
    }
 
    // overwrite the input array with sorted order
    int index = 0;
    for (size_t i{}; i <freq.size(); ++i)
    {
        while (freq[i]--) {
            ivec[index++] = i;
        }
    }
}

// Version 2
static constexpr std::size_t range{256};

void counting_sort_2(std::vector<int> &vec) {
	// The vector containing the result.
	std::vector<int> output(vec.size(), 0);
	
	// The count vector.
	std::vector<int> count(range, 0);
	
	for (std::size_t i{}; i < vec.size(); ++i) {
		++count[vec[i]];
	}
	
	// Make count[i] contain the start position of the element in the output vector.
	for (std::size_t i{1}; i < count.size(); ++i) {
		count[i] += count[i-1];
	}
	
	// Build the output vector.
	for (std::size_t i{}; i < vec.size(); ++i) {
		output[count[vec[i]] - 1] = vec[i];
		--count[vec[i]];
	}
	
	for (std::size_t i{}; i < vec.size(); ++i) {
		vec[i] = output[i];
	}
}

void print(const std::vector<int>& test_vec) {
	for (auto elem: test_vec) {
		std::cout << elem << " ";
		
	}
	std::cout << "\n";
}
 
int main()
{
    std::cout<<"Counting Sort Version 1:\n";
    std::vector<int> ivec = { 4, 2, 10, 10, 1, 4, 2, 1, 10 };

    std::cout << "The container: ";
	print(ivec);

    counting_sort(ivec);
 
    std::cout << "The sorted container: ";
	print(ivec);
    std::cout<<"\n";
    
    std::cout<<"Counting Sort Version 2:\n";
    std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<int> dist(0, 255);

	std::vector<int> ivec2;

    std::generate_n(std::back_inserter(ivec2), 25, [&]{return dist(eng);});
	
	std::cout << "The container: ";
	print(ivec2);
	
	counting_sort_2(ivec2);
	
	std::cout << "The sorted container: ";
	print(ivec2);
}