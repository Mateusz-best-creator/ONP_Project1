#ifndef __LINKED_LIST_STACK_H_
#define __LINKED_LIST_STACK_H_

#include <iostream>
#include <cstdlib>
#include <cassert>

// Double linked linked_list
template <typename T>
class LinkedListStack
{
private:
    // Node structure: <-[VALUE]->
    struct Node
    {
        T value;
        Node* next,* previous;
        Node(T val, Node* prev = nullptr, Node* nxt = nullptr)
            : value(val), previous(prev), next(nxt) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;
    size_t m_Size = 0;

public:
    // Constructor and destructor
    LinkedListStack() = default;
    ~LinkedListStack()
    {
        clear();
    }

    // push_back and pop_back methods
    void push_back(T val)
    {
        Node* newNode = new Node(val);
        if (head == nullptr) 
        {
            head = newNode;
            tail = newNode;
        } else {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        }
        m_Size++;
    }

    T pop_back()
    {
        T poppedValue = tail->value;
        Node* temp = tail;
        tail = tail->previous;
        if (tail != nullptr)
            tail->next = nullptr;
        delete temp;
        m_Size--;
        if (m_Size == 0)
            head = tail = nullptr;
        return poppedValue;
    }

    // Getters and setters
    size_t& size() { return m_Size; }
    const size_t& size() const { return m_Size; }
    bool isEmpty() const { return m_Size == 0; }

    T back() const 
    {
        if (m_Size == 0)
        {
            std::cerr << "Size of linked list is 0 in back() call!\n";
            exit(EXIT_FAILURE);
        } 
        return tail->value; 
    }

    // For deallocating memory
    void clear()
    {
        while (!isEmpty())
            pop_back();
    }

    // Overloaded operators
    T& operator[](size_t index)
    {
        assert((index < m_Size) && "Index out of range");
        // Time = O(n)
        Node* temp = head;
        size_t counter = 0;
        while (counter < index)
        {
            counter++;
            temp = temp->next;
        }
        return temp->value;
    }

    const T& operator[](size_t index) const
    {
        assert((index < m_Size) && "Index out of range");
        // Time = O(n)
        Node* temp = head;
        size_t counter = 0;
        while (counter < index)
        {
            counter++;
            temp = temp->next;
        }
        return temp->value;
    }

    // friend functions
    friend std::ostream& operator<<(std::ostream& os, const LinkedListStack& other)
    {
        Node* temp = other.head;
        while (temp != nullptr)
        {
            os << temp->value << " ";
            temp = temp->next;
        }
        return os;
    }
};

#endif