#include <iostream>
#include <string>

const int S_MAX = 100;

int wage(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == 'N' || ch == 'I' || ch == 'M' || ch == 'A') // I stand for "if" for now, "M" stands for min and 'A' stands for max
        return 3;
    return 0;
}

void operator_char(char Stack[S_MAX], int& index, char character, std::string& output)
{
    while (index > 0)
    {
        if (wage(character) == 3 || wage(character) > wage(Stack[index - 1]))
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
        if (character == ',')
            continue;

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
            std::cout << "Stack here: \n";
            for (int i = 0; i < stack_index; i++)
                std::cout << Stack[i] << " ";
            std::cout << std::endl;
            while (stack_index > 0 && Stack[stack_index - 1] != '(')
            {
                output += Stack[--stack_index];
                output += ' ';
            }
            if (stack_index > 0) 
                stack_index--; // Remove '(' from the stack
            std::cout << "Stack there: \n";
            for (int i = 0; i < stack_index; i++)
                std::cout << Stack[i] << " ";
            std::cout << std::endl;
            if (Stack[stack_index - 1] == 'I' || Stack[stack_index - 1] == 'M' || Stack[stack_index - 1] == 'A')
            {
                output += Stack[--stack_index];
                output += ' ';
            }
            break;
        case '+':
        case '-':
        case '*':
        case '/':
        case 'N':
        case 'I':
        case 'M': // MIN
        case 'A': // MAX
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