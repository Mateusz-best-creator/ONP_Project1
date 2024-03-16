#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

int main()
{
    std::deque<std::string> queue;
    std::vector<std::string> separated_expression = { "400", "N", "11", "3", "2", "*",  "-",  "2",  "/",  "+",  "200",  "N",  "N" , "+" };

    
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
            int first = std::stoi(queue.back());
            queue.pop_back();
            int second = std::stoi(queue.back());
            queue.pop_back();
            int third = std::stoi(queue.back());
            queue.pop_back();
            std::string result;
            if (first > 0)
                result = std::to_string(second);
            else
                result = std::to_string(third);
            std::cout << first << " " << second << " " << third << " ";
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
                result = std::to_string(num2 / num1);
            else if (word == "+")
                result = std::to_string(num1 + num2);
            else
                result = std::to_string(num2 - num1);
            queue.push_back(result);
        }
        else
        {
            queue.push_back(word);
        }
    }
    std::cout << queue.back() << std::endl;
}
