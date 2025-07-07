#include<gtest/gtest.h>
#include <cmath>
#include <random>
#include "./helper/matrix_util.hpp"


TEST(MatrixTransposeTest, TransposesLargeMatrixWithMixedValues) {
    Matrix A(3, 4);
    A.data = {
        1e6f, -2.5f, 0.0f, 3.14f,
        -1e6f, 7.77f, -8.88f, 9.99f,
        42.0f, -100.0f, 1e-3f, -1e-3f
    };

    Matrix expected(4, 3);
    expected.data = {
        1e6f, -1e6f, 42.0f,
        -2.5f, 7.77f, -100.0f,
        0.0f, -8.88f, 1e-3f,
        3.14f, 9.99f, -1e-3f
    };

    A.tp();

    ASSERT_TRUE(matricesAlmostEqual(A, expected));
}

TEST(MatrixTransposeTest, TransposesMatrixWithInfinityAndNaN) {
    Matrix A(2, 3);
    A.data = {
        std::numeric_limits<float>::infinity(), -1.0f, std::nanf(""),
        0.0f, -std::numeric_limits<float>::infinity(), 2.0f
    };

    Matrix expected(3, 2);
    expected.data = {
        std::numeric_limits<float>::infinity(), 0.0f,
        -1.0f, -std::numeric_limits<float>::infinity(),
        std::nanf(""), 2.0f
    };

    A.tp();

    // If you have a custom comparison for NaN and infinity
    ASSERT_TRUE(matricesAlmostEqual(A, expected));
}

TEST(MatrixTransposeTest, TransposesMatrixWithRepeatingPatterns) {
    Matrix A(2, 3);
    A.data = {
        1.0f, 2.0f, 1.0f,
        2.0f, 1.0f, 2.0f
    };

    Matrix expected(3, 2);
    expected.data = {
        1.0f, 2.0f,
        2.0f, 1.0f,
        1.0f, 2.0f
    };

   A.tp();

    ASSERT_TRUE(matricesAlmostEqual(A, expected));
}

