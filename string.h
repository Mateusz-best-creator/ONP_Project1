#pragma once

#include <iostream>

class String
{
private:
    char* str;
    int length;
    static const int CINLIM = 1000;

public:
    // Define constructors and destructor
    String();
    explicit String(const char* s);
    String(const String& s); // Copy constructor
    ~String();

    const int& size() const { return length; }
	void clear();
	int stoi() const;

    // Define overloaded operators
    bool operator==(const String& s) const;
    String& operator=(const String& s);
    String& operator=(const char* s);
    char& operator[](int index);
    const char& operator[](int index) const;
	String& operator+=(const char ch);
	String& operator+=(const String& s);
	String& operator+=(int number);

    // Friend functions
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    friend std::istream& operator>>(std::istream& is, String& s);
};