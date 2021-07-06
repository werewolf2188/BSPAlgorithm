//
//  CQueue.h
//  BSPAlgorithm
//
//  Created by Enrique on 6/30/21.
//

#ifndef CQueue_hpp
#define CQueue_hpp

#include <stdio.h>

// Templates have to be self-contained in the header file since they are templates.

template<typename T, int n>
class CircularQueue {
private:
    T queue[n];
    T* head;
    T* tail;

    void verifyHead();
    void verifyTail();
public:
    CircularQueue();
    ~CircularQueue();

    void enque(T object);
    T deque();
    int queuePosition();
    bool empty();
};

template<typename T, int n>
CircularQueue<T, n>::CircularQueue() {
    head = queue; // They are referencing the same spot
    tail = queue; // That means when I assign head, I also assign tail.
}

template<typename T, int n>
CircularQueue<T, n>::~CircularQueue() {
}

template<typename T, int n>
void CircularQueue<T, n>::enque(T object) {
    *head = object;
    verifyHead();
}

template<typename T, int n>
T CircularQueue<T, n>::deque() {
    T temp = *tail;
    verifyTail();
    return temp;
}

template<typename T, int n>
void CircularQueue<T, n>::verifyHead() {
    // ++head is moving the pointer before checking if it is in the end of the queue
    if(++head == queue + n) { // TODO: This is making a circular queue to reset to position 0
        head = queue;
    }
}

template<typename T, int n>
void CircularQueue<T, n>::verifyTail() {
    // ++tail is moving the pointer before checking if it is in the end of the queue
    if(++tail == queue + n) { // TODO: This is making a circular queue to reset to position 0
        tail = queue;
    }
}

template<typename T, int n>
int CircularQueue<T, n>::queuePosition() {
    return (head + n + 1 - tail) % n; // This checks the position of the circular queue
}
template<typename T, int n>
bool CircularQueue<T, n>::empty() {
    return head == tail;
}


#endif /* CQueue_h */
