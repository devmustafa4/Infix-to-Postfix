#include<iostream>
#include<sstream>

using namespace std;

class Stack
{
    private:
    int size = 2;
    string* array = new string[size];
    int length = 0;

    bool isEmpty()
    {
        return length == 0;
    }

    bool isFull()
    {
        return length == size - 1;
    }

    string* increaseSize()
    {
        // create a new array 
        string* newArray = new string[size];
        // copy the data from the old array to the new array
        for (int i=0;i<=length;i++)
        {
            newArray[i] = *(array+i);
        }
        return newArray;
    }

    void growArray()
    {
        size *= 2;
        array = increaseSize();
    }

    public:
    string peak()
    {
        if (isEmpty())
            return "";
        
        return array[length];
    }

    void push(string element)
    {
        if (isFull())
            growArray();
        length ++;
        array[length] = element;
    }

    void pop()
    {
        if (!isEmpty())
        {
            length--;
        }
    }
};

bool isDigit(char character)
{
    return (character >= '0' && character <= '9');
        
}

bool isOperator(char character)
{
    switch (character)
    {
        case '^':
        case '/':
        case '*':
        case '+':
        case '-':
            return true;
        default:
            return false;
    }
}

int getPrecedance(char _operator)
{
    switch (_operator)
    {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
    }
    return 0;
}

string infixToPostfix(string infix) {
 
    Stack stack; //For stack operations, we are using C++ built in stack
    string postfix;
 
    for(int i = 0; i < infix.length(); i++) {

        string current = "";
        current += infix[i];
 
        if(isDigit)
            postfix += current;
 
        else if(infix[i] == '(')
            stack.push("(");

        else if(infix[i] == ')') 
        {
            while(stack.peak() != "(")
            {
                postfix += stack.peak();
                stack.pop();
            }
            stack.pop();
        }
 
        else if (isOperator(infix[i]))
        {
            while(stack.peak() != "" && getPrecedance(infix[i]) <= getPrecedance(stack.peak()[0])) {
                postfix += stack.peak();
                stack.pop(); 
            }
            stack.push(current);
            if (isDigit(infix[i+1]))
            {
                postfix += " ";
            }
        }

    }

    while(stack.peak() != "") {
        postfix += stack.peak();
        stack.pop();
    }
 
    return postfix;
}

int performOperation(int left, int right, char operation)
{
    switch(operation)
    {
        case '^':
            return left ^ right;
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        default:
            return 0;
    }
}

int evaluatePostFix(string postfix)
{   
    string prev = "";
    Stack stack;
    int result = 0;
    for (int i=0; i < postfix.length(); i++)
    {
        if (isDigit(postfix[i]) && isDigit(postfix[i-1]))
        {
            prev += postfix[i];
        }
        else if (isDigit(postfix[i]))
        {
            prev = postfix[i];
        }
        else if (postfix[i] == ' ')
        {
            stack.push(prev);
            prev = "";
        }
        else if (isOperator(postfix[i]))
        {

            int left;
            stringstream stream2(stack.peak());
            stream2 >> left;            
            stack.pop();


            int right;
            stringstream stream1(prev);
            stream1 >> right;            
            prev = "";
            
            result = performOperation(left, right, postfix[i]);
            stack.push(to_string(result));
        }
        
    }
    return result;
}

int main()
{
    string infix = "(12+28)*(31+42)";
    cout<<infix<<endl<<endl;
    string postfix = infixToPostfix(infix);
    cout<<postfix<<endl;
    cout<<evaluatePostFix(postfix);
}