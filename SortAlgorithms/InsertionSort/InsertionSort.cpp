#include <iostream>
#include <vector>
#include <functional>

/*
 * The worst-case time complexity of insertion sort is O(n^2), 
 * where n is the size of the input. The worst case happens when 
 * the container is reverse sorted. The best-case time complexity of 
 * insertion sort is O(n). The best case happens when the container 
 * is already sorted.
 *
 * The auxiliary space used by the iterative version is O(1) and O(n) 
 * by the recursive version for the call stack.
*/
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

// Recursive function to perform insertion sort.
template<typename C, typename Cmp = std::greater<>>
void insertion_sort_recursive(C& cont, std::size_t i = 1, Cmp cp = Cmp{}){// start from the second element (the element at index 0 is already sorted)
    auto temp = cont[i];
    auto j = i;

    while ((j > 0) && cp(cont[j - 1], temp)){
        cont[j] = cont[j - 1];
        --j;
    }
 
    cont[j] = temp;

    if (i < cont.size())
        insertion_sort_recursive(cont, i + 1);
}

template <typename T>
void print(const std::vector<T>& vec){
    for (std::size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << ' ';
}
 
int main(){
    std::vector ivec = { 3, 8, 5, 4, 1, 9, -2 };

    std::cout << "Before calling insertion_sort_iterative: ";
    print(ivec);

    insertion_sort_iterative(ivec);

    std::cout << "\nAfter calling insertion_sort_iterative: ";
    print(ivec);
    std::cout<<"\n\n";

    std::vector ivec2 = { 23, 56, 76, 2, -1, -78, 69 };
    
    std::cout << "Before calling insertion_sort_recursive: ";
    print(ivec2);

    insertion_sort_recursive(ivec2);

    std::cout << "\nAfter calling insertion_sort_recursive: ";
    print(ivec2);
    std::cout<<"\n\n";

    std::cout << "Before calling insertion_sort_iterative (greater to less): ";
    print(ivec);

    insertion_sort_iterative(ivec, std::less{});

    std::cout << "\nAfter calling insertion_sort_iterative (greater to less): ";
    print(ivec);
    std::cout<<"\n\n";
}