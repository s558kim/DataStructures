#include "polynomial.h"
#include "doubly-linked-list.h"
#include <iostream>
#include <string>
using namespace std;
Polynomial::Polynomial(int A[], int size) {
    size_ = size;
    for (int i = 0; i < size; i++) {
        coefficients.insert_back(A[i]);
    }
}
Polynomial* Polynomial::add(Polynomial* rhs) {
    int maxsize = max(size_, rhs -> size_);
    int arr[maxsize];
    for (int i = 0; i < maxsize; i++) {
        if (i + 1 > rhs -> size_) { //LEFT-HAND SIZE IS BIGGER THAN THE RIGHT-HAND SIZE
            arr[i] = coefficients.select(i); //MAKE RESULT ADD THE REMAINING LHS
            continue;
        }
        if (i + 1 > size_) { //VICE VERSA
            arr[i] = rhs -> coefficients.select(i);
            continue;
        }

        arr[i] = coefficients.select(i) + rhs -> coefficients.select(i); // when size is the same
    }
    Polynomial* answer = new Polynomial(arr, maxsize);
    return answer;
}
Polynomial* Polynomial::sub(Polynomial* rhs) {
    int maxsize = max(size_, rhs -> size_);
    int arr[maxsize];
    for (int i = 0; i < maxsize; i++) {
        if (i + 1 > rhs -> size_) { //LEFT-HAND SIZE IS BIGGER THAN THE RIGHT-HAND SIZE
            arr[i] = coefficients.select(i); //MAKE RESULT ADD THE REMAINING LHS
            continue;
        }
        if (i + 1 > size_) { //VICE VERSA
            arr[i] = -1 * rhs -> coefficients.select(i); //FLIPPED OPPOSITE I DONT KNOW WHY?
            continue;
        }
        arr[i] = coefficients.select(i) - rhs -> coefficients.select(i);
    }
    Polynomial* answer = new Polynomial(arr, maxsize);
    return answer;
}
Polynomial* Polynomial::mul(Polynomial* rhs) {
    int maxsize = size_ + rhs -> size_ - 1;
    int arr[maxsize];
    for (int i = 0; i < maxsize; i++) {
        arr[i] = 0;
    }
    for (int i = 0; i < size_; i++) {
        for (int k = 0; k < rhs -> size_; k++) {
            //if(coefficients.select(i) != 0 && rhs -> coefficients.select(i) != 0) {}
            arr[i+k] += (coefficients.select(i) * rhs -> coefficients.select(k));
        }
    }
    Polynomial* answer = new Polynomial(arr, maxsize);
    return answer;
}
void Polynomial::print() {
    int real_size = 0;
    int count = 0;
    for (int i = 0; i < size_; i++) {
        if (coefficients.select(i) == 0 ) {
            count ++;
        }
        if (count == size_) {
            cout << "empty";
        }
    }
    count = 0;
    for (int i = 0; i < size_; i++) {
        if (coefficients.select(i) != 0) {
            real_size++;
        }
    }
    for (int i = size_; i > 0; i--) { // when result is positive
        if(coefficients.select(i-1) > 0) {
            count++;
            if (count == real_size) {
                cout << coefficients.select(i-1) << "x^" << i-1;
            } else {
                cout << coefficients.select(i-1) << "x^" << i-1 << " + ";
            }
        }
        if(coefficients.select(i-1) < 0) {
            count ++;
            if (count == real_size) {
                cout << "(" << coefficients.select(i-1) << ")x^" << i-1;
            } else {
                cout << "(" << coefficients.select(i-1) << ")x^" << i-1 << " + ";
            }
        }
    }
    cout << endl << endl;
}

