#include <exception>
#include <iostream>
using namespace std;

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

struct MatchingIllegalException : public exception {
    virtual const char* what() const throw() {
        return "The shapes of the given matrice do not support such operations!";
    }
};