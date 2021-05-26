#pragma once

#include <iostream>
#include <string>
#include <vector>


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
        Node *find(Node *n, T val);
        BinaryTree &add_root(T val);
        BinaryTree &add_left(T val, T new_val);
        BinaryTree &add_right(T val, T new_val);

        class Iterator{
            private:
                Node *pointer_to_current_node;
                void (*func)();
                std::vector<Node*> vec;

            public:
                Iterator(Node *ptr = nullptr, void (*selected_order)() = nullptr) : 
                pointer_to_current_node(ptr), func(selected_order){}
                static void pre_order() {};
                static void in_order() {};
                static void post_order() {};
                T &operator*() const {return pointer_to_current_node->value;}
                T *operator->()const{return &(pointer_to_current_node->value);}
                Iterator &operator++(){return *this;}
                Iterator operator++(int){return *this;}
                bool operator==(const Iterator &it) const {return false;}
                bool operator!=(const Iterator &it) const {return false;}
        };

       
        Iterator begin_inorder() {return Iterator(root, &Iterator::in_order);} 
        Iterator end_inorder() {return Iterator();} 
        Iterator begin_preorder() {return Iterator(root, &Iterator::pre_order);}
        Iterator end_preorder() {return Iterator();}
        Iterator begin_postorder() {return Iterator(root, &Iterator::post_order);}
        Iterator end_postorder() {return Iterator();}
        Iterator begin() { return begin_inorder(); };
        Iterator end() { return Iterator(); };

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree){
            return os << "my binary tree" << std::endl;
        }
    };

    template<typename T>
    typename BinaryTree<T>::Node *BinaryTree<T>::find(BinaryTree::Node *n, T val) {
        if (n == nullptr || n->value == val) {
            return n;
        }
        Node *find_left = find(n->left, val);
        Node *find_right = find(n->right, val);
        if (find_left == nullptr) {
            return find_right;
        } 
        else {
            return find_left;
        }
    }  

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_root(T val) {
        if (root == nullptr) { root = new Node{val}; } 
        else { root->value = val; }
        return *this;
    }

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_left(T val, T new_val) {
        Node *n = find(root, val);
        if (n == nullptr) {
            throw std::runtime_error("Error: val is not existing in the tree.\n");
        }
        if (n->left == nullptr) {
            n->left = new Node{new_val};
        } 
        else {
            n->left->value = new_val;
        }
        return *this;
    }

    template<typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(T val, T new_val) {
        Node *n = find(root, val);
        if (n == nullptr) {
            throw std::runtime_error("Error: existing_value is no exist in the tree.\n");
        }
        if (n->right == nullptr) {
            n->right = new Node{new_val};
        } 
        else {
            n->right->value = new_val;
        }
        return *this;
    }
} 