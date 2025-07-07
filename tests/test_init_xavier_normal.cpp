#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include <numeric>
#include "./helper/init_util.hpp"


TEST(XavierInitializationTest, FillsMatrixWithCorrectStatistics) {
    int rows = 100;
    int cols = 50;
    Matrix m(rows, cols);

    nn.init.xavier_normal(m);

    float mean, variance;
    compute_mean_variance(m.data, mean, variance);

    float expected_variance = 2.0f / (rows + cols);

    // Allow some tolerance due to randomness
    ASSERT_NEAR(mean, 0.0f, 0.05f);
    ASSERT_NEAR(variance, expected_variance, expected_variance * 0.1f);
}

TEST(XavierInitializationTest, HandlesEmptyMatrix) {
    int rows = 0;
    int cols = 0;
    Matrix m(rows, cols);

    // Should not crash or throw
    ASSERT_NO_THROW({
        nn.init.xavier_normal(m);
    });
    ASSERT_EQ(m.data.size(), 0);
}