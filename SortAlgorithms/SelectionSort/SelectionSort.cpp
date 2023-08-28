#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end)
{
    for (ForwardIt it = begin; it != end; ++it)
        std::iter_swap(it, std::min_element(it, end));
}

/*Average case complexity: n^2*/
template <typename T, typename C = std::less<>>
void selection_sort_2(std::vector<T>& vec, C cmp = C{}){
    for (std::size_t i = 0; i < vec.size(); i++){
        std::size_t min = i;
        for (std::size_t j = i + 1; j < vec.size(); j++)
            if (cmp(vec[j], vec[min]))
                min = j;
        std::swap(vec[i], vec[min]);
    }
}

template <typename T>
void print(const std::vector<T>& vec){
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << ' ';
}

std::ostream& double_new_line(std::ostream& os){
    return os << "\n\n";
}

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-99, +99);
    std::vector<int> ivec;
    std::generate_n(std::back_inserter(ivec), 20, std::bind(dist, gen));
    std::cout << std::showpos;
    std::cout << "Before selection_sort: ";
    print(ivec);
    selection_sort(ivec.begin(), ivec.end());
 
    std::cout << "\nAfter selection_sort: ";
    print(ivec);
    std::cout << double_new_line;

    std::shuffle(ivec.begin(), ivec.end(), gen); // mixes vector.

    std::cout << "Before selection_sort_2: ";
    print(ivec);
    selection_sort_2(ivec);
 
    std::cout << "\nAfter selection_sort_2: ";
    print(ivec);
    std::cout << double_new_line;

    std::shuffle(ivec.begin(), ivec.end(), gen); // mixes vector.

    std::cout << "Before selection_sort_2 (greater to less): ";
    print(ivec);
    selection_sort_2(ivec, std::greater{});
 
    std::cout << "\nAfter selection_sort_2 (greater to less): ";
    print(ivec);
    std::cout << double_new_line;
}