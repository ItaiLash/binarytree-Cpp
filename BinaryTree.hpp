#pragma once
#include <iostream>
#include <ostream>
#include <vector>
#include <iomanip>
#include <cstring>

namespace ariel {

    template<typename T>
    class BinaryTree {

    private:
        struct Node {
            T value;
            Node *right, *left;

            Node(const T &value) : value(value), right(nullptr), left(nullptr) {}

            ~Node() {
                delete left;
                delete right;
            }
        }; 

        Node *root;

    public:
        BinaryTree() : root(nullptr) {}
        ~BinaryTree() { delete root; }
        BinaryTree &add_root(T value);
        BinaryTree &add_left(T existing_value, T new_value);
        BinaryTree &add_right(T existing_value, T new_value);
        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree);

        class Iterator{
        private:
            Node *node;

        public:
            Iterator(Node *ptr = nullptr) : node(ptr) {}
            T &operator*() const {return node->value;}
            Iterator &operator++() {return *this;}  //prefox
            Iterator operator++(int) {return *this;} //postfix
            bool operator==(const Iterator &it) const {return false;}
            bool operator!=(const Iterator &it) const {return false;}
            Iterator &operator=(const Iterator &iterator){return iterator;}
            T *operator->()const{T ans;
            return ans;}
        };

       
        Iterator begin_inorder() {return Iterator();} 
        Iterator end_inorder() {return Iterator();} 
        Iterator begin_preorder() {return Iterator();}
        Iterator end_preorder() {return Iterator();}
        Iterator begin_postorder() {return Iterator();}
        Iterator end_postorder() {return Iterator();}

    };

    ////////////////////////////////
    //////  Implementations:  //////
    ////////////////////////////////

    /*
     * BinaryTree:
     */

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_root(T value) {
        if (root == nullptr) 
        {
            root = new Node{value};
        } 
        else 
        {
            root->value = value;
        }
        return *this;
    }

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_left(T existing_value, T new_value) {
        return *this;
    }

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(T existing_value, T new_value) {
      
        return *this;
    }


} 