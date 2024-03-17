#include <iostream>
#include <cstring>
#include "string.h"

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

// Define overloaded operators
bool String::operator<(const String& s) const
{
    return strcmp(this->str, s.str) < 0;
}

bool String::operator>(const String& s) const
{
    return s.str < this->str;
}

bool String::operator==(const String& s) const
{
    return strcmp(s.str, this->str) == 0;
}

String String::operator+(const String& s) const
{
    size_t size1 = strlen(this->str), size2 = strlen(s.str);
    char* buffer = new char[size1 + size2 + 1];
    strcpy(buffer, this->str);
    strcat(buffer, s.str);
    String new_string { buffer };
    delete[] buffer;
    return new_string;
}

void String::operator+=(const String& s)
{
    size_t size1 = strlen(this->str), size2 = strlen(s.str);
    char* buffer = new char[size1 + size2 + 1];
    strcpy(buffer, this->str);
    strcat(buffer, s.str);
    delete[] this->str;
    this->str = new char[size1 + size2 + 1];
    strcpy(this->str, buffer);
    this->length = strlen(this->str);
    delete[] buffer;
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

std::istream& operator>>(std::istream& is, String& s)
{
    char temp[CIN_LIM];
    is.getline(temp, CIN_LIM);
    for (int i = 0; i < CIN_LIM; i++)
        s.str[i] = temp[i];

    while (is && is.get() != '\n')
        continue;
    return is;
}