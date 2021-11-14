#include <iostream>
#include <cmath>

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

    void push(char element)
    {
        if (isFull())
            growArray();
        length ++;
        string temp = "";
        temp += element;
        array[length] = temp;
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
 
        if(isDigit(infix[i]))
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
            postfix += " ";
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
            return pow(double(left),double(right));
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

int toInteger(string intstring)
{
    int number = 0;
    for (int i=0; i<intstring.length();i++)
    {
        int integer = 0;
        switch(intstring[i])
        {
            case '1':   integer = 1;
                        break;
            case '2':   integer = 2;
                        break;
            case '3':   integer = 3;
                        break;
            case '4':   integer = 4;
                        break;
            case '5':   integer = 5;
                        break;
            case '6':   integer = 6;
                        break;
            case '7':   integer = 7;
                        break;
            case '8':   integer = 8;
                        break;
            case '9':   integer = 9;
                        break;
            default:   integer = 0;
        }
        number = number * 10 + integer;
    }
    return number;
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
            stack.pop();
            prev += postfix[i];
            stack.push(prev);
        }
        else if (isDigit(postfix[i]))
        {
            prev = "";
            prev += postfix[i];
            stack.push(prev);
        }
        else if (postfix[i] == ' ')
        {
            prev = "";
        }
        else if (isOperator(postfix[i]))
        {
            int right = toInteger(stack.peak());
            stack.pop();

            int left = toInteger(stack.peak());
            stack.pop();

            result = performOperation(left, right, postfix[i]);
            stack.push(to_string(result));
            prev = "";
        }
        
    }
    return result;
}

// string validation funcitons
bool valid_num_of_Brackets(string input)
{
    Stack stack;
    // checking the string input
    for (int i=0; i<input.length(); i++)
    {
        // if the character is opening brace then add it to the stack
        if (input[i] == '{' || input[i] == '[' || input[i] == '(')
            stack.push(input[i]);

        // if the character is a closing brace and matches with character in the stack then pop character from the stack
        if ((input[i] == '}' && stack.peak() == "{")||
            (input[i] == ')' && stack.peak() == "(")||
            (input[i] == ']' && stack.peak() == "["))
        {
            stack.pop();
        }
        // if the expression contains closing braces without matching closing brace in stack then expression is invalid
        else if (input[i] == '}' || input[i] == ')' || input[i] == ']')
        {
            return false;
        }
    }
    // if the expression contains any opening braces without matching closing braces in stack then expression is invalid
    if (!(stack.peak() == ""))
    {
        return false; 
    }
    return true;
}

bool valid_Characters(string infix)
{
    for (int i=0; i<infix.length();i++)
    {
        if ((isDigit(infix[i]))||
            (infix[i] == '{' || infix[i] == '}')||
            (infix[i] == '[' || infix[i] == ']')||
            (infix[i] == '(' || infix[i] == ')')||
            (isOperator(infix[i])))
                continue;
        return false;
    }
    return true;
}

bool valid_num_of_Operators(string infix)
{
    string prev = "";
    Stack stack;
    
    if (isOperator(infix[0]) || isOperator(infix[infix.length()-1]))
        return false;
    
    // convert the stirng to stack
    for (int i=0; i < infix.length(); i++)
    {
        if (isDigit(infix[i]) && isDigit(infix[i-1]))
        {
            stack.pop();
            prev += infix[i];
            stack.push(prev);
        }
        else if (isDigit(infix[i]))
        {
            prev = "";
            prev += infix[i];
            stack.push(prev);
        }
        else if (infix[i] == ' ')
        {
            prev = "";
        }
        else if (isOperator(infix[i]))
        {
            if (isOperator(stack.peak()[0]))
            {
                return false;
            }
            else
            {
                stack.push(infix[i]);
            }
        }
    }
    return true;
}

void vaildateInfix(string infix)
{
    // infix string should not be empty
    if ((infix == "")||(infix == " "))
        throw "Infix string cannot be empty";
    // infix string should not begin with operator
    if (isOperator(infix[0]))
        throw "Infix string cannot begin with an operator";
    // infix string should have valid number of braces
    if (!valid_num_of_Brackets(infix))
        throw "Infix string contains invalid number of brackets";
    // infix string should not have invalid characters
    if (!valid_Characters(infix))
        throw "Infix string contains invalid characters\nNote that special only numbers, operators (+,-,*,/) and brackets ('{}','[]','()')";
    // infix string should have number of operators (two operators for every operand)
    if (!valid_num_of_Operators(infix))
        throw "Infix string contains invalid number of operators and operands";
}

int main()
{
    try
    {    
        string infix = "(((1*(2+3))-3)+4)*5";
        vaildateInfix(infix);
        cout<<"Infix Expression: "<<infix<<endl<<endl;
        string postfix = infixToPostfix(infix);
        cout<<"Postfix Expression: "<<postfix<<endl;
        cout<<"Evaluation: "<<evaluatePostFix(postfix)<<endl<<endl;
    }
    catch (const char* msg) 
    {
        cerr << "\nERROR: " <<msg << endl<< endl;
    }

    return 0;
}