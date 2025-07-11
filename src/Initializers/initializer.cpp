#include "logger.hpp"
#include <neural/neural.hpp>

Matrix NeuralNetwork::add_weight(std::string name, int neurons, int shape,
                                 weightInitializer initializer) {
  Matrix m(neurons, shape);
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