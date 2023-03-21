#include "circular-queue.h"
const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -99999;
#include <iostream>
using namespace std;

CircularQueue::CircularQueue() {
    capacity_ = 16;
    size_ = 0;
    items_ = new int[capacity_];
    head_ = 0;
    tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity;
    size_ = 0;
    items_ = new int[capacity_];
    head_ = 0;
    tail_ = 0;

}

CircularQueue::~CircularQueue() {
    delete [] items_;
}

bool CircularQueue::empty() const {

    if (size_ == 0){
        return true;
    }
    return false;
}

bool CircularQueue::full() const {

    if (size_ == capacity_) {
        return true;
    }
    return false;
}

int CircularQueue::size() const {
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    if (size_ == capacity_) {
        return false;
    }

    items_[tail_] = value;
    tail_++;
    size_ ++;

    if (tail_ == capacity_) {
        tail_ = 0;
    }
    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    int first;
    if (size_ == 0) {
        return EMPTY_QUEUE;
    }

    first = items_[head_];
    items_[head_] = 0;
    head_++;
    size_--;

    if(head_ == capacity_){
        head_ = 0;
    }

    return first;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (size_ == 0) {
        return EMPTY_QUEUE;
    }
    int first = items_[head_];
    return first;
}

void CircularQueue::print() const {

}

