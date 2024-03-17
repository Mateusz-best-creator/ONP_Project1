#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>

const int CIN_LIM = 1000;

class String
{
private:
    char* str;
    int length;

public:
    // Define constructors and destructor
    String();
    String(const char* s);
    String(const String& s); // Copy constructor
    ~String();

    int get_length() const { return length; }

    // Define overloaded operators
    bool operator<(const String& s) const;
    bool operator>(const String& s) const;
    bool operator==(const String& s) const;
    String operator+(const String& s) const;
    void operator+=(const String& s);
    String& operator=(const String& s);
    String& operator=(const char* s);
    char& operator[](int index);
    const char& operator[](int index) const;

    // Friend functions
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend std::istream& operator>>(std::istream& is, String& s);
};

#endif