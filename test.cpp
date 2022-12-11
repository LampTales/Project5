#include <exception>
#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main() {
    int x[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Matrix<int> a(2,2,2);
    a.setValueForWholeMatrix(x);
    cout << a << endl;
    cout << a.getValue(0,1,1) << endl;
    // Matrix<int> b = a;
    cout << "sdf" << endl;
    a.clone(a);
    cout << "ghj" << endl;
    // cout << (a != b) << endl;
    // cout << (a != a) << endl;
    // cout << (a != c) << endl;
    // a = a;

    // a = c;
}