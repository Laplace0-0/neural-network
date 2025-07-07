#include <gtest/gtest.h>
#include <cmath>
#include "./helper/matrix_util.hpp"

TEST(MatrixScalarMultiplicationTest, MultipliesCorrectlyWithPositiveScalar) {
    Matrix A(2, 2);
    A.data = {2.0f, 3.0f,
              5.0f, 4.0f};

    float scalar = 5.0f;

    Matrix expected(2, 2);
    expected.data = {10.0f, 15.0f,
                     25.0f, 20.0f};

    Matrix result = A * scalar; // or scalarMul(A, scalar);

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixScalarMultiplicationTest, MultipliesCorrectlyWithNegativeScalar) {
    Matrix A(2, 2);
    A.data = {1.0f, -2.0f,
              3.0f, -4.0f};

    float scalar = -3.0f;

    Matrix expected(2, 2);
    expected.data = {-3.0f, 6.0f,
                     -9.0f, 12.0f};

    Matrix result = A * scalar;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixScalarMultiplicationTest, MultipliesCorrectlyWithZeroScalar) {
    Matrix A(2, 2);
    A.data = {7.0f, 8.0f,
              9.0f, 10.0f};

    float scalar = 0.0f;

    Matrix expected(2, 2);
    expected.data = {0.0f, 0.0f,
                     0.0f, 0.0f};

    Matrix result = A * scalar;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixScalarMultiplicationTest, MultipliesEmptyMatrix) {
    Matrix A(0, 0);
    float scalar = 10.0f;

    Matrix expected(0, 0);

    Matrix result = A * scalar;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}
