#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
#include <vector>

void removeDoubleWhitespaces(std::string& str) 
{
    for (size_t i = 0; i < str.size() - 1; ++i) 
    {
        if (std::isspace(str[i]) && std::isspace(str[i + 1])) 
        {
            // Erase the next whitespace
            str.erase(i + 1, 1);
            --i;
        }
    }
}

void replaceSingleWhitespacesWithDouble(std::string& str) 
{
    size_t pos = 0;
    while ((pos = str.find(' ', pos)) != std::string::npos) 
    {
        str.replace(pos, 1, "  ");
        pos += 2;
    }
}

const int S_MAX = 100;

int wage(std::string ch) 
{
    if (ch == "+" || ch == "-")
        return 1;
    else if (ch == "*" || ch == "/")
        return 2;
    else if (ch == "N" || ch == "IF" || ch == "MIN" || ch == "MAX")
        return 3;
    return 0;
}

void operator_char(std::string Stack[S_MAX], int& index, std::string& character, std::string& output) {
    while (index > 0) {
        if (wage(character) == 3 || wage(character) > wage(Stack[index - 1]))
            break;
        output += Stack[--index];
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
        bool first = true;

        std::string expression;
        std::getline(std::cin, expression);
        std::vector<std::string> separated_expression;
        
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

        
        for (auto string : separated_expression) 
        {
            if (string == ",") {
                while (stack_index > 0 && (Stack[stack_index - 1] == "+" || Stack[stack_index - 1] == "-" 
                || Stack[stack_index - 1] == "/" || Stack[stack_index - 1] == "*")) 
                {
                    stack_index--;
                    output += Stack[stack_index];
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
                    output += ' ';
                }
                break;
            }

            if (string == "(") {
                Stack[stack_index++] = string;
                if (first)
                    first = false;
                else
                    local_stack_index++;
                local_counter_stack[local_stack_index] = 1;
            }
            else if (string == ")") 
            {
                while (stack_index > 0 && Stack[stack_index - 1] != "(") 
                {
                    output += Stack[--stack_index];
                    output += ' ';
                }

                if (stack_index > 0) 
                    stack_index--; // Remove '(' from the stack

                if (stack_index > 0 && (Stack[stack_index - 1] == "IF" || Stack[stack_index - 1] == "MIN" || Stack[stack_index - 1] == "MAX")) 
                {
                    output += Stack[stack_index - 1];
                    if (stack_index > 0 && Stack[stack_index - 1] != "IF")
                        output += '0' + local_counter_stack[local_stack_index];
                    stack_index--;
                    output += ' ';
                }
                local_counter_stack[local_stack_index] = 0;
                if (local_stack_index > 0)
                    local_stack_index--;
            }

            else if (string == "+" || string == "-" || string == "/" || string == "*" || string == "MIN" || string == "MAX" || string == "IF" || string == "N") 
                operator_char(Stack, stack_index, string, output);
            else 
            {
                output += string;
                output += ' ';
            }
        }
        removeDoubleWhitespaces(output);
        temp.clear();
        separated_expression.clear();
        for (char c : output)
        {
            if (c == ' ')
            {
                separated_expression.push_back(temp);
                temp.clear();
            }
            else
            {
                temp += c;
            }
        }
        replaceSingleWhitespacesWithDouble(output);
        std::cout << output << std::endl;
        
        // Now when basic preprocessing is done we begin!
        std::deque<std::string> queue;
        
        for (auto word : separated_expression)
        {
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
                        return 0;
                    }
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
        std::cout << queue.back() << "\n\n";
    }
}