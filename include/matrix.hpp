#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

class Matrix {
    public:
        int rows, cols, total;
        std::vector<float> data;

        // Matrix Initializer Matrix[rows][cols] = 0
        Matrix(int rows, int cols, bool random = false);
        
        // Matrix Addition
        Matrix operator+(const Matrix& other) const;
};

#endif