#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

struct Node{
    std::string content;
    time_t timestamp;
    Node* left;
    Node* right;
    int height;
    Node(std::string &c): content(c), timestamp(time(nullptr)), left(nullptr), right(nullptr), height(0) {}
};

class AVLTree{
private:
    Node* root;

    int height(Node* node){
        return node? node->height : 0;
    }

    int balanceFactor(Node* node){
        return node? height(node->left) - height(node->right):0;
    }

    Node* rightRotate(Node* y){
        Node* x = y->left;
        Node* t2 = x->right;
        x->right = y;
        y->left = t2;
        y->height = std::max(height(y->left),height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* y){
        Node* x = y->right;
        Node* t1 = x->left;
        x->left = y;
        y->right = t1;
        y->height = std::max(height(y->left),height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* insertHelper(Node* node, std::string c){
        if(!node){
            return new Node(c);
        }
        node->right = insertHelper(node->right, c);
        node->height = 1 + std::max(height(node->left), height(node->right));
        int bf = balanceFactor(node);
        if(bf==-2){
            return leftRotate(node);
        }
        return node;
    }
    void deleteTree(Node* node) {
        if (node != nullptr) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
    void inorder(Node* node, std::vector<Node*>& vec) {
        if (!node) return;
        inorder(node->left, vec);
        vec.push_back(node);
        inorder(node->right, vec);
    }

public:
    AVLTree() : root(nullptr) {}
    void insert(const std::string& c) {
        root = insertHelper(root, c);
    }
    void outputN(int N){
        if(!root) return;
        std::vector<Node*> posts;
        inorder(root, posts);
        std::reverse(posts.begin(), posts.end());
        if(N==-1 || posts.size() < N) N = posts.size();
        for(int i=0; i<N; i++){
            std:: cout << posts[i]->content << std::endl;
        }
    }   
    ~AVLTree(){
        deleteTree(root);
    }

};

#endif