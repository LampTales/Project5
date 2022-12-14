#include <exception>
#include <iostream>
using namespace std;

struct ShapeOversizeException : public exception {
    virtual const char* what() const throw() {
        return "The given shape is too large to create!";
    }
};

struct NULLPointerException : public exception {
    virtual const char* what() const throw() {
        return "The given pointer is NULL!";
    }
};

struct SpotIllegalException : public exception {
    virtual const char* what() const throw() {
        return "The given spot is illegal for this matrix!";
    }
};

struct ROIShapeIllegalException : public exception {
    virtual const char* what() const throw() {
        return "The given ROI shape is out of the original matrix!";
    }
};

struct MatchingIllegalException : public exception {
    virtual const char* what() const throw() {
        return "The shapes of the given matrice do not support such operations!";
    }
};