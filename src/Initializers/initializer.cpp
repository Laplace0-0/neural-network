#include "logger.hpp"
#include <neural/neural.hpp>

Matrix NeuralNetwork::add_weight(std::string name, int shape,
                                 weightInitializer initializer) {
  printf("Adding weight: %s\n", name.c_str());
  Matrix m(shape, 1);
  switch (initializer) {
  case weightInitializer::ZERO:
    break;

  case weightInitializer::HE_NORMAL:
    nn.init.he_normal(m);
    break;

  case weightInitializer::XAVIER_NORMAL:
    nn.init.xavier_normal(m);
    break;
  default:
    log_error("Invalid initializer");
    break;
  }
  return m;
}