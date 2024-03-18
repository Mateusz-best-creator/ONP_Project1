#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
#include <ostream>
#include <cstring>

class String
{
private:
	char * buf = nullptr;
	unsigned int size = 0;

public:
	String() : buf(nullptr), size(0) // default constructor
	{
	}

	String(const char * const buffer) // constructor
	{
		size = strlen(buffer);
		buf = new char[size + 1]; // + 1 for the keeping the null character
		strncpy(buf, buffer, size); // copy from the incoming buffer to character buffer of the new object
	}

	String(const String & obj) // copy constructor
	{
		size = obj.size;
		buf = new char[size + 1]; // + 1 for the keeping the null character
		strncpy(buf, obj.buf, size); // copy from the incoming buffer to character buffer of the new object
	}

	String& operator=(const String & obj) // copy assignment
	{
		clear(); // cleanup any existing data

		// Copy data from the newly assigned String object
		size = obj.size;
		buf = new char[size + 1]; // + 1 for the keeping the null character
		strncpy(buf, obj.buf, size); // copy from the incoming buffer to character buffer of the new object
		return *this;
	}

	String(String && dyingObj) // move constructor
	// && is a reference operator defined in the C++11 standard 
	// which means "dyingObj" is an r-value reference.
	// Compiler calls this constructor when the object passed in the argument
	// is about to die due to scope end or such
	{
		clear(); // cleanup any existing data

		// Copy data from the incoming object
		size = dyingObj.size;
		
		// Transfer ownership of underlying char buffer from incoming object to this object
		buf = dyingObj.buf;
		dyingObj.buf = nullptr;		
	}

	String& operator=(String && dyingObj) // move assignment
	{
		clear(); // cleanup any existing data

		// Copy data from the incoming object
		size = dyingObj.size;

		// Transfer ownership of underlying char buffer from incoming object to this object
		buf = dyingObj.buf;
		dyingObj.buf = nullptr;

		return *this;
	}

	String operator+(const String & obj) // concatenation
	{
		String s; // create a new string named 's'
		s.size = this->size + obj.size;
		s.buf = new char[s.size + 1]; // allocate memory to keep the concatenated string
		strncpy(s.buf, this->buf, this->size); // copy the 1st string
		strncpy(s.buf + this->size, obj.buf, obj.size);

		return s;
	}

	unsigned int length()
	{
		return size;
	}

	const char * c_str() const
	{
		return buf;
	}

	~String() // destructor
	{
		clear();
	}

    friend std::ostream& operator<<(std::ostream& cout, const String & obj)
    {
        cout << obj.c_str();
        return cout;
    }

private:
	void clear()
	{
		if (buf != nullptr)
		{
			delete[] buf;
		}
		size = 0;
	}
};



#endif