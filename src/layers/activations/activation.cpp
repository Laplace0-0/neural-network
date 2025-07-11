#include <neural/neural.hpp>

Matrix NeuralNetwork::activation(Matrix &x, Activation activation) {

  switch (activation) {
  case Activation::RELU:
    nn.relu(x);
    break;

  case Activation::SIGMOID:
    break;

  case Activation::TANH:
    break;

  default:
    break;
  }

  return x;
}