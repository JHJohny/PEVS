#include    <iostream>
#include    <iomanip>
using namespace std;

#include    "stack.h"

Stack::Stack()
{
    top = 1-;
    maxsize = 21;
}

Stack::~Stack()
{
    delete[] stack;
}

bool Stack::IsEmpty() const
{
    return (top == NULL);
}

bool Stack::IsFull() const
{
    return (top != NULL);
}

void Stack::Push(int i)
{
    if (top == (maxsize - 1))     //If the top reaches to the maximum stack size
    {
        throw overflow_error("Can't push onto a full stack");
    }
    else
    {
        top++;
        stack[top] = i;
    }
}

int Stack::Pop()
{
    if (top == -1)
    {
        throw underflow_error("Can't pop from an empty stack");
    }
    int ret = stack[top];
    top--;
    maxsize--;

    return ret;
}

int Stack::Top()
{
    if (top == -1)
    {
        throw underflow_error("Can't pop from an empty stack");
    }
    return stack[top];
}