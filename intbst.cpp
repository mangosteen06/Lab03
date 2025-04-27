// intbst.cpp
// Implements class IntBST
// Serafina Wong, 4/25

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(n == nullptr){
        return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
    n = nullptr;
    
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if(root == nullptr){
        root= new Node(value);
        return true;
    }else{
        return insert(value,root);
    }
   
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
   if(value == n->info){
        return false;
    }else if (value< n->info){
        if(n->left == nullptr){
            n->left = new Node(value);
            return true;
        }
        return insert(value, n->left);
    }else if(value >n->info){
         if(n->right == nullptr){
            n->right = new Node(value);
            return true;
        }
       return insert(value, n->right); 
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(n== nullptr) {
        return;
     }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
     printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
     if(n== nullptr) {
        return;
     }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
     if(n== nullptr){
        return;
     }
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
   return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(n== nullptr) {
        return 0;
     }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root); // REPLACE THIS NON-SOLUTION
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(n== nullptr) {
        return 0;
     }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
     if(n == nullptr){
        return NULL;
     }else if(value == n->info){
        return n;
    }else if (value< n->info){
        return getNodeFor(value, n->left);
    }else if(value >n->info){
       return getNodeFor(value, n->right); 
    }else{
        return NULL;
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if(getNodeFor(value,root)==NULL){
        return false;
    }else{
        return true;
    }
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
     Node*n = root;
     Node*result= nullptr;
     while(n != nullptr){
       if(value == n->info){
            if(n->left !=nullptr){
                n = n->left;
                while(n->right != nullptr){
                    n= n->right;
                }
                result = n;
            }
            return result;
        }else if(value <n->info){
            n = n->left;
        }else if(value >n->info){
            result = n;
            n = n->right;
        }
     }
     return result;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    if(!contains(value)||getPredecessorNode(value)==nullptr){
        return 0;
    }
    return getPredecessorNode(value)->info; 
    
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node*n = root;
     Node*result= nullptr;
     while(n != nullptr){
       if(value == n->info){
            if(n->right !=nullptr){
                n = n->right;
                while(n->left != nullptr){
                    n= n->left;
                }
                result = n;
            }
            return result;
        }else if(value <n->info){
            result = n;
            n = n->left;
        }else if(value >n->info){
            n = n->right;
        }
     }
     return result;
    
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    if(!contains(value)||getSuccessorNode(value)==nullptr){
        return 0;
    }
    return getSuccessorNode(value)->info; 
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    if (!contains(value)) {
        return false; 
    }
    Node* b;
    Node* p = nullptr;
    Node* n = getNodeFor(value,root);
    Node * iter = root;
    while (iter != nullptr && iter->info != value) {
        p=iter;
        if(value <iter->info){
            iter = iter->left;
        }else if(value >iter->info){
            iter = iter->right;
        }
    }
     if (n->left != nullptr && n->right != nullptr) {
        Node* New = getSuccessorNode(value);
        while (iter != nullptr && iter->info != New->info) {
            p=iter ;
            if (New->info < iter->info) {
                iter = iter->left;
            } else {
                iter = iter->right;
            }
    }
        n->info = New->info;
        n = New;
    }

    if(n->left != nullptr){
         b= n->left;
    }else{
        b= n->right; 
    }
    if (p == nullptr) {
        root = b;
    } else if (p->left == n) {
        p->left = b;
    } else {
        p->right = b;
    }

    delete n;
    return true;

    }

    

