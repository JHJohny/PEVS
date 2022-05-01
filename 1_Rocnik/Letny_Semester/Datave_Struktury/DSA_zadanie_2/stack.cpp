#include <iostream>
using namespace std;

#include "stack.h"

// Constructor to initialize the stack - even it's not a real constructor as it should be
void Stack::Create(int size)
{
    arr = new char[size];
    capacity = size;
    top = -1;
}

// Destructor to free memory allocated to the stack
Stack::~Stack() {
    delete[] arr;
}

// Utility function to add an element `x` to the stack
void Stack::Push(char x)
{
    if (IsFull())
    {
        cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }

    arr[++top] = x;
}

// Utility function to pop a top element from the stack
char Stack::Pop()
{
    // check for stack underflow
    if (IsEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }

    // decrease stack size by 1 and (optionally) return the popped element
    return arr[top--];
}

// Utility function to return the top element of the stack
char Stack::Top()
{
    if (!IsEmpty()) {
        return arr[top];
    }
    else {
        exit(EXIT_FAILURE);
    }
}

// Utility function to return the size of the stack
int Stack::size() {
    return top + 1;
}

// Utility function to check if the stack is empty or not
bool Stack::IsEmpty() {
    return top == -1;
}

// Utility function to check if the stack is full or not
bool Stack::IsFull() {
    return top == capacity - 1;
}