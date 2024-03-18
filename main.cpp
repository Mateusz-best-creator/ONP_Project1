#include <iostream>
#include "vector.h"
#include "string.h"
#include <cctype>

const int S_MAX = 10000;

int min(int a, int b)
{
    if (a > b)
        return b;
    return a;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int wage(const String& ch) 
{
    if (ch[0] == '+' || ch[0] == '-')
        return 1;
    else if (ch[0] == '*' || ch[0] == '/')
        return 2;
    else if (ch[0] == 'N' || (ch[0] == 'I' && ch[1] == 'F') || (ch[0] == 'M' && ch[1] == 'I') || (ch[0] == 'M' && ch[1] == 'A'))
        return 3;
    return 0;
}

void operator_char(String Stack[S_MAX], int& index, String& character, String& output, Vector<String>& helper) 
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
    String Stack[S_MAX];
    while (std::cin.get() != '\n')
        continue;

    for (int time = 0; time < times; time++)
    {

        int stack_index = 0;
        String output;
        int local_counter_stack[S_MAX];
        int local_stack_index = 0;
        bool first_bool = true;
        bool division_by_zero = false;

        String expression;
        std::cin >> expression;
        Vector<String> separated_expression;
        Vector<String> separated_expression_for_processing;
        
        String temp;
        for (int i = 0; i < expression.size(); i++)
        {
            char c = expression[i];
            if (c != ' ')
                temp += c;
            else 
            {
                if (temp.size())
                    separated_expression.push_back(temp);
                temp.clear();
            }
        }
        if (temp[0] != ' ')
            separated_expression.push_back(temp);
        
        for (int k = 0; k < separated_expression.size(); k++)
        {
            String string = separated_expression[k];
            if (string[0] == ',') {
                while (stack_index > 0 && (Stack[stack_index - 1][0] == '+' || Stack[stack_index - 1][0] == '-' 
                || Stack[stack_index - 1][0] == '/' || Stack[stack_index - 1][0] == '*' || Stack[stack_index - 1][0] == 'N')) 
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

            if (string[0] == '.') 
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

            if (string[0] == '(') 
            {
                Stack[stack_index++] = string;
                if (first_bool)
                    first_bool = false;
                else
                    local_stack_index++;
                local_counter_stack[local_stack_index] = 1;
            }
            else if (string[0] == ')') 
            {
                while (stack_index > 0 && Stack[stack_index - 1][0] != '(') 
                {
                    output += Stack[--stack_index];
                    if (Stack[stack_index].size())
                        separated_expression_for_processing.push_back(Stack[stack_index]);
                    output += ' ';
                }

                if (stack_index > 0) 
                    stack_index--; // Remove '(' from the stack

                if (stack_index > 0 && ((Stack[stack_index - 1][0] == 'I' && Stack[stack_index - 1][1] == 'F') 
                || (Stack[stack_index - 1][0] == 'M' && Stack[stack_index - 1][1]== 'I') 
                || (Stack[stack_index - 1][0] == 'M' && Stack[stack_index - 1][1] == 'A'))) 
                {
                    String full;
                    output += Stack[stack_index - 1];
                    full += Stack[stack_index - 1];
                    if (stack_index > 0 && Stack[stack_index - 1][0] != 'I' && Stack[stack_index - 1][1] != 'F')
                    {
                        output += local_counter_stack[local_stack_index];
                        full += local_counter_stack[local_stack_index];
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

            else if (string[0] == '+' || string[0] == '-' || string[0] == '/' || string[0] == '*' 
            || (string[0] == 'M' && string[1] == 'I') 
            || (string[0] == 'M' && string[1] == 'A') 
            || (string[0] == 'I' && string[1] == 'F')
            || string[0] == 'N') 
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
        Vector<String> queue;
        
        for (int k = 0; k < separated_expression_for_processing.size(); k++)
        {
            String word = separated_expression_for_processing[k];
            if (division_by_zero)
                break;
            
            if (word[0] == 'M' && word[1] == 'A')
            {
                int amount = (word[word.size() - 1]) - '0';
                std::cout << word << " ";
                int maxValue = INT16_MIN;
                
                for (int i = 0; i < amount; i++)
                {
                    int number = queue.back().stoi();
                    queue.pop_back();
                    maxValue = max(maxValue, number);
                    std::cout << number << " ";
                }
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                
                std::cout << std::endl;
                String maxValueString;
                maxValueString += maxValue;
                queue.push_back(maxValueString);
            }
            
            else if (word[0] == 'M' && word[1] == 'I')
            {
                int amount = (word[word.size() - 1]) - '0';
                std::cout << word << " ";
                int minValue = INT16_MAX;
                for (int i = 0; i < amount; i++)
                {
                    int number = queue.back().stoi();
                    queue.pop_back();
                    minValue = min(minValue, number);
                    std::cout << number << " ";
                }
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                String minValueString;
                minValueString += minValue;
                queue.push_back(minValueString);
            }
            
            else if (word[0] == 'N')
            {
                int num1 = queue.back().stoi();
                queue.pop_back();
                std::cout << word << " " << num1 << " ";
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                num1 *= -1;
                String result;
                result += num1;
                queue.push_back(result);
            }
            
            else if (word[0] == 'I' && word[1] == 'F')
            {
                std::cout << word << " ";
                int third = queue.back().stoi();
                queue.pop_back();
                int second = queue.back().stoi();
                queue.pop_back();
                int first = queue.back().stoi();
                queue.pop_back();
                String result;
                if (first > 0)
                    result += second;
                else
                    result += third;
                std::cout << third << " " << second << " " << first << " ";
                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                queue.push_back(result);
            }
            
            else if (word[0] == '*' || word[0] == '/' || word[0] == '+' || word[0] == '-')
            {
                String second = queue.back();
                queue.pop_back();
                String first = queue.back();
                queue.pop_back();
                std::cout << word << " " << second << " " << first << " ";

                for (int i = queue.size() - 1; i >= 0; i--)
                {
                    std::cout << queue[i] << " ";
                }
                std::cout << std::endl;
                int num1 = first.stoi();
                int num2 = second.stoi();
                
                String result;
                if (word[0] == '*')
                {
                    result += (num2 * num1);
                }
                else if (word[0] == '/')
                {
                    if (num2 == 0)
                    {
                        std::cout << "ERROR\n";
                        division_by_zero = true;
                    }
                    else
                        result += (num1 / num2);
                }
                else if (word[0] == '+')
                    result += (num1 + num2);
                else
                    result += (num1 - num2);
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
        {
            if (queue.size())
                std::cout << queue.back() << "\n\n";
        }
            
    }
}