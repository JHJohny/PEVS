#include    <iostream>
#include    <iomanip>
using namespace std;


class Stack
{
public:
Stack();           // constructor
~Stack();              // destructor

void Push(int);       // push an int into a Stack
int  Pop();            // pop an int from a Stack
int  Top();               // same as pop but it doesn't erase value

bool IsEmpty() const;    // is the Stack empty?
bool IsFull() const;     // is the Stack full?


private:
int *stack;             // pointer to local stack of ints
char chars[21];         // actual users input

int top;                // top of stack (next avail. location)
int maxsize;            // max size of the stack
};
