#include "avl-tree.h"
#include "binary-search-tree.h"
#include <iostream>

bool AVLTree::insert(DataType val) {
    alpha = nullptr;
    if(!BinarySearchTree::insert(val)){ // return false if the node already exists
        return false;
    }

    BinarySearchTree::updateNodeBalance(getRootNode());

    findAlpha(getRootNode()); //find alpha node
    if (alpha == nullptr) { //this means that the tree is balanced.
        return true;
    }

    if (alpha -> right != nullptr && alpha -> right -> right != nullptr && BinarySearchTree::exists(alpha->right->right->val)) {
        leftRotation();
        return true;

    } else if (alpha -> left != nullptr && alpha -> left -> left != nullptr && BinarySearchTree::exists(alpha->left->left->val)) {
        rightRotation();
        return true;

    } else if (alpha -> left != nullptr && alpha -> left -> right != nullptr && BinarySearchTree::exists(alpha->left->right->val)) {
        leftRightRotation();
        return true;

    } else if (alpha -> right != nullptr && alpha -> right -> left != nullptr && BinarySearchTree::exists(alpha->right->left->val)) {
        rightLeftRotation();
        return true;
    }

}

bool AVLTree::remove(DataType val)
{
    alpha = nullptr;
    if(!BinarySearchTree::remove(val)){ // return false if the node already exists
        return false;
    }

    BinarySearchTree::updateNodeBalance(getRootNode());
    findAlpha(getRootNode());

    if (alpha == nullptr) { //this means that the tree is balanced.
        return true;
    }

    if (val > getRootNode() -> val) { //if deleted from the right subtree
        if (alpha -> avlBalance == 2 && alpha -> left -> avlBalance == 1) {
            rightRotation();
            return true;
        }
        if (alpha -> avlBalance == 2 && alpha -> left -> avlBalance == -1) {
            leftRightRotation();
            return true;
        }
        if (alpha -> avlBalance == 2 && alpha -> left -> avlBalance == 0) {
            rightRotation();
            return true;
        }
    }

    if (val < getRootNode() -> val) { //if deleted from the left subtree
        if (alpha -> avlBalance == -2 && alpha -> right -> avlBalance == -1) {
            leftRotation();
            return true;
        }
        if (alpha -> avlBalance == -2 && alpha -> right -> avlBalance == 1) {
            rightLeftRotation();
            return true;
        }
        if (alpha -> avlBalance == -2 && alpha -> right -> avlBalance == 0) {
            leftRotation();
            return true;
        }
    }
}

void AVLTree::leftRotation() {

    Node* temp = new Node(alpha->val);
    temp -> left = alpha -> left;
    temp -> right = alpha -> right -> left; //replace with successor
    alpha->val = alpha -> right -> val;
    alpha -> left = temp;
    alpha -> right = alpha -> right -> right;
}

void AVLTree::rightRotation() {
    Node* temp = new Node(alpha-> val);
    temp -> right = alpha -> right;
    temp -> left = alpha -> left -> right; //replace with successor
    alpha -> val = alpha -> left -> val;
    alpha -> right = temp;
    alpha -> left = alpha -> left -> left;
}

void AVLTree::leftRightRotation(){
    Node * temp = alpha;
    alpha = alpha -> left;
    leftRotation();
    alpha = temp;
    rightRotation();
}

void AVLTree::rightLeftRotation(){
    Node *temp = alpha;
    alpha = alpha -> right;
    rightRotation();
    alpha = temp;
    leftRotation();
}

void AVLTree::findAlpha(Node *n) {
    if (n==nullptr) {
        return;
    }
    if(n -> avlBalance > 1 || n -> avlBalance <-1) { //start at root
        alpha = n;
    }
    findAlpha(n->left);
    findAlpha(n->right);
}




