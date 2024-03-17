#include "string.h"

String::String()
{
    str = new char[1];
    str[0] = '\0';
    string_size = 0;
    max_size = 0;
}



String::~String()
{
    delete[] str;
}