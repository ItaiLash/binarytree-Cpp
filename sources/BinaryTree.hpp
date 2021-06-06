#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
 
namespace ariel {

    template<typename T> 
    class BinaryTree {

        enum Order{ pre_order, in_order, post_order };

    //--------------------Node Class-------------------//
        class Node {
            public:
                T value;
                Node *right;
                Node *left;

                Node(T val) : value(val), right(nullptr), left(nullptr){}

                Node(const Node* other) : value(-1), right(nullptr), left(nullptr){
                    if(other != nullptr) {
                        value = other->value;
                        if(other->right != nullptr){
                            right = new Node(other->right); }
                        if(other->left != nullptr){
                            left = new Node(other->left); }
                    }
                }
        };
    //-----------------End Of Node Class-----------------//

    //--------------------Iterator Class-------------------//
        class Iterator {
            uint current;
            std::vector<Node*> order_by;

            void fill_by_order(Order order, Node* n){
                if(n != nullptr){
                    if(order == pre_order) {
                        order_by.push_back(n); 
                    }
                    fill_by_order(order, n->left);
                    if(order == in_order) {
                        order_by.push_back(n); 
                    }
                    fill_by_order(order, n->right);
                    if(order == post_order) {
                        order_by.push_back(n); 
                    }
                }
            }
            
            public:
                Iterator(Order order, Node* n) : current(0) {
                    fill_by_order(order, n); 
                    order_by.push_back(nullptr);
                    order_by.push_back(nullptr);
                    order_by.push_back(nullptr);
                }

                Iterator& operator++() {
                     current++; 
                     return *this;
                }

                Iterator operator++(int) {
                     Iterator itr = *this; 
                     current++; 
                     return itr;
                }

                T& operator*() const {
                     return order_by.at(current)->value; 
                }

                T* operator->() const {
                     return &(order_by.at(current)->value); 
                }

                bool operator==(Iterator const &other) const {
                     return order_by.at(current) == other.order_by.at(other.current); 
                }

                bool operator!=(Iterator const &other) const { 
                    return !(*this==other); 
                }
        };
        //-----------------End Of Iterator Class-----------------//

        Node* root;
        Node* find_node(Node *n ,T val) {
            if (n == nullptr || n->value == val) {
                return n;
            }            
            Node *find_left = find_node(n->left, val);
            if(find_left == nullptr) {
                return find_node(n->right, val);
            }
            return find_left;
        }

        void free_all(Node* n){
            if(n != nullptr) {
                free_all(n->right);
                free_all(n->left);
                delete n;
            }
        }

        public:
            BinaryTree() : root(nullptr){}

            BinaryTree(const BinaryTree& other) : root(new Node(other.root)){}

            BinaryTree(BinaryTree &&other) noexcept {
                root = other.root;
                other.root = nullptr;
            }

            ~BinaryTree() {
                free_all(root);
            }

            BinaryTree& operator=(BinaryTree&& other) noexcept {
                root = other._root;
                other._root = nullptr;
                return *this;
            }

            BinaryTree& operator=(const BinaryTree& other) {
                if (this == &other) {
                    return *this;
                }
                delete(this->root);
                root = new Node(other.root);
                return *this;
            }
                        
            BinaryTree& add_root(const T& val){
                if (root == nullptr) {
                     root = new Node{val}; 
                } 
                else {
                     root->value = val; 
                }
                return *this;
            }

            BinaryTree& add_right(const T& val, const T& new_val){
                Node *n = find_node(root, val);
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

            BinaryTree& add_left(const T& val, const T& new_val){
                Node *n = find_node(root, val);
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

            friend std::ostream& operator<<(std::ostream& os, const BinaryTree &tree){
                return os << "my binary tree" << std::endl;
            }

            Iterator begin_preorder() { return Iterator(Order::pre_order, root); }
            Iterator end_preorder() { return Iterator(Order::pre_order, nullptr); }
            Iterator begin_inorder() { return Iterator(Order::in_order, root);}
            Iterator end_inorder() { return Iterator(Order::in_order, nullptr);}
            Iterator begin_postorder(){ return Iterator(Order::post_order, root); }
            Iterator end_postorder(){ return Iterator(Order::post_order, nullptr);}
            Iterator begin(){ return begin_inorder(); }
            Iterator end(){ return end_inorder(); }
    };
};