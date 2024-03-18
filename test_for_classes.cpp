#include "string.h"
#include "vector.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    
    Vector<String> vector;
    vector.push_back("Mateusz ");
    vector.push_back("C++ ");
    vector.push_back("Vector ");
    cout << vector << endl;
    vector.pop_back();
    cout << vector << endl;
    cout << vector.back() << endl;
    
    String name1("Jacek Cebula");
    String name("Mateusz Lalala");
    String name2;
    std::cin >> name2;
    cout << name << endl;
    cout << name1 << endl;
    cout << name2 << endl;

    name2 += 213;
    cout << name2 << endl;
    String test = "123321";
    cout << "Czesc oto liczba + 4 = " << test.stoi() + 4 << endl; 
}