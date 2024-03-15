#include <iostream>
#include <string>
#include <vector>

int wage(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

void operator_char(std::vector<std::string>& Stack, int& index, char character, std::vector<std::string>& output)
{
    while (index > 0)
    {
        if (wage(character) >= wage(Stack[index - 1][0]))
            break;
        output.push_back(Stack[--index]);
        Stack.pop_back();
    }
    if (character != ',')
    {
        Stack.push_back(std::string(1, character));
        index++;
    }
}

int main()
{
    std::string expression = "MIN ( 100 , MAX ( 1 , 34 * 2 + 10 - 20 , 2 ) , 80 , 60 )";
    std::vector<std::string> stack;
    int index = 0;
    std::string temp = "";
    std::vector<std::string> output;

    for (char c : expression)
    {
        if (c == ')')
        {
            while (index > 0 && stack[index - 1] != "(")
                output.push_back(stack[--index]);
            if (index > 0) 
            {
                index--;
                stack.pop_back(); // remove '(' symbol
            }
            if (stack[index - 1] == "MIN" || stack[index - 1] == "MAX")
            {
                output.push_back(stack[--index]);
                stack.pop_back();
            }            
        }
        else if (c == '(' || c == ' ')
        {
            if (!temp.empty())
            {
                if (temp[0] == '1' || temp[0] == '2' || temp[0] == '3' || temp[0] == '4' 
                || temp[0] == '5' || temp[0] == '6' || temp[0] == '7' || temp[0] == '8' || temp[0] == '9')
                {
                    output.push_back(temp);
                }
                else
                {
                    stack.push_back(temp);
                    index++;
                }
                temp.clear();
            }
            if (c != ' ')
            {
                stack.push_back(std::string(1, c));
                index++;
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == ',')
        {
            operator_char(stack, index, c, output);
        }
        else
        {
            temp += c;
        }
    }

    // Output the separated pieces
    for (const std::string& piece : stack)
    {
        std::cout << piece << std::endl;
    }
    for (int i = index; i < stack.size(); i++)
        output.push_back(stack[i]);

    std::cout << "Result:\n";
    for (const std::string& piece : output)
    {
        std::cout << piece << std::endl;
    }

    return 0;
}
