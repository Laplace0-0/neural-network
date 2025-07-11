#include <iostream>
#include <neural/neural.hpp>
#include <vector>

int main() {
  Matrix A(3, 3), B(3, 3), C(3, 3), D(3, 3), E(3, 3);
  /*
      int neurons,
      int input_shape,
      weightInitializer weight_initializer = weightInitializer::ZERO,
      weightInitializer bias_initializer = weightInitializer::ZERO,
      bool use_bias = true,
      Activation activation,
      std::string name,
      bool is_trainable = true,
      float dropout_rate = 0.0f
  */

  Dense *dense =
      new Dense({.neurons = 3,
                 .input_shape = 3,
                 .activation = Activation::RELU,
                 .bias_initializer = weightInitializer::XAVIER_NORMAL,
                 .weight_initializer = weightInitializer::XAVIER_NORMAL,
                 .use_bias = false,
                 .name = "Dense1"});

  dense->weight.print();

  return 0;
}