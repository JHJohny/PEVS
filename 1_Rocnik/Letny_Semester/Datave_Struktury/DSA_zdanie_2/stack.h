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
    //Stack(int size = SIZE);         // constructor -This constructor is not actually used for this assinment
    ~Stack();                       // destructor

    void Create(int size = SIZE); // something like constructor
    void Push(char);
    char Pop();
    char Top();

    int size();
    bool IsEmpty();
    bool IsFull();

private:
    char *arr;
};
