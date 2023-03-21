#include "sequential-list.h"
#include <iostream>
using namespace std;

SequentialList::SequentialList(unsigned int cap) {
    data_ = new DataType[cap];
    capacity_ = cap;
    size_ = 0;

}

SequentialList::~SequentialList(){
    delete [] data_;
    data_ = nullptr;

}

unsigned int SequentialList::size() const {
    return size_;
}

unsigned int SequentialList::capacity() const {
    return capacity_;
}

bool SequentialList::empty() const{

    if (size_ == 0) {
        return true;
    } else {
        return false;
    }

}

bool SequentialList::full() const{
    if (size_ == 0 && capacity_ == 0) {
        return false;
    }
    if (size_ == capacity_) {
        return true;
    } else {
        return false;
    }
}

SequentialList::DataType SequentialList::select(unsigned int index) const{
    if (index < 0 || index >= size_) {
        return data_[size_ -1];
    } else {
        return data_[index];
    }
}

unsigned int SequentialList::search(DataType val) const{

    int unsigned i;
    for (i = 0; i < size_; i++) {
        if (data_[i] == val) {
            return i;
        }
    }
    return size_;
}

void SequentialList::print() const {

    int unsigned i;
    for (i = 0; i < size_; i++) {
        cout << data_[i];
    }
}

bool SequentialList::insert(DataType val, unsigned int index) {
    int unsigned i;
    if (index < 0 || index >= capacity_) { //checking the bounds. cannot be added to indeces less than zero, or bigger than the
        return false;                            //capacity
    }
    if (index >= size_) {
        data_[size_] = val;
        size_ = size_ + 1;
        return true;
    } else if (size_ == capacity_) {
        return false;
    }
    for (i = size_; i > index; i--) { //has to check when list is full * size = capacity
        data_[i] = data_[i-1];
    }
    data_[i] = val;
    size_ = size_ + 1;
    return true;
}

bool SequentialList::insert_front(DataType val){
    return insert(val, 0);
}

bool SequentialList::insert_back(DataType val){
    return insert(val, size_);
}

bool SequentialList::remove(unsigned int index) {
    int unsigned i;
    if (index < 0 || index >= size_) {
        return false;
    }
    if (index == size_ - 1){
        size_ = size_ - 1;
        return true;
    }

    for (i = index; i < size_-1; i++) {
        data_[i] = data_[i+1];
    }

    size_ = size_ -1;
    return true;
}

bool SequentialList::remove_front(){

    return remove(0);
}

bool SequentialList::remove_back(){

    return remove(size_ - 1);
}

bool SequentialList::replace(unsigned int index, DataType val) {
    if (index >= size_ || index < 0) {
        return false;
    }

    data_[index] = val;
    return true;

}

