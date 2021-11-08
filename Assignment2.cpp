#include<iostream>
using namespace std;

class Stack
{
    private:
    static const int size = 10;
    char array[size];
    int length = 0;

    bool isEmpty()
    {
        return length == 0;
    }

    bool isFull()
    {
        return length == size - 1;
    }

    public:
    char* top()
    {
        if (isEmpty())
            return NULL;
        return &array[length];
    }

    void push(int element)
    {
        if (!isFull())
            array[length++] = element;
    }

    void pop()
    {
        if (!isEmpty())
        {
            length--;
        }
    }
};

int main()
{
    Stack stack;
    stack.push('a');
    stack.push('b');
    stack.pop();
    cout<<*stack.top();
    stack.pop();
    
    if (stack.top() != NULL)
        cout<<*stack.top();
        
}