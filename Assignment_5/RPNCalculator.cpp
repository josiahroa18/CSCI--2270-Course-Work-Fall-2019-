#include "RPNCalculator.hpp"
using namespace std;

// Constructor--set the ​stackHead ​pointer to NULL
RPNCalculator::RPNCalculator(){
    stackHead = NULL;
}

// Destructor--​pop​ everything off the stack and set ​stackHead ​to NULL
RPNCalculator::~RPNCalculator(){
    while(stackHead != NULL){
        pop();
    }
    stackHead = NULL;
}

// Returns true if the stack is empty, false otherwise
bool RPNCalculator::isEmpty(){
    if(stackHead == NULL){
        return true;
    }else{
        return false;
    }
}

// Insert a new node with ​number​ ​onto the top of the stack
void RPNCalculator::push(float num){
    Operand *newNode = new Operand;
    newNode->number = num;
    newNode->next = NULL;
    newNode->next = stackHead;
    stackHead = newNode;
}

// If the stack is empty, print ​"Stack empty, cannot pop an item." ​and return. 
// Otherwise delete the top most item from the stack
void RPNCalculator::pop(){
    if(isEmpty()){
        cout << "Stack empty, cannot pop an item." << endl;
        return;
    }else{
        Operand *temp = stackHead;
        stackHead = stackHead->next;
        delete temp;
    }
}

//If the stack is empty, print​ "Stack empty, cannot peek." a​nd return NULL.​ ​
//Otherwise, return a pointer to the top of the stack
Operand* RPNCalculator::peek(){
    if(isEmpty()){
        cout << "Stack empty, cannot peek." << endl;
        return NULL;
    }
    return stackHead;
}

bool RPNCalculator::compute(string symbol){
    if(symbol == "+" || symbol == "*"){
        if(isEmpty()){
            cout << "err: not enough operands" << endl;
            return false;
        }
        float firstValue = stackHead->number;
        pop();
        if(isEmpty()){
            cout << "err: not enough operands" << endl;
            push(firstValue);
            return false;
        }
        float secondValue = stackHead->number;
        pop();
        float result = 0;
        if(symbol == "+"){
            result = firstValue + secondValue;
        }else{
            result = firstValue * secondValue;
        }
        push(result);
        return true;
    }else{
        cout << "err: invalid operation" << endl;
        return false;
    }
}