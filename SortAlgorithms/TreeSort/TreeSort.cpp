#include<iostream>
#include<array>


struct Node 
{ 
    int key; 
    Node *left, *right; 
}; 
  
// A utility function to create a new BST Node 
Node *newNode(int item) 
{ 
    Node *temp = new Node; 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
  
// Stores inorder traversal of the BST 
// in arr[] 
template<std::size_t N>
void storeSorted(Node *root, std::array<int, N>& arr, int &i) 
{ 
    if (root){ 
        storeSorted(root->left, arr, i); 
        arr[i++] = root->key; 
        storeSorted(root->right, arr, i); 
    } 
} 
  
/* A utility function to insert a new 
   Node with given key in BST */
Node* insert(Node* node, int key) {
    /* If the tree is empty, return a new Node */
    if (!node) return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
  
    /* return the (unchanged) Node pointer */
    return node; 
} 
  
// This function sorts arr[0..n-1] using Tree Sort 
template<std::size_t N>
void treeSort(std::array<int, N>& arr){
    Node *root = nullptr; 

    for (std::size_t i{}; i<N; ++i) root = insert(root, arr[i]); 
  
    // Store inorder traversal of the BST 
    // in arr[] 
    int i{}; 
    storeSorted(root, arr, i); 
} 
  
int main(){
    std::array<int, 5> arr{5, 4, 7, 2, 11}; 
  
    treeSort(arr);
    
    std::cout << "Sorted Array: ";
    for (std::size_t i{}; i<arr.size(); ++i) 
        std::cout << arr[i] << " "; 
} 