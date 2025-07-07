#pragma once

#include <vector>

class Matrix {
public:
    int rows, cols, total;
    std::vector<float> data;

    // Constructor: Initializes matrix with zeros
    Matrix(int rows, int cols);

    // Matrix Addition
    Matrix operator+(const Matrix& other) const;

    // Matrix Subtraction
    Matrix operator-(const Matrix& other) const;

    // Matrix Scalar Multiplication
    Matrix operator*(const Matrix& other) const;   // Matrix-Matrix multiplication
    
    Matrix operator*(float scalar) const;          // Scalar multiplication


    // Matrix Transpose
    void tp();

    // Print Matrix
    void print() const;
};



