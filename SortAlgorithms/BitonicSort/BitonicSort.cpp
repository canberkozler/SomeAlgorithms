#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

//Note that this sort algorithm works only when the number of elements to sort is 2^n.
enum class SortingDirection{Descending, Ascending};

template<typename C>
void compare_and_swap(C& cont, 
                      std::size_t i, 
                      std::size_t j, 
                      SortingDirection dir) 
{
    switch (dir){
        case SortingDirection::Descending:
            if(cont[i]<cont[j])
                std::swap(cont[i],cont[j]); 
            break;
        case SortingDirection::Ascending:
            if(cont[i]>cont[j])
                std::swap(cont[i],cont[j]); 
            break;
    
        default:
            std::cerr<<"Invalid Direction!\n";
            break;
    }
} 
  
/* 
 * It recursively sorts a bitonic sequence. 
 */
template<typename C>
void bitonic_merge(C& cont, 
                   std::size_t lower_bound, 
                   std::size_t number_of_elem, 
                   SortingDirection dir) 
{
    if (number_of_elem>1){
        std::size_t k {number_of_elem/2};

        for (std::size_t i{lower_bound}; i<lower_bound+k; ++i)
            compare_and_swap(cont, i, i+k, dir);

        bitonic_merge(cont, lower_bound, k, dir); 
        bitonic_merge(cont, lower_bound+k, k, dir); 
    } 
} 
  
/* 
 * Produces a bitonic sequence by recursively 
 * sorting its two halves in opposite sorting orders, and then 
 * calls bitonic_merge to make them in the same order.
 */
 
template<typename C>
void bitonic_sort(C& cont, 
                  std::size_t lower_bound, 
                  std::size_t number_of_elem, 
                  SortingDirection dir) 
{ 
    if (number_of_elem>1){
        std::size_t k {number_of_elem/2}; 

        bitonic_sort(cont, lower_bound, k, SortingDirection::Ascending); 

        bitonic_sort(cont, lower_bound+k, k, SortingDirection::Descending); 
  
        // Merge sequence in "dir" order. 
        bitonic_merge(cont,lower_bound, number_of_elem, dir); 
    } 
} 

template<typename C>
void sort(C& cont, SortingDirection dir) {
    bitonic_sort(cont, 0, cont.size(), dir); 
} 

int main(){
    std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution dist{0, 100};

    std::vector<int> ivec(32);
    std::generate(ivec.begin(), ivec.end(), [&]{ return dist(eng); });

    sort(ivec, SortingDirection::Ascending); 
  
    std::cout<<"Sorted array(Ascending): \n"; 
    for (std::size_t i{}; i<ivec.size(); ++i) 
       std::cout<< ivec[i] << " "; 
    std::cout <<"\n\n";

    sort(ivec, SortingDirection::Descending); 
  
    std::cout<<"Sorted array(Descending): \n"; 
    for (std::size_t i{}; i<ivec.size(); ++i) 
       std::cout<< ivec[i] << " "; 
}