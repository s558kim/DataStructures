#include "dynamic-stack.h"
#include <iostream>
using namespace std;

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -99999;

DynamicStack::DynamicStack() {
    capacity_ = 16;
    init_capacity_ = capacity_;
    size_ = 0;
    items_ = new int[init_capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity){
    init_capacity_ = capacity;
    capacity_ = capacity;
    size_ = 0;
    items_ = new int[init_capacity_];
}

DynamicStack::~DynamicStack() {
    delete [] items_;
}

bool DynamicStack::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

int DynamicStack::size() const {
    return size_;
}

void DynamicStack::push(StackItem value) {
    if (size_ == capacity_) {
        capacity_ *= 2;
        int *temp = new int[capacity_]; //creates temporary array with same capacity;

        for (int i = 0; i < size_; i++) { //copy all items into temporary array
            temp[i] = items_[i];
        }

        delete [] items_; //delete old array
        items_ = temp;

    }
    items_[size_] = value;
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {

    if (size_ == 0) {
        return EMPTY_STACK; //SHOULD RETURN EMPTY_STACK
    }
    if (size_-1 <= 0.25*capacity_ && 0.5*capacity_ >= init_capacity_) { //TEST WHEN CAPACITY BECOMES 0{
        capacity_ = capacity_/2;
    }

    int *temp = new int[capacity_];
    int last_item = items_[size_-1];
    for (int i = 0; i < size_ - 1; i++) { //copy all items into temporary array
        temp[i] = items_[i];
    }

    delete [] items_; //delete old array
    items_ = temp;
    size_--;
    return last_item;

}

DynamicStack::StackItem DynamicStack::peek() const {
    if (size_ == 0) {
        return EMPTY_STACK;
    }
    int last_item = items_[size_-1];
    return last_item;
}

void DynamicStack::print() const {
    for (int i = 0; i < size_; i++) {
        cout << items_[i];
    }
}