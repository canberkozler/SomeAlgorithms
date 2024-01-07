#include <list>
#include <iostream>
#include <iterator>
 
// A recursive function to implement Strand sort.
void strandSort(std::list<int>& ilist, std::list<int>& olist){
    if (ilist.empty())
        return;

    std::list<int> sublist;
    sublist.push_back(ilist.front());
    ilist.pop_front();

    for (auto it = ilist.begin(); it != ilist.end(); ) {
        if (*it > sublist.back()){
            sublist.push_back(*it);
            it = ilist.erase(it);
        } else std::advance(it, 1);
    }
 
    // Merge current sublist into output
    olist.merge(sublist);
 
    // Recur for remaining items in
    // input and current items in op.
    strandSort(ilist, olist);
}

int main(){
    std::list<int> ilist{10, 5, 30, 40, 2, 4, 9}, olist;

    strandSort(ilist, olist);

    for (auto&& x : olist)
        std::cout << x << " ";
}