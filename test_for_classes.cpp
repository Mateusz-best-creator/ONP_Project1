#include "string.h"
#include "stack.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    String name1("Jacek Cebula");
    String name("Mateusz Lalala");
    String name2;
    std::cin >> name2;
    cout << name << endl;
    cout << name1 << endl;
    cout << name2 << endl;

    name2 += 213;
    cout << name2 << endl;
    String test = "-10";
    cout << "Czesc oto liczba + 4 = " << test.stoi() + 4 << endl; 
    test += -20;
    cout << test << endl;
    String test2;
    test2 += -400;
    cout << test2 << endl;

    String test3;
    test3 += 0;
    cout << test3 << endl;
}