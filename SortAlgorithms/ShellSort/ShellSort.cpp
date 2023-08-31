#include <iostream>
#include <vector>
#include <algorithm>

template<typename C>
void shell_sort(C& cont){
    // Start with a big gap, then reduce the gap
    for (std::size_t gap{cont.size()/2}; gap > 0; gap /= 2){
        // Do a gapped insertion sort for this gap size.
        // The first gap elements cont[0..gap-1] are already in gapped order
        // keep adding one more element until the entire container is gap sorted 
        for (std::size_t i{gap}; i < cont.size(); ++i){
            // add cont[i] to the elements that have been gap sorted
            // save cont[i] in temp and make a hole at position i
            auto temp = cont[i];
 
            // shift earlier gap-sorted elements up until the correct 
            // location for cont[i] is found
            std::size_t j;            
            for (j = i; j >= gap && cont[j - gap] > temp; j -= gap)
                cont[j] = cont[j - gap];
             
            //  put temp (the original cont[i]) in its correct location
            cont[j] = temp;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& cont){
    for(auto elem : cont)
        os << elem << ' ';
    return os<<'\n';
}

int main(){
    std::vector<int> ivec {12, 34, 54, 2, 3};

    std::cout << "The container: " << ivec;

    shell_sort(ivec);

    std::cout << "The sorted container: "<< ivec;
}