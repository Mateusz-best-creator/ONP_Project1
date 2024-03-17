#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
#include <cstring>

class String
{
private:
    char* m_Data;
    size_t m_Size;

public:
    // Constructor and destructor
    String()
    {
        m_Size = 0;
        m_Data = new char[1];
        m_Data[0] = '\0';
    }

    String(const char* string)
    {
        m_Size = strlen(string);
        m_Data = new char[m_Size + 1];
        memcpy(m_Data, string, m_Size);
        m_Data[m_Size] = '\0';
    }

    ~String()
    {
        delete[] m_Data;
    }

    // Overloaded operators
    String& operator+=(const String& other)
    {
        size_t total_size = m_Size + other.m_Size;
        char* new_data = new char[total_size + 1];

        strcpy(new_data, m_Data);
        strcat(new_data, other.m_Data);

        // Free memory of the current data
        delete[] m_Data;

        // Update data and size
        m_Data = new_data;
        m_Size = total_size;

        return *this;
    }

    String& operator+=(const char ch)
    {
        size_t total_size = m_Size + 1;
        char* new_data = new char[total_size + 1];
        strcpy(new_data, this->m_Data);
        new_data[total_size - 1] = ch;
        new_data[total_size] = '\0';

        // Free memory of the current data
        delete[] m_Data;

        // Update data and size
        m_Data = new_data;
        m_Size = total_size;

        return *this;
    }

    char& operator[](int index) { return m_Data[index]; }
    const char& operator[](int index) const { return m_Data[index]; }

    // Getters and setters
    size_t& size() { return m_Size; }
    const size_t& size() const { return m_Size; }
    char* get_data() { return m_Data; }
    const char* get_data() const { return m_Data; }

    // Friend functions
    friend std::ostream& operator<<(std::ostream& os, const String& str)
    {
        for (int i = 0; i < str.m_Size; i++)
        {
            os << str.m_Data[i];
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, String& str)
    {
        return is;
    }

    void clear()
    {
        delete[] m_Data;
        m_Size = 0;
    }

    // TODO
    void to_string(int number)
    {

    }
};


#endif