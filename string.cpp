#include "string.h"

String::String()
{
    ReAlloc(1);
}

String::String(const char* buffer) 
{
    m_Size = strlen(buffer);
    m_Capacity = 2 * m_Size;

    m_Data = new char[m_Capacity];
    for (size_t i = 0; i < m_Size; i++)
        m_Data[i] = buffer[i];

    m_Data[m_Size] = '\0'; // Null-terminate the string
}

String::String(const String& other)
{
    m_Size = other.m_Size;
    m_Capacity = other.m_Capacity;

    m_Data = new char[m_Size];
    for (size_t i = 0; i < m_Size; i++)
            m_Data[i] = other.m_Data[i];

    m_Data[m_Size] = '\0'; // Null-terminate the string
}

String::String(String&& other)
{
    m_Size = other.m_Size;
    m_Capacity = other.m_Capacity;
    m_Data = other.m_Data;

    other.m_Data = nullptr;
    other.m_Size = other.m_Capacity = 0;
}

String::~String()
{
    delete[] m_Data;
}

String& String::operator+(const String& other)
{
    m_Size += other.m_Size;
    if (m_Size >= m_Capacity)
    {
        ReAlloc(m_Capacity * 2);
    }
}

void String::ReAlloc(size_t newCapacity)
{
    char* newBlock = new char[newCapacity];

    if (newCapacity < m_Size)
        m_Size = newCapacity;

    for (size_t i = 0; i < m_Size; i++)
        newBlock[i] = m_Data[i];

    delete[] m_Data;
    m_Data = newBlock;
    m_Data[m_Size] = '\0';
    m_Capacity = newCapacity;
}