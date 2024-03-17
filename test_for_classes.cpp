#include "string.h"
#include "vector.h"
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    Vector<std::string> vector;
    vector.push_back("Mateusz ");
    vector.push_back("C++ ");
    vector.push_back("Vector ");
    cout << vector << endl;
    vector.pop_back();
    cout << vector << endl;
    cout << vector.back() << endl;
}