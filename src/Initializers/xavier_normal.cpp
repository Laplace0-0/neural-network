#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "neural.hpp"

void Initializer::xavier_normal(Matrix &m) {
  std::default_random_engine generator(std::random_device{}());
  std::normal_distribution<float> distribution(
      0.0f, std::sqrt(2.0f / (m.cols + m.rows)));

  for (int i = 0; i < m.total; ++i) {
    m.data[i] = distribution(generator);
  }
}
