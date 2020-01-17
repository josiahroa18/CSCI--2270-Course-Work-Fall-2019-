#include "ProducerConsumer.hpp"
#include <iostream>
using namespace std;

ProducerConsumer::ProducerConsumer(){
    queueFront = queueEnd = 0;
}

bool ProducerConsumer::isEmpty(){
    if (counter == 0){
        return true;
    }else{
        return false;
    }
}

bool ProducerConsumer::isFull(){
    if(counter == SIZE){
        return true;
    }
    return false;
}

void ProducerConsumer::enqueue(string item){
    if(isFull()){
        cout << "Queue full, cannot add new item" << endl;
    }else{
        queue[queueEnd] = item;
        if(queueEnd == SIZE - 1){
            queueEnd = 0;
        }else{
            queueEnd ++;
        }
        counter ++;
    }
}

void ProducerConsumer::dequeue(){
    if(isEmpty()){
        cout << "Queue empty, cannot dequeue an item" << endl;
    }else{
        if(queueFront == SIZE - 1){
            queueFront = 0;
        }else{
            queueFront ++;
        }
        counter --;
    }
}

string ProducerConsumer::ProducerConsumer::peek(){
    if(isEmpty()){
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }else{
        return queue[queueFront];
    }
}

int ProducerConsumer::queueSize(){
    return counter;
}