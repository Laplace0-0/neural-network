#include "logger.hpp"
#include "neural.hpp"
/*
    Dense Layer (default initializer is zero for weight and bias)
    Dense(
        neurons, (output_shape: rows)
        input_shape (for Input layer only), (input_shape: cols) -> if not
   provided, it is takes from neurons of previous layer weight_initializer,
        weight_regularizer,
        bool use_bias,
        bias_initializer,
        bias_regularizer,
        activation,
        name,
        bool is_trainable,
        float dropout_rate
    )
*/

Dense::Dense(const DenseConfig &config)
    : neurons(config.neurons), input_shape(config.input_shape),
      weight_initializer(config.weight_initializer),
      bias_initializer(config.bias_initializer), use_bias(config.use_bias),
      activation(config.activation), name(config.name),
      is_trainable(config.is_trainable), dropout_rate(config.dropout_rate),
      weight(config.input_shape, config.neurons), bias(config.neurons, 1) {

  if (neurons <= 0)
    log_error("Number of neurons must be greater than 0");

  weight = nn.add_weight("_weight",         // name
                         input_shape,       // shape
                         weight_initializer // initializer
  );

  if (use_bias) {
    bias = nn.add_weight("_bias",         // name
                         neurons,         // shape
                         bias_initializer // initializer
    );
  }
}
