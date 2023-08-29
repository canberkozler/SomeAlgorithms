#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

template <typename C>
void bubble_sort(C& container) {
    bool swapped;
    do {
        swapped = false;
        for (auto it = container.begin(); std::next(it) != container.end(); ++it) {
            if (*it > *std::next(it)) {
                std::iter_swap(it, std::next(it));
                swapped = true;
            }
        }
    } while (swapped);
}

template <typename C>
void bubble_sort_2(C& vec){
    bool swapped;
    for (std::size_t i = 0; i < vec.size() - 1; i++) {
        swapped = false;
        for (std::size_t j = 0; j < vec.size() - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                swapped = true;
            }
        }
  
        // If no two elements were swapped
        // by inner loop, then break
        if (!swapped)
            break;
    }
}

std::ostream& double_new_line(std::ostream& os){
    return os << "\n\n";
}

int main() {
    std::vector<int> vec = {5, 2, 9, 1, 5};
    std::list<double> lst = {3.14, 1.41, 2.71, 0.577};

    std::cout << "Original vector: ";
    for (auto num : vec)
        std::cout << num << ' ';

    std::cout << '\n';
    bubble_sort(vec);

    std::cout << "Sorted vector: ";
    for (auto num : vec)
        std::cout << num << ' ';

    std::cout << double_new_line;

    std::cout << "Original list: ";
    for (auto num : lst)
        std::cout << num << " ";

    std::cout << '\n';

    bubble_sort(lst);

    std::cout << "Sorted list: ";
    for (auto num : lst)
        std::cout << num << " ";

    std::cout << double_new_line;

    std::vector<int> vec2 = {5, 22, 76, 8, 1, 9, 11, 0, 1};

    std::cout << "BubbleSort2 original vector: ";
    for (auto num : vec2)
        std::cout << num << ' ';

    std::cout << '\n';
    bubble_sort_2(vec2);

    std::cout << "Sorted vector: ";
    for (auto num : vec2)
        std::cout << num << ' ';
}