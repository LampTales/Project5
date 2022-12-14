#include <exception>
#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main() {
    int x[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    float y[12] = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1, 10.1, 11.1, 12.1};
    Matrix<int> a(2, 3, 2, x);
    // a.setValueForWholeMatrix(x);
    cout << a << endl;
    cout << a.getValue(0, 1, 1) << endl;
    Matrix<int> b(3, 2, 2, x);
    cout << b << endl;
    cout << "-----------------------------------" << endl;
    Matrix<int> c = a * b;
    cout << "-----------------------------------" << endl;
    cout << c << endl;

    // cout << (a != b) << endl;
    // cout << (a != a) << endl;
    // cout << (a != c) << endl;
    // a = a;

    // a = c;
}