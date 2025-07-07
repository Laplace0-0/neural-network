#include <iostream>
#include <vector>
#include <cmath>
#include <random>

#include "neural.hpp"
// Matrix weight Intialization

void Initializer::he_normal(Matrix &m) {
    std::default_random_engine generator(std::random_device{}());
    std::normal_distribution<float> distribution(0.0f, std::sqrt(2.0f / m.cols));

    for (int i = 0; i < m.total; ++i) {
        m.data[i] = distribution(generator);
    }
}


NeuralNetwork nn;