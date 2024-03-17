#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>

class String
{
private:
    char* str;
    size_t string_size, max_size;

public:
    String();
    String(const String& other);
    String(String&& other);
    ~String();

    size_t size() { return string_size; }
};

#endif