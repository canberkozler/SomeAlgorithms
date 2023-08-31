#include <iostream>
#include <array>
#include <algorithm>
#include <string_view>
#include <type_traits>

// To heapify a subtree rooted with node i which is an index in container.
template<typename C>
void heapify(C& cont, std::size_t heap_size, std::size_t i){
	std::size_t largest{i}; // Initialize largest as root.
	std::size_t lft{2*i + 1};

	// If left child is larger than root.
	if (lft < heap_size && cont[lft] > cont[largest])
		largest = lft;

	std::size_t r8{2*i + 2};
	// If right child is larger than largest so far.
	if (r8 < heap_size && cont[r8] > cont[largest])
		largest = r8;

	// If largest is not root.
	if (largest != i){
		std::swap(cont[i], cont[largest]);

		// Recursively heapify the affected sub-tree.
		heapify(cont, heap_size, largest);
	}
}

template<typename C>
void heap_sort(C& cont){
	// Build heap (rearrange array).
	for (std::size_t i{cont.size() / 2}; i --> 0;)
		heapify(cont, cont.size(), i);

	// One by one extract an element from heap.
	for (std::size_t i{cont.size()}; i --> 0;){
		// Move current root to end.
		std::swap(cont[0], cont[i]);

		// Call max heapify on the reduced heap.
		heapify(cont, i, 0);
	}
}

template<typename C>
void println(std::string_view rem, const C& v){
    std::cout << rem;
    if constexpr (std::is_scalar<std::decay_t<decltype(v)>>::value)
        std::cout << v;
    else
        for (auto e : v)
            std::cout << e << ' ';
    std::cout << '\n';
}

int main(){
	std::array<int, 6> i_arr{12, 11, 13, 5, 6, 7};
	println("The container: ", i_arr);

	heap_sort(i_arr);

	println("The sorted container: ", i_arr);
}