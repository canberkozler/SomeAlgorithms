#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>

/* Cocktail Sort is a variation of Bubble sort. 
 * The Bubble sort algorithm always traverses elements from left and moves the largest 
 * element to its correct position in the first iteration and second-largest in the second 
 * iteration and so on. Cocktail Sort traverses through a given array in both directions alternatively. 
 * Cocktail sort does not go through the unnecessary iteration making it efficient for large arrays.
 */
template<typename C, typename Cmp = std::greater<>>
void CocktailSort(C& cont, Cmp cp = Cmp{}){
    bool swapped{true};
    std::size_t start{}, end{cont.size()-1};
 
    while (swapped){
        // reset the swapped flag on entering
        // the loop, because it might be true from
        // a previous iteration.
        swapped = false;
 
        for (std::size_t i{start}; i < end; ++i){
            if (cp(cont[i], cont[i + 1])){
                std::swap(cont[i], cont[i+1]);
                swapped = true;
            }
        }

        if (!swapped)
            break; // if container is sorted, then break.
 
        
        swapped = false; // reset the swapped flag to use next step.
 
        // move the end point back by one, because item at the end is in its rightful spot.
        --end;
 
        for (std::size_t i{end}; i--> start;){
            if (cp(cont[i], cont[i + 1])){
                std::swap(cont[i], cont[i+1]);
                swapped = true;
            }
        }
 
        // increase the starting point, because the last stage would have moved the next
        // smallest number to its rightful spot.
        ++start;
    }
}
 
int main(){
    std::vector<int> ivec{5, 1, 4, 2, 8, 0, 2};
    std::cout<<"The container: ";
    std::generate_n(std::ostream_iterator<int>{std::cout, " "}, ivec.size(), [&ivec]() {
        static size_t index = 0;
        return ivec[index++];
    });

    CocktailSort(ivec);

    std::cout<<"\nThe sorted contianer: ";
    std::generate_n(std::ostream_iterator<int>{std::cout, " "}, ivec.size(), [&ivec]() {
        static size_t index = 0;
        return ivec[index++];
    });

    CocktailSort(ivec, std::less<>{});

    std::cout<<"\nThe sorted contianer(Greater to less): ";
    std::generate_n(std::ostream_iterator<int>{std::cout, " "}, ivec.size(), [&ivec]() {
        static size_t index = 0;
        return ivec[index++];
    });
}