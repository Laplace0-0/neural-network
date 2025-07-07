#include<gtest/gtest.h>
#include <cmath>
#include <random>
#include "./helper/matrix_util.hpp"

TEST(MatrixSubtractionTest, SubtractsCorrectlySimple) {
    Matrix A(2, 2);
    A.data = {5, 7, 9, 11};

    Matrix B(2, 2);
    B.data = {1, 2, 3, 4};

    Matrix expected(2, 2);
    expected.data = {4, 5, 6, 7};

    Matrix result = A - B;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixSubtractionTest, SubtractsCorrectlyComplex) {
    Matrix A(2, 2);
    A.data = {1e6f, -1e6f, 3.14f, -2.71f};

    Matrix B(2, 2);
    B.data = {999999.0f, -1000001.0f, 3.14f, 1.0f};

    Matrix expected(2, 2);
    expected.data = {1.0f, 1.0f, 0.0f, -3.71f};

    Matrix result = A - B;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixSubtractionTest, ThrowsOnDimensionMismatch) {
    Matrix A(2, 3);
    Matrix B(3, 2);  // Mismatch

    EXPECT_THROW({
        Matrix C = A - B;
    }, std::invalid_argument);
}