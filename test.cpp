#include <exception>
#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main() {
    int intvalue1[36] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    Matrix<int> RGB_img1(3, 4, 3, intvalue1);
    cout << "img1:" << endl
         << RGB_img1 << endl;

    Matrix<int> RGB_img2 = RGB_img1;
    if (RGB_img1 == RGB_img2) {
        cout << "They are the same!" << endl;
    }

    RGB_img1.setValue(0, 0, 0, 255);
    cout << "img2:" << endl
         << RGB_img2 << endl;

    Matrix<int> ROIofimg1;
    ROIofimg1.setROIfrom(RGB_img1, 1, 1, 2, 2);
    if (RGB_img1 != ROIofimg1) {
        cout << "They are not the same!" << endl;
    }
    ROIofimg1.setValue(0, 0, 1, 255);
    cout << "ROI of img1:" << endl
         << ROIofimg1 << endl;
    cout << "img1:" << endl
         << RGB_img1 << endl;

    int intvalue2[12] = {255, 0, 0, 255, 0, 0, 255, 0, 0, 255, 0, 0};
    Matrix<int> REDimg(2, 2, 3, intvalue2);
    ROIofimg1.setValueForWholeMatrix(REDimg);
    cout << "ROI of img1:" << endl
         << ROIofimg1 << endl;
    cout << "img1:" << endl
         << RGB_img1 << endl;

    Matrix<int> RGB_img3;
    RGB_img3.clone(ROIofimg1);
    RGB_img3.setValue(0, 0, 2, 255);
    cout << "img3:" << endl
         << RGB_img3 << endl;
    cout << "ROI of img1:" << endl
         << ROIofimg1 << endl;
    cout << "img1:" << endl
         << RGB_img1 << endl;

    float floatvalue[8] = {1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1};
    Matrix<float> floatMatrix(2, 2, 2, floatvalue);
    Matrix<int> intMatrix;
    intMatrix.clone(floatMatrix);
    cout << "the float matrix:" << endl;
    cout << floatMatrix << endl;
    cout << "the int matrix:" << endl;
    cout << intMatrix << endl;
    cout << endl;
    cout << intMatrix + intMatrix << endl;
    cout << endl;
    cout << intMatrix - intMatrix << endl;
    cout << endl;
    cout << intMatrix * intMatrix << endl;

    // int value = RGB_img1.getValue(4, 4, 2);
}