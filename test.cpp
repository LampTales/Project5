#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main() {
    Matrix<int> a;
    Matrix<int> b;
    Matrix<float> c;
    a = a;
    a = b;
    a = c;
}