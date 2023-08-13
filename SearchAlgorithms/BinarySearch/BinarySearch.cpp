#include <array>
#include <vector>
#include <set>
#include <iostream>
//simple binary searches

template<typename C>
int binarySearchRecursive(const C& con, int frstIdx,int LstIdx,int key){
    if(frstIdx<=LstIdx){
        int midIdx = frstIdx + (LstIdx - frstIdx) / 2;

        if (con[midIdx] == key) return midIdx; // returns the index if key is found.

        if (con[midIdx] < key) return binarySearchRecursive(con, midIdx + 1, LstIdx, key);
        else return binarySearchRecursive(con, frstIdx, midIdx - 1, key);
    }
    return -1; //key not found
}

template<typename C>
int binarySearchIterative(const C& con, int frstIdx,int LstIdx,int key){
    while (frstIdx <= LstIdx){
        int midIdx = frstIdx + (LstIdx - frstIdx) / 2;
        if (con[midIdx] < key){
           frstIdx = midIdx + 1;
        }
        else if (con[midIdx] > key){
           LstIdx = midIdx - 1;
        }
        else{
           return midIdx; // returns the index if key is found.
        }
    }
    return -1; // key not found
}

template<typename C>
int ternarySeach(const C& con, int frstIdx,int LstIdx,int key){
    if(LstIdx>=frstIdx){
        int midIdx1 = frstIdx + (LstIdx-frstIdx)/3;
        int midIdx2 = LstIdx -  (LstIdx-frstIdx)/3;
        
        if(ar[midIdx1] == key) return midIdx1;
        
        if(ar[midIdx2] == key) return midIdx2;

        if(key<ar[midIdx1]) return ternary_search(frstIdx,midIdx1-1,key);
        else if(key>ar[midIdx2]) return ternary_search(midIdx2+1,LstIdx,key);
        else return ternary_search(midIdx1+1,midIdx2-1,key);
    }
    return -1;
}

int main(){

}