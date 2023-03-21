#include "doubly-linked-list.h"
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data){
    prev = nullptr;
    next = nullptr;
    value = data;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node *temp = head_;
    while(head_ != nullptr) {
        temp = temp->next;
        delete head_;
        head_ = temp;
    }
    head_ = nullptr;
    size_ = 0;
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }

}

bool DoublyLinkedList::full() const
{
    if (size_ == CAPACITY) {
        return true;
    }
    return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index >= size_ || index < 0){
        return tail_->value;
    }

    Node* temp = head_;

    for(int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->value;

}

unsigned int DoublyLinkedList::search(DataType value) const
{
    Node* temp = head_;
    int i = 0; //variable's scope is within the function so can be returned later

    while (i < size_ - 1) {
        if (temp->value == value) { //checks if value matches and if not go to next,
            return i;
        }
        temp = temp->next;
        i++;
    }

    if (temp->value == value) { //checks the last value if it matches
        return i;
    }

    return size_;

}

void DoublyLinkedList::print() const
{
    Node* temp = head_;
    for (int i = 0; i < size_ - 1; i++) {
        cout << temp->value; // ERROR MAKE IT MAKE SENSE
        temp = temp->next;

    }
    cout << temp->value;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if ((index > size_) || size_ >= CAPACITY) { // tests if when index is out of range
        return false;
    }
    if (index == 0) {
        return insert_front(value);
    }
    if (index == size_) {
        return insert_back(value);
    }
    Node* temp = new Node(value);
    Node* temp1 = head_;
    Node* temp2 = head_;
    for (int i = 0; i < index - 1; i++) { //points towards node before the index
        temp1 = temp1->next;
    }
    for (int i = 0; i < index; i++) { //points towards node at the index
        temp2 = temp2->next;
    }
    temp1->next = temp; //the node before index points to new node
    temp2->prev = temp; //node at index points to new node. the new node is now in-between the 2 nodes. it is at the index
    temp->prev = temp1;
    temp->next = temp2;

    size_++;
    return true;
}

bool DoublyLinkedList::insert_front(DataType value){
    if(size_ == CAPACITY) {
        return false;
    }
    Node* temp = new Node(value); //creates a temporary
    if(head_==nullptr){ //if empty set temporary node to head.
        head_ = temp;
        head_->next = nullptr;
        head_->prev = nullptr;
        tail_ = head_; //???? NOT SURE SET TAIL AS HEAD AS THERE'S ONLY 1 ELEMENT
    } else {
        temp->prev = nullptr; //set temporary's prev pointer to null
        temp->next = head_; //and next pointer to the head, so it is now in front of the head
        head_->prev = temp; //temporary is before head
        head_ = temp; //temporary is added and becomes the new head
    }

    size_++;
    return true;

}

bool DoublyLinkedList::insert_back(DataType value)
{
    if (size_ == CAPACITY) {
        return false;
    }
    Node* temp = new Node(value);
    Node* last = head_;
    if (head_==nullptr){ //if empty set temporary node to head.
        head_ = temp;
        head_->next = nullptr;
        head_->prev = nullptr;
        tail_ = head_; //???? NOT SURE SET TAIL AS HEAD AS THERE'S ONLY 1 ELEMENT
    } else {
        while (last->next != nullptr){ //last points to head
            last = last->next; //last will reach the tail as tail points to null
        }

        last->next = temp; //temp is now at the end
        tail_ = temp; //set tail as the last
        tail_->prev = last;
        tail_->next = nullptr;

    }
    size_++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if ((index >= size_) || index < 0) { // tests if when index is out of range
        return false;
    }
    if (index == 0) { //remove front node
        return remove_front();
    }
    if (index == size_ - 1) { //remove last node
        return remove_back();
    }

    Node* temp = head_; // remove node in between list
    for (int i = 0; i < index; i++){
        temp = temp->next;
    }

    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    delete temp;
    temp = nullptr;
    size_++;
    return true;

}

bool DoublyLinkedList::remove_front()
{
    Node* temp = head_;

    if (size_ == 0 || head_ == nullptr) {
        return false;
    }

    if (size_ == 1){ //check when there is only one node
        head_ = nullptr;
        tail_ = nullptr;
        delete head_;
        size_--;
        return true;
    }

    head_ = head_->next;
    head_->prev = nullptr; //head prev points to null
    delete temp;
    size_--;
    return true;

}

bool DoublyLinkedList::remove_back()
{

    if (size_ == 0 || head_ == nullptr)  {
        return false;
    }

    if (size_ == 1){ //check when there is only one node
        head_ = nullptr;
        tail_ = nullptr;
        size_--;
        return true;
    }
    Node* temp = tail_;
    tail_ = tail_ -> prev;
    tail_->next = nullptr;
    delete temp;
    temp = nullptr;
    size_--;
    return true;

}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if ((index >= size_) || index < 0 || head_==nullptr) {
        return false;
    }

    Node* temp = head_;

    for (int i = 0; i < index; i++){
        temp = temp->next;
    }

    temp->value = value;
    return true;
}

