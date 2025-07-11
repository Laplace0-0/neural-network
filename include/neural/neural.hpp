#ifndef NEURAL_HPP
#define NEURAL_HPP

#include "matrix.hpp"

class Matrix;

enum class Activation { NONE, RELU, SIGMOID, TANH };

enum class weightInitializer { ZERO, HE_NORMAL, XAVIER_NORMAL };

struct DenseConfig {
  int neurons;
  int input_shape;
  weightInitializer weight_initializer = weightInitializer::ZERO;
  weightInitializer bias_initializer = weightInitializer::ZERO;
  bool use_bias = true;
  Activation activation = Activation::NONE;
  std::string name;
  bool is_trainable = true;
  float dropout_rate = 0.0f;
};

class Initializer {
public:
  void he_normal(Matrix &m);
  void xavier_normal(Matrix &m);
};

class Dense {
public:
  int neurons;
  int input_shape;
  weightInitializer weight_initializer = weightInitializer::ZERO;
  weightInitializer bias_initializer = weightInitializer::ZERO;
  bool use_bias = true;
  Activation activation = Activation::NONE;
  std::string name;
  bool is_trainable = true;
  float dropout_rate = 0.0f;
  Matrix weight;
  Matrix bias;

  // Constructor: Initializes matrix with zeros
  Dense(const DenseConfig &config);
};

class NeuralNetwork {
public:
  // Activation Functions
  void relu(Matrix &x);
  Matrix activation(Matrix &x, Activation act);
  Matrix add_weight(std::string name, int neurons, int shape,
                    weightInitializer initializer);

  // weight Intialization
  Initializer init;
};

extern NeuralNetwork nn;

#endif