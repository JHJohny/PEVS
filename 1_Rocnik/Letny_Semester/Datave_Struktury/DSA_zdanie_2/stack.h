#include    <iostream>
#include    <iomanip>
using namespace std;

#define SIZE 21
// A class to represent a stack
class Stack
{
    char top;
    char capacity;

public:
    Stack(int size = SIZE);         // constructor
    ~Stack();                       // destructor

    void push(char);
    char pop();
    char peek();

    int size();
    bool isEmpty();
    bool isFull();

private:
    char *arr;
};
