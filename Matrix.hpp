#pragma once
#include <string.h>
#include <iostream>
#include "MatrixException.hpp"

using namespace std;

template <typename T>
class Matrix {
   private:
    size_t row;
    size_t col;
    size_t chan;

    uint8_t* p;

    bool isROI;
    size_t ROIspot;
    size_t ROIrow;
    size_t ROIcol;

   public:
    Matrix();
    Matrix(size_t row, size_t col, size_t chan);
    Matrix(size_t row, size_t col, size_t chan, const T* values);
    Matrix(const Matrix& m);
    ~Matrix();

    Matrix& operator=(const Matrix& m);
    bool operator==(const Matrix& m);
    bool operator!=(const Matrix& m);
    size_t getRow() const;
    size_t getCol() const;
    size_t getChan() const;
    T getValue(size_t rowSpot, size_t colSpot, size_t chanSpot) const;
    void setValue(size_t rowSpot, size_t colSpot, size_t chanSpot, T value);
    void setValueForWholeMatrix(const T* values);
    void clone(const Matrix& m);

    template <typename X>
    void clone(const Matrix<X>& m);

    bool beROI();
    void setROIfrom(Matrix source, size_t ROIrowSpot, size_t ROIcolSpot, size_t ROIrow, size_t ROIcol);

    template <typename W>
    friend Matrix<W> operator+(const Matrix<W>& a, const Matrix<W>& b);
    template <typename W>
    friend Matrix<W> operator-(const Matrix<W>& a, const Matrix<W>& b);
    template <typename W>
    friend Matrix<W> operator*(const Matrix<W>& a, const Matrix<W>& b);
    template <typename W>
    friend ostream& operator<<(ostream& out, const Matrix<W>& m);
};

// implementation
template <typename T>
Matrix<T>::Matrix()
    : row(1), col(1), chan(1), isROI(false), ROIspot(0), ROIrow(1), ROIcol(1) {
    cout << "here is simplest constructor" << endl;
    this->p = (uint8_t*)malloc(row * col * chan * sizeof(T) + sizeof(size_t));
    *((size_t*)p) = 1;
};

template <typename T>
Matrix<T>::Matrix(size_t row, size_t col, size_t chan)
    : row(row), col(col), chan(chan), isROI(false), ROIspot(0), ROIrow(row), ROIcol(col) {
    this->p = (uint8_t*)malloc(row * col * chan * sizeof(T) + sizeof(size_t));
    if (p == NULL) {
        throw ShapeOversizeException();
    }
    *((size_t*)p) = 1;
}

template <typename T>
Matrix<T>::Matrix(size_t row, size_t col, size_t chan, const T* values)
    : row(row), col(col), chan(chan), isROI(false), ROIspot(0), ROIrow(row), ROIcol(col) {
    if (values == NULL) {
        throw NULLPointerException();
    }

    this->p = (uint8_t*)malloc(row * col * chan * sizeof(T) + sizeof(size_t));
    if (p == NULL) {
        throw ShapeOversizeException();
    }
    memcpy((p + sizeof(size_t)), values, (row * col * chan * sizeof(T)));
    *((size_t*)p) = 1;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& m)
    : row(m.row), col(m.col), chan(m.chan), isROI(m.isROI), ROIspot(m.ROIspot), ROIrow(m.ROIrow), ROIcol(m.ROIcol), p(m.p) {
    cout << "here is copy constructor" << endl;
    *((size_t*)p) += 1;
};

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m) {
    cout << "here is =" << endl;
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
    this->ROIspot = m.ROIspot;
    this->ROIrow = m.ROIrow;
    this->ROIcol = m.ROIcol;
    this->p = m.p;
    *((size_t*)p) += 1;

    return *this;
};

template <typename T>
bool Matrix<T>::operator==(const Matrix& m) {
    return (this->p == m.p && this->ROIspot == m.ROIspot && this->ROIrow == m.ROIrow && this->ROIcol == m.ROIcol && this->isROI == m.isROI);
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix& m) {
    return !((*this) == m);
}

template <typename T>
size_t Matrix<T>::getRow() const {
    return this->ROIrow;
}

template <typename T>
size_t Matrix<T>::getCol() const {
    return this->ROIcol;
}

template <typename T>
size_t Matrix<T>::getChan() const {
    return this->chan;
}

template <typename T>
T Matrix<T>::getValue(size_t rowSpot, size_t colSpot, size_t chanSpot) const {
    if ((rowSpot + 1) > (this->ROIrow) || (colSpot + 1) > (this->ROIcol) || (chanSpot + 1) > (this->chan)) {
        throw SpotIllegalException();
    }

    T* data = (T*)(p + sizeof(size_t));
    return data[ROIspot + (rowSpot * this->col + colSpot) * this->chan + chanSpot];
}

template <typename T>
void Matrix<T>::setValue(size_t rowSpot, size_t colSpot, size_t chanSpot, T value) {
    if ((rowSpot + 1) > (this->ROIrow) || (colSpot + 1) > (this->ROIcol) || (chanSpot + 1) > (this->chan)) {
        throw SpotIllegalException();
    }

    T* data = (T*)(p + sizeof(size_t));
    data[ROIspot + (rowSpot * this->col + colSpot) * this->chan + chanSpot] = value;
}

template <typename T>
void Matrix<T>::setValueForWholeMatrix(const T* values) {
    if (values == NULL) {
        throw NULLPointerException();
    }
    T* data = (T*)(p + sizeof(size_t));
    size_t length = ROIcol * chan;
    for (size_t i = 0; i < ROIrow; i++) {
        memcpy(data + ROIspot + i * col * chan, values + i * length, length * sizeof(T));
    }
}

template <typename T>
void Matrix<T>::clone(const Matrix& m) {
    cout << "clone1" << endl;
    if (this == &m) {
        uint8_t* np = (uint8_t*)malloc(this->row * this->col * this->chan * sizeof(T) + sizeof(size_t));
        *((size_t*)np) = 1;
        T* data = (T*)(p + sizeof(size_t));
        T* Ndata = (T*)(np + sizeof(size_t));
        size_t length = ROIcol * chan;
        for (size_t i = 0; i < this->ROIrow; i++) {
            memcpy(Ndata + length * i, data + ROIspot + col * chan * i, length * sizeof(T));
        }

        *((size_t*)p) -= 1;
        if (*((size_t*)p) == 0) {
            cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
            free(p);
        }
        this->p = np;
        this->isROI = false;
        this->ROIspot = 0;
        this->row = this->ROIrow;
        this->col = this->ROIcol;
        return;
    }

    *((size_t*)p) -= 1;
    if (*((size_t*)p) == 0) {
        cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
        free(p);
    }

    this->row = m.ROIrow;
    this->col = m.ROIcol;
    this->chan = m.chan;
    this->isROI = false;
    this->ROIspot = 0;
    this->ROIrow = m.ROIrow;
    this->ROIcol = m.ROIcol;

    this->p = (uint8_t*)malloc(this->row * this->col * this->chan * sizeof(T) + sizeof(size_t));
    *((size_t*)p) = 1;
    T* data = (T*)(p + sizeof(size_t));
    T* oriData = (T*)(m.p + sizeof(size_t));
    size_t length = this->col * this->chan;
    for (size_t i = 0; i < this->row; i++) {
        memcpy(data + length * i, oriData + m.ROIspot + m.col * m.chan * i, length * sizeof(T));
    }
}

template <typename T>
template <typename X>
void Matrix<T>::clone(const Matrix<X>& m) {
    cout << "clone2" << endl;
    *((size_t*)p) -= 1;
    if (*((size_t*)p) == 0) {
        cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
        free(p);
    }

    this->row = m.getRow();
    this->col = m.getCol();
    this->chan = m.getChan();
    this->isROI = false;
    this->ROIspot = 0;
    this->ROIrow = this->row;
    this->ROIcol = this->col;

    this->p = (uint8_t*)malloc(this->row * this->col * this->chan * sizeof(T) + sizeof(size_t));
    if (p == NULL) {
        throw ShapeOversizeException();
    }
    *((size_t*)p) = 1;
    T* data = (T*)(p + sizeof(size_t));
    size_t cpySpot = 0;
    for (size_t i = 0; i < this->row; i++) {
        for (size_t j = 0; j < this->col; j++) {
            for (size_t k = 0; k < this->chan; k++) {
                data[cpySpot] = (T)m.getValue(i, j, k);
                cpySpot++;
            }
        }
    }
}

template <typename T>
bool Matrix<T>::beROI() {
    return this->isROI;
}

template <typename T>
void Matrix<T>::setROIfrom(Matrix m, size_t ROIrowSpot, size_t ROIcolSpot, size_t ROIrow, size_t ROIcol) {
    if (ROIrowSpot + ROIrow > m.ROIrow || ROIcolSpot + ROIcol > m.ROIcol) {
        throw ROIShapeIllegalException();
    }

    this->row = m.row;
    this->col = m.col;
    this->chan = m.chan;
    this->isROI = true;
    this->ROIrow = ROIrow;
    this->ROIcol = ROIcol;
    this->ROIspot = m.ROIspot + (ROIrowSpot * m.col + ROIcolSpot) * this->chan;

    *((size_t*)(m.p)) += 1;

    *((size_t*)p) -= 1;
    if (*((size_t*)p) == 0) {
        cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
        free(p);
    }

    this->p = m.p;
}

template <typename T>
Matrix<T> operator+(const Matrix<T>& a, const Matrix<T>& b) {
    if (a.ROIrow != b.ROIrow || a.ROIcol != b.ROIcol || a.chan != b.chan) {
        throw MatchingIllegalException();
    }
    Matrix<T> ans(a.ROIrow, a.ROIcol, a.chan);
    T* store = (T*)(ans.p + sizeof(size_t));
    T* ap = (T*)(a.p + sizeof(size_t));
    T* bp = (T*)(b.p + sizeof(size_t));

    for (size_t i = 0; i < a.ROIrow; i++) {
        size_t storeSpot = i * a.ROIcol * a.chan;
        size_t apSpot = a.ROIspot + i * a.col * a.chan;
        size_t bpSpot = b.ROIspot + i * b.col * b.chan;
        for (size_t j = 0; j < a.ROIcol * a.chan; j++) {
            store[storeSpot + j] = ap[apSpot + j] + bp[bpSpot + j];
        }
    }
    return ans;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& a, const Matrix<T>& b) {
    if (a.ROIrow != b.ROIrow || a.ROIcol != b.ROIcol || a.chan != b.chan) {
        throw MatchingIllegalException();
    }
    Matrix<T> ans(a.ROIrow, a.ROIcol, a.chan);
    T* store = (T*)(ans.p + sizeof(size_t));
    T* ap = (T*)(a.p + sizeof(size_t));
    T* bp = (T*)(b.p + sizeof(size_t));

    for (size_t i = 0; i < a.ROIrow; i++) {
        size_t storeSpot = i * a.ROIcol * a.chan;
        size_t apSpot = a.ROIspot + i * a.col * a.chan;
        size_t bpSpot = b.ROIspot + i * b.col * b.chan;
        for (size_t j = 0; j < a.ROIcol * a.chan; j++) {
            store[storeSpot + j] = ap[apSpot + j] - bp[bpSpot + j];
        }
    }
    return ans;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) {
    if (a.ROIcol != b.ROIrow || a.chan != b.chan) {
        throw MatchingIllegalException();
    }
    Matrix<T> ans(a.ROIrow, b.ROIcol, a.chan);
    for (size_t chanCnt = 0; chanCnt < ans.chan; chanCnt++) {
        for (size_t rowCnt = 0; rowCnt < ans.ROIrow; rowCnt++) {
            for (size_t colCnt = 0; colCnt < ans.ROIcol; colCnt++) {
                T sum = 0;
                for (size_t i = 0; i < a.ROIcol; i++) {
                    sum += a.getValue(rowCnt, i, chanCnt) * b.getValue(i, colCnt, chanCnt);
                }
                ans.setValue(rowCnt, colCnt, chanCnt, sum);
            }
        }
    }

    return ans;
}
// break break break break break break break

template <typename T>
ostream& operator<<(ostream& out, const Matrix<T>& m) {
    out << "{";
    size_t spot = m.ROIspot;
    T* data = (T*)(m.p + sizeof(size_t));
    for (size_t i = 0; i < m.ROIrow; i++) {
        spot = m.ROIspot + i * m.col * m.chan;
        out << "[";
        for (size_t j = 0; j < m.ROIcol; j++) {
            out << "(";
            for (size_t k = 0; k < m.chan; k++) {
                out << data[spot];
                if (k != m.chan - 1) {
                    out << ",";
                }
                spot++;
            }
            out << ")";
            if (j != m.ROIcol - 1) {
                out << " ";
            }
        }
        out << "]";
        if (i != m.ROIrow - 1) {
            out << endl;
        }
    }
    out << "}";
    return out;
}

template <typename T>
Matrix<T>::~Matrix() {
    *((size_t*)p) -= 1;
    if (*((size_t*)p) == 0) {
        cout << "My smart pointer was pointed by cnt 0, time to release!" << endl;
        free(p);
    }
}