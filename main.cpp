#include <iostream>
#include <string>

const int S_MAX = 100;

int wage(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

void operator_char(char Stack[S_MAX], int& index, char character, std::string& output)
{
    while (index > 0)
    {
        if (wage(character) >= wage(Stack[index - 1]))
            break;
        output += Stack[--index];
        output += ' ';
    }
    Stack[index++] = character;
}

int main()
{
    char Stack[S_MAX];
    int stack_index = 0;
    std::string output;
    char character;

    while (true)
    {
        std::cin >> character;

        if (character == '.')
        {
            while (stack_index)
            {
                output += Stack[--stack_index];
                output += ' ';
            }
            break;
        }

        switch (character)
        {
        case ' ': 
            break;
        case '(':
            Stack[stack_index++] = character;
            break;
        case ')':
            while (stack_index > 0 && Stack[stack_index - 1] != '(')
            {
                output += Stack[--stack_index];
                output += ' ';
            }
            if (stack_index > 0) 
                stack_index--; // Remove '(' from the stack
            break;
        case '+':
        case '-':
        case '*':
        case '/':
            operator_char(Stack, stack_index, character, output);
            break;
        default:
            output += character;
            output += ' ';
            break;
        }
    }

    std::cout << "Result:\n" << output << std::endl;
}