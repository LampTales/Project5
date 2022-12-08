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
    Matrix() {
        this->row = 1;
        this->col = 1;
        this->chan = 1;
        this->isROI = false;
        this->p = malloc(row * col * chan * sizeof(T) + sizeof(size_t));
        *((size_t*)p) = 1;
        this->data = (T*)(p + sizeof(size_t));
    };

    Matrix(const Matrix& m) {
        *((size_t*)p) -= 1;
        if (*((size_t*)p) == 0) {
            cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
            free(p);
        }
    }

    ~Matrix() {
        *((size_t*)p) -= 1;
        if (*((size_t*)p) == 0) {
            cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
            free(p);
        }
    };
};
