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

    void Push(char);
    char Pop();
    char Top();

    int size();
    bool IsEmpty();
    bool IsFull();

private:
    char *arr;
};
