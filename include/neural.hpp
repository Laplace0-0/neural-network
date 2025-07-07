#ifndef NEURAL_HPP
#define NEURAL_HPP

#include "matrix.hpp"

class Matrix;

class Initializer {
    public:
        void he_normal(Matrix& m);
        void xavier_normal(Matrix& m);    
};   

class NeuralNetwork {
public:
    Initializer init;
};

extern NeuralNetwork nn;

#endif