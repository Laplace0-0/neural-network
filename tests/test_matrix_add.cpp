#include <gtest/gtest.h>
#include <cmath>
#include <random>
#include "./helper/matrix_util.hpp"

TEST(MatrixAdditionTest, AddsCorrectlyWithComplexData) {
    Matrix A(4, 4);
    A.data = {
        1e10f,      -1e-10f,   3.141592f,   -2.7182818f,
        99999.999f, -0.0000001f, 42.00042f,   -0.123456f,
        123456.789f, -987654.321f, 0.0000009f, -999.999f,
        0.000000001f, 1e9f,     -1e9f,         0.111111f
    };

    Matrix B(4, 4);
    B.data = {
        -1e10f,     1e-10f,    -3.141592f,    2.7182818f,
        -99999.999f, 0.0000001f, -42.00042f,   0.123456f,
        -123456.789f, 987654.321f, -0.0000009f, 999.999f,
        -0.000000001f, -1e9f,   1e9f,         -0.111111f
    };

    Matrix expected(4, 4);
    expected.data = std::vector<float>(16, 0.0f);  // All results should be 0 if precise

    Matrix result = A + B;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}


TEST(MatrixAdditionTest, ComplexAdd) {
    Matrix A(4, 4);
    A.data = {
        1234.5678f, -9876.5432f,  0.0001f,   3.141592f,
        -2.71828f,   1.61803f,   -0.33333f,  99999.9999f,
        0.000001f,  -0.000001f,  42.4242f,  -42.4242f,
        1000000.1f, -1000000.1f, 0.123456f, -0.123456f
    };

    Matrix B(4, 4);
    B.data = {
        -1234.5678f,  9876.5432f, -0.0001f,  -3.141592f,
         2.71828f,   -1.61803f,   0.33333f, -99999.9999f,
        -0.000001f,   0.000001f, -42.4242f,  42.4242f,
        -1000000.1f,  1000000.1f, -0.123456f, 0.123456f
    };

    Matrix expected(4, 4);
    expected.data = std::vector<float>(16, 0.0f);  // All elements should be 0

    Matrix result = A + B;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixAdditionTest, Large512x256Addition) {
    const int rows = 512;
    const int cols = 256;

    Matrix A(rows, cols);
    Matrix B(rows, cols);
    Matrix expected(rows, cols);

    // Fill A and B with random data, compute expected
    std::mt19937 rng(42);  // Fixed seed for consistency
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);

    for (int i = 0; i < rows * cols; ++i) {
        A.data[i] = dist(rng);
        B.data[i] = dist(rng);
        expected.data[i] = A.data[i] + B.data[i];
    }

    Matrix result = A + B;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixAdditionTest, ThrowsOnDimensionMismatch) {
    Matrix A(2, 2);
    Matrix B(3, 3);  // Mismatched dimensions

    EXPECT_THROW({
        Matrix C = A + B;
    }, std::invalid_argument);
}
