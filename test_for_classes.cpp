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

    String name;
    cin >> name;
    cout << name << std::endl;
    name += " I jeszcze Mikolaj";
    cout << name << std::endl;
}