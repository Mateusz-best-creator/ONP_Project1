#include <iostream>
#include <cstring>
#include "string.h"
#include "vector.h"

using std::strlen;
using std::strcpy;
using std::strcmp;
using std::strcat;

String::String()
{
    length = 0;
    str = new char[1];
    str[0] = '\0';
}

String::String(const char* s)
{
    if (s == nullptr)
    {
        length = 0;
        str = new char[1];
        str[0] = '\0';
    }
    else
    {
        length = strlen(s);
        str = new char[length + 1];
        strcpy(str, s);
    }
}

String::String(const String& s)
{
    length = strlen(s.str);
    str = new char[length + 1];
    strcpy(str, s.str);
}

String::~String()
{
    delete[] str;
}

void String::clear()
{
    length = 0;
    delete[] str;
    str = new char[1];
    str[0] = '\0';
}

bool String::operator==(const String& s) const
{
    return strcmp(s.str, this->str) == 0;
}

String& String::operator=(const String& s)
{
    // Check for self assignment
    if (this == &s)
        return *this;
    delete[] this->str;
    this->length = strlen(s.str);
    this->str = new char[this->length + 1];
    strcpy(this->str, s.str);
    return *this;
}

String& String::operator=(const char* s)
{
    delete[] this->str;
    this->length = strlen(s);
    this->str = new char[length + 1];
    strcpy(this->str, s);
    return *this;
}

char& String::operator[](int index)
{
    return this->str[index];
}

const char& String::operator[](int index) const
{
    return this->str[index];
}

// Friend functions
std::ostream& operator<<(std::ostream& os, const String& s)
{
    os << s.str;
    return os;
}

String& String::operator+=(const char ch)
{
    char* temp = new char[length + 2]; // Allocate memory for the new string
    strcpy(temp, this->str); // Copy current string to temp
    temp[length] = ch; // Append the character
    temp[length + 1] = '\0'; // Null-terminate the string
    delete[] this->str; // Delete old string
    this->str = temp; // Update str to point to the new string
    length++; // Increment the length
    return *this; // Return reference to the modified string
}

String& String::operator+=(const String& s)
{
    size_t size = s.length + length;
    char* temp = new char[size + 1];
    strcpy(temp, this->str);
    strcat(temp, s.str);
    temp[size] = '\0';
    delete[] this->str;
    this->str = temp;
    length = size;
    return *this;
}

// Probems with negative numbers
String& String::operator+=(int number)
{
    bool smaller_than_zero = false;
    if (number < 0)
    {
        smaller_than_zero = true;
        number *= -1;
    }
    Vector<int> numbers;
    if (number == 0)
        numbers.push_back(0);
    while (number > 0)
    {
        int t = number % 10;
        number /= 10;
        numbers.push_back(t);
    }
    Vector<char> characters;
    if (smaller_than_zero)
        characters.push_back('-');
    for (int i = numbers.size() - 1; i >= 0; i--)
    {
        char temp;
        switch(numbers[i])
        {
        case 0: temp = '0'; break;
        case 1: temp = '1'; break;
        case 2: temp = '2'; break;
        case 3: temp = '3'; break;
        case 4: temp = '4'; break;
        case 5: temp = '5'; break;
        case 6: temp = '6'; break;
        case 7: temp = '7'; break;
        case 8: temp = '8'; break;
        case 9: temp = '9'; break;
        }
        characters.push_back(temp);
    }
    size_t newSize = length + characters.size();
    char* temp = new char[newSize + 1];
    strcpy(temp, this->str);
    for (int i = 0; i < characters.size(); i++)
        temp[length + i] = characters[i];
    temp[newSize] = '\0';
    
    delete[] this->str;
    this->str = temp;
    length = newSize;
    
    return *this;
}

int String::stoi()
{
    int number = 0;
    int power = 1;
    for (int i = length - 1; i >= 0; i--)
    {
        int digit;
        switch (this->str[i])
        {
        case '0': digit = 0; break;
        case '1': digit = 1; break;
        case '2': digit = 2; break;
        case '3': digit = 3; break;
        case '4': digit = 4; break;
        case '5': digit = 5; break;
        case '6': digit = 6; break;
        case '7': digit = 7; break;
        case '8': digit = 8; break;
        case '9': digit = 9; break;
        default: digit = -1;
        }
        if (digit == -1)
        {
            number *= -1;
        }
        else
        {
            number += digit * power;
            power *= 10;
        }
    }
    return number;
}

std::istream& operator>>(std::istream& is, String& s)
{
    for (char c; is.get(c) && c != '\n'; ) s += c;
    return is;
}