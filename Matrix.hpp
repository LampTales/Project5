#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Matrix {
   private:
    size_t row;
    size_t col;
    size_t chan;

    uint8_t* p;
    T* data;

    bool isROI;
    size_t ROIrow;
    size_t ROIcol;

   public:
    Matrix();
    Matrix(const Matrix& m);

    Matrix& operator=(const Matrix& m) {
        if (this == &m) {
            cout << "this* is the same as m*" << endl;
            return *this;
        }

        *((size_t*)p) -= 1;
        if (*((size_t*)p) == 0) {
            cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
            free(p);
        }

        this->row = m.row;
        this->col = m.col;
        this->chan = m.chan;
        this->isROI = m.isROI;
        this->ROIrow = m.ROIrow;
        this->ROIcol = m.ROIcol;
        this->p = m.p;
        this->data = m.data;
        *((size_t*)p) += 1;

        return *this;
    };

    template <typename W>
    Matrix& operator=(const Matrix<W>& m) {
        cout << "here!" << endl;
        return *this;
    };

    ~Matrix() {
        *((size_t*)p) -= 1;
        if (*((size_t*)p) == 0) {
            cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
            free(p);
        }
    };
};

template <typename T>
Matrix<T>::Matrix() {
    this->row = 1;
    this->col = 1;
    this->chan = 1;
    this->isROI = false;
    this->p = (uint8_t*)malloc(row * col * chan * sizeof(T) + sizeof(size_t));
    *((size_t*)p) = 1;
    this->data = (T*)(p + sizeof(size_t));
};

template <typename T>
Matrix<T>::Matrix(const Matrix& m) {
    this->row = m.row;
    this->col = m.col;
    this->chan = m.chan;
    this->isROI = m.isROI;
    this->ROIrow = m.ROIrow;
    this->ROIcol = m.ROIcol;
    this->p = m.p;
    this->data = m.data;
    *((size_t*)p) += 1;
};
