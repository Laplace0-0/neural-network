#pragma once
#include <cmath>
#include <neural/neural.hpp>
#include <numeric>

inline void compute_mean_variance(const std::vector<float> &data, float &mean,
                                  float &variance) {
  mean = std::accumulate(data.begin(), data.end(), 0.0f) / data.size();
  variance = std::accumulate(data.begin(), data.end(), 0.0f,
                             [mean](float acc, float x) {
                               return acc + (x - mean) * (x - mean);
                             }) /
             data.size();
}
