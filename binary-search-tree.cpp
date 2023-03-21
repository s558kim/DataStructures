#include "binary-search-tree.h"

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = nullptr;
    right = nullptr;
}

void BinarySearchTree::updateNodeBalance(Node* n)
{
    if (n == nullptr) {
        return;
    }

    n->avlBalance = getNodeDepth(n->left) - getNodeDepth(n->right);
    updateNodeBalance(n->left);
    updateNodeBalance(n->right);
}


int BinarySearchTree::getNodeDepth(Node* n) const
{
    if (n == nullptr)
    {
        return -1;
    }
    else
    {
        int leftdepth = getNodeDepth(n->left);
        int rightdepth = getNodeDepth(n->right);

        if (leftdepth > rightdepth) { // add 1 because depth starts at 0
            return leftdepth + 1;
        }

        return rightdepth + 1;
    }
}

BinarySearchTree::BinarySearchTree()
{
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{

}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const{

    Node * temp = root_;

    while (temp -> right != nullptr) {
        temp = temp -> right;
    }

    return temp -> val;
}

BinarySearchTree::DataType BinarySearchTree::min() const{

    Node * temp = root_;

    while (temp -> left != nullptr) {
        temp = temp -> left;
    }

    return temp -> val;
}

unsigned int BinarySearchTree::depth() const {

    if (size() == 1) { //if it only has the root node
        return 0;
    }

    return getNodeDepth(root_);

}

void BinarySearchTree::print() const
{

}

bool BinarySearchTree::exists(DataType val) const
{
    Node * temp = root_;

    while (temp != nullptr){
        if (temp->val == val) {
            return true;
        }
        if (temp->val > val) {
            temp = temp -> left;
        } else if (temp->val < val) {
            temp = temp -> right;
        }

    } return false;


}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {

    if (size_ == 0) { //if empty set root to new node
        root_ = new Node(val);
        size_++;
        return true;
    }

    if (exists(val)) { //if it exists then return false
        return false;
    }

    Node * temp = root_;

    while (temp != nullptr){
        if (val < temp -> val) {// if key is smaller than node's value, check left sub tree
            if (temp->left == nullptr) { //If the left child is empty, add a new node on the left.
                temp->left = new Node(val);
                size_++;
                return true;
            } else {
                temp = temp -> left; //if the left child is not empty, then go down towards the left
            }
        }

        if (val > temp -> val) {// if key is bigger than node's value, check right sub tree
            if (temp->right == nullptr) { //If the right child is empty, add a new node on the right.
                temp->right = new Node(val);
                size_++;
                return true;
            } else {
                temp = temp->right; //if the right child is not empty, then go down towards the right
            }
        }
    }
}

bool BinarySearchTree::remove(DataType val) {

    //FIRST SEARCH THE NODE UR REMOVING (THIS IS TEMP VARIABLE)
    //SEARCH PARENT OF THE NODE UR REMOVING (THIS IS PARENT VARIABLE)
    //1. If node to be deleted is a leaf node (no children), just delete the node.
    //2. If node to be deleted has one child, copy the child to the node and delete the child.
    //3. If node to be deleted has two children, first find the successor (or predecessor) of the node. Delete it. Replace the node to be deleted with the successor
    //Inorder Successor of a node in binary tree is the next node in Inorder traversal of the Binary Tree. Inorder Successor is NULL for the last node in Inorder traversal.
    //The inorder successor can be found by finding the minimum element in the right subtree of the node

    Node * temp = root_;
    Node * parent;
    Node * temp2;

    if (!exists(val)) { //if key doesn't exist, cannot be removed.
        return false;
    }
    if (root_ == nullptr) { //if size == 0 cannot be removed.
        return false;
    }

    while (temp->val != val) { //SEARCHES AND MAKES TEMP NODE THE NODE YOU WANT TO DELETE
        parent = temp; //PARENT NODE TO NODE YOU WANT TO DELETE
        if (val > temp -> val) {
            temp = temp -> right;
        } else {
            temp = temp -> left;
        }
    }

    if (temp -> left == nullptr && temp -> right == nullptr) { //leaf node
        if (temp == root_) {
            delete temp;
            root_ = nullptr;
            size_ --;
            return true;
        }
        if (parent -> val > temp -> val) {
            parent -> left = nullptr; //if the leaf node is the left child of the parent
            delete temp;
            size_ --;
            return true;
        } else {
            parent -> right = nullptr; //if the leaf node is the right child of the parent
            delete temp;
            size_ --;
            return true;
        }
    }

    if (temp -> left == nullptr && temp -> right != nullptr) { //has one right child

        if (size_ == 2 && temp == root_) {
            temp2 = temp -> right;
            root_ -> val = temp2 -> val;
            root_ -> right = nullptr;
            delete temp2;
            return true;
        }

        temp2 = temp -> right; //COPY NODE FROM RIGHT CHILD
        parent -> left = temp2;
        delete temp;
        size_ --;
        return true;
    }

    if (temp -> left != nullptr && temp -> right == nullptr) { //has one left child

        if (size_ == 2 && temp == root_) {
            temp2 = temp -> left;
            root_ -> val = temp2 -> val;
            root_ -> left = nullptr;
            delete temp2;
            return true;
        }

        temp2 = temp -> left; //COPY NODE FROM RIGHT CHILD
        parent -> right = temp2;
        delete temp;
        size_ --;
        return true;
    }

    //finding inorder successor when node has two child
    Node * predecessor;
    Node * predecessorParent = temp;

    predecessor = temp -> left; //at the first step, predecessor is the left child of its parent
    bool isRightChild = false;
    while(predecessor->right != nullptr) {
        predecessorParent = predecessor;
        predecessor = predecessor -> right;
        isRightChild = true;
    }

    temp->val = predecessor ->val;

    //CHECK IF SUCCESSOR IS A LEAF NODE OR BRANCH NODE WITH ONE CHILD

    //if leaf node
    if (predecessor->left == nullptr) {
        if (isRightChild) {
            predecessorParent -> right = nullptr;
        } else {
            predecessorParent -> left = nullptr;
        }
    } else { //if branch node
        if (isRightChild) {
            predecessorParent->right = predecessor->left;
        } else {
            predecessorParent->left = predecessor->right;
        }
    }

    delete predecessor;
    size_ --;
    return true;
}
