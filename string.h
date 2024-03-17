#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
#include <cstring> // for strlen, strcpy and strcat

class String
{
private:
    char* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;

    void ReAlloc(size_t newCapacity);

public:
    // Constructors and destructor
    String();
    String(const char* buffer);
    String(const String& other);
    String(String&& other);
    ~String();

    // Setters and getters
    size_t& size() { return m_Size; }
    const size_t& size() const { return m_Size; }
    size_t& capacity() { return m_Capacity; }
    const size_t& capacity() const { return m_Capacity; }

    // Overloaded operators
    String& operator+(const String& other);
    String& operator+(const char ch);
    String& operator=(const String& other);
    String& operator=(String&& other);

    friend std::ostream& operator<<(std::ostream& os, const String& other);
    friend std::istream& operator>>(std::istream& is, String& other);
};

#endif