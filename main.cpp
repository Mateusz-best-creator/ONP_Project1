#include <iostream>
#include <string>
#include <algorithm>
#include "vector.h"

const int S_MAX = 10000;

int wage(const std::string& ch) 
{
    if (ch == "+" || ch == "-")
        return 1;
    else if (ch == "*" || ch == "/")
        return 2;
    else if (ch == "N" || ch == "IF" || ch == "MIN" || ch == "MAX")
        return 3;
    return 0;
}

void operator_char(std::string Stack[S_MAX], int& index, std::string& character, std::string& output, Vector<std::string>& helper) 
{
    while (index > 0) {
        if (wage(character) == 3 || wage(character) > wage(Stack[index - 1]))
            break;
        output += Stack[--index];
        if (Stack[index].size())
            helper.push_back(Stack[index]);
        output += ' ';
    }
    if (index < S_MAX) // Check if index is within bounds before accessing the array
        Stack[index++] = character;
}

int main() 
{
    int times;
    std::cin >> times;
    std::string Stack[S_MAX];
    while (std::cin.get() != '\n')
        continue;

    for (int time = 0; time < times; time++)
    {

        int stack_index = 0;
        std::string output;
        int local_counter_stack[S_MAX];
        int local_stack_index = 0;
        bool first_bool = true;
        bool division_by_zero = false;

        std::string expression;
        std::getline(std::cin, expression);
        Vector<std::string> separated_expression;
        Vector<std::string> separated_expression_for_processing;
        
        std::string temp;
        for (char c : expression) 
        {
            if (c != ' ')
                temp += c;
            else 
            {
                separated_expression.push_back(temp);
                temp.clear();
            }
        }
        if (temp != " ")
            separated_expression.push_back(temp);

        for (int i = 0; i < separated_expression.size(); i++)
        {
            std::string string = separated_expression[i];
            if (string == ",") {
                while (stack_index > 0 && (Stack[stack_index - 1] == "+" || Stack[stack_index - 1] == "-" 
                || Stack[stack_index - 1] == "/" || Stack[stack_index - 1] == "*" || Stack[stack_index - 1] == "N")) 
                {
                    stack_index--;
                    output += Stack[stack_index];
                    if (Stack[stack_index].size())
                        separated_expression_for_processing.push_back(Stack[stack_index]);
                    output += ' ';
                }
                local_counter_stack[local_stack_index]++;
                continue;
            }

            if (string == ".") 
            {
                while (stack_index > 0) 
                {
                    output += Stack[--stack_index];
                    if (Stack[stack_index].size())
                        separated_expression_for_processing.push_back(Stack[stack_index]);
                    output += ' ';
                }
                break;
            }

            if (string == "(") {
                Stack[stack_index++] = string;
                if (first_bool)
                    first_bool = false;
                else
                    local_stack_index++;
                local_counter_stack[local_stack_index] = 1;
            }
            else if (string == ")") 
            {
                while (stack_index > 0 && Stack[stack_index - 1] != "(") 
                {
                    output += Stack[--stack_index];
                    if (Stack[stack_index].size())
                        separated_expression_for_processing.push_back(Stack[stack_index]);
                    output += ' ';
                }

                if (stack_index > 0) 
                    stack_index--; // Remove '(' from the stack

                if (stack_index > 0 && (Stack[stack_index - 1] == "IF" || Stack[stack_index - 1] == "MIN" || Stack[stack_index - 1] == "MAX")) 
                {
                    std::string full;
                    output += Stack[stack_index - 1];
                    full += Stack[stack_index - 1];
                    if (stack_index > 0 && Stack[stack_index - 1] != "IF")
                    {
                        output += std::to_string(local_counter_stack[local_stack_index]);
                        full += std::to_string(local_counter_stack[local_stack_index]);
                    }
                    if (full.size())
                        separated_expression_for_processing.push_back(full);
                    stack_index--;
                    output += ' ';
                }
                local_counter_stack[local_stack_index] = 0;
                if (local_stack_index > 0)
                    local_stack_index--;
            }

            else if (string == "+" || string == "-" || string == "/" || string == "*" || string == "MIN" || string == "MAX" || string == "IF" || string == "N") 
                operator_char(Stack, stack_index, string, output, separated_expression_for_processing);
            else 
            {
                output += string;
                if (string.size())
                    separated_expression_for_processing.push_back(string);
                output += ' ';
            }
        }

        std::cout << output << std::endl;

        // Now when basic preprocessing is done we begin!
        Vector<std::string> queue;
        
        for (int i = 0; i < separated_expression_for_processing.size(); i++)
        {
            std::string word = separated_expression_for_processing[i];
            if (division_by_zero)
                break;
            if (word[0] == 'M' && word[1] == 'A')
            {
                int amount = (word[word.size() - 1]) - '0';
                std::cout << word << " ";
                int maxValue = -9999;
                for (int i = 0; i < amount; i++)
                {
                    int number = std::stoi(queue.back());
                    queue.pop_back();
                    maxValue = std::max(maxValue, number);
                    std::cout << number << " ";
                }
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                queue.push_back(std::to_string(maxValue));
            }
            else if (word[0] == 'M' && word[1] == 'I')
            {
                int amount = (word[word.size() - 1]) - '0';
                std::cout << word << " ";
                int minValue = 9999;
                for (int i = 0; i < amount; i++)
                {
                    int number = std::stoi(queue.back());
                    queue.pop_back();
                    minValue = std::min(minValue, number);
                    std::cout << number << " ";
                }
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                queue.push_back(std::to_string(minValue));
            }
            else if (word == "N")
            {
                int num1 = std::stoi(queue.back());
                queue.pop_back();
                std::cout << word << " " << num1 << " ";
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                num1 *= -1;
                std::string result = std::to_string(num1);
                queue.push_back(result);
            }
            else if (word == "IF")
            {
                std::cout << word << " ";
                int third = std::stoi(queue.back());
                queue.pop_back();
                int second = std::stoi(queue.back());
                queue.pop_back();
                int first = std::stoi(queue.back());
                queue.pop_back();
                std::string result;
                if (first > 0)
                    result = std::to_string(second);
                else
                    result = std::to_string(third);
                std::cout << third << " " << second << " " << first << " ";
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                queue.push_back(result);
            }
            else if (word == "*" || word == "/" || word == "+" || word == "-")
            {
                std::string second = queue.back();
                queue.pop_back();
                std::string first = queue.back();
                queue.pop_back();
                std::cout << word << " " << second << " " << first << " ";

                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                int num1 = std::stoi(first);
                int num2 = std::stoi(second);
                
                std::string result;
                if (word == "*")
                    result = std::to_string(num2 * num1);
                else if (word == "/")
                {
                    if (num2 == 0)
                    {
                        std::cout << "ERROR\n";
                        division_by_zero = true;
                    }
                    else
                        result = std::to_string(num1 / num2);
                }
                else if (word == "+")
                    result = std::to_string(num1 + num2);
                else
                    result = std::to_string(num1 - num2);
                queue.push_back(result);
            }
            else
            {
                queue.push_back(word);
            }
        }
        if (division_by_zero)
        {
            std::cout << "\n\n";
            division_by_zero = false;
        }
        else
            std::cout << queue.back() << "\n\n";
    }
}