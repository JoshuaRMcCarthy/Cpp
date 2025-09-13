#ifndef MONOSTACK_H
#define MONOSTACK_H
#include <iostream> 

template <typename T>
class MonoStack{
    public:
        MonoStack(int iSize, char o);
        ~MonoStack();

        // interface
        void push(T c); //add to the top
        T pop(); //remove from the top
        T peek(); //return the top without removing

        
        bool isFull();
        bool isEmpty();
        int size();
        void addSpace();
        void clearStack();
        int getCount();

    private:
        char typeStack;
        T* stackArr;
        int count; //number of items currently in the stack
        int maxSize; //max number of things in the stack
        int top; //index of the current top of the stack
};


template <typename T>
MonoStack<T>::MonoStack(int iSize, char o){
    stackArr = new T[iSize];
    typeStack = o;
    maxSize = iSize;
    count = 0;
    top = -1;
}
template <typename T>
MonoStack<T>::~MonoStack(){
    //std::cout << "clearing a MonoStack obj!" << std::endl;
    delete[] stackArr;
}
template <typename T>
bool MonoStack<T>::isFull(){
    return (count == maxSize);
}
template <typename T>
bool MonoStack<T>::isEmpty(){
    return (count == 0);
}
template <typename T>
int MonoStack<T>::size(){
    return count;
}
template <typename T>
void MonoStack<T>::push(T c){
    /*
        for increasing monostack:
        checks if the stack is full to add space if necessary. Then checks if the value 
        at the top of the stack is greater or equal to the value being pushed and if the
        stack is empty. If it is not empty and the top value is greater than or equal to
        the value being pushed, it will be popped. Loops and pops until the value isnt 
        greater than or equal to the value being pushed. Then pushes the value and increments 
        the count.
    */
    if (typeStack == 'i'){
        if(isFull()){
        addSpace();
        }
        if (!isEmpty() && peek() >= c){
            while(!isEmpty() && peek() >= c){
                pop();
            }
        }
        stackArr[++top] = c;
        ++count;

    /*
        for decreasing monostack:
        checks if the stack is full to add space if necessary. Then checks if the value 
        at the top of the stack is less than or equal to the value being pushed and if
        the stack is empty. If it is less than or equal to the value being pushed and
        the stack is not empty, it will be popped. Loops and pops until the value isnt 
        less than or equal to the value being pushed. Then pushes the value and increments 
        the count.
    */
    } else if (typeStack == 'd'){
        if(isFull()){
            addSpace();
        }
        if (!isEmpty() && peek() <= c){
            while(!isEmpty() && peek() <= c){
                pop();
            }
        }
        stackArr[++top] = c;
        ++count;
    } else {
        std::cerr << "Invalid stack type entered" << std::endl;
    }
}

template <typename T>
void MonoStack<T>::addSpace(){
    T* temp = new T[2*maxSize];
    for(int i = 0; i < maxSize; ++i){
        temp[i] = stackArr[i];
    }
    maxSize *= 2;
    delete[] stackArr;
    stackArr = temp;
}


template <typename T>
T MonoStack<T>::pop(){
    --count;
    return stackArr[top--];
}
template <typename T>
T MonoStack<T>::peek(){
    return stackArr[top];
}

template <typename T>
int MonoStack<T>::getCount(){
    return count;
}

#endif