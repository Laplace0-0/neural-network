#include <gtest/gtest.h>
#include "./helper/matrix_util.hpp"

// 5x5 matrix multiplication test
TEST(MatrixDotTest, Multiplies5x5Correctly) {
    Matrix A(5, 5);
    A.data = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        16, 17, 18, 19, 20,
        21, 22, 23, 24, 25
    };

    Matrix B(5, 5);
    B.data = {
        25, 24, 23, 22, 21,
        20, 19, 18, 17, 16,
        15, 14, 13, 12, 11,
        10, 9, 8, 7, 6,
        5, 4, 3, 2, 1
    };

    Matrix expected(5, 5);
    expected.data = {
        175, 160, 145, 130, 115,
        550, 510, 470, 430, 390,
        925, 860, 795, 730, 665,
        1300, 1210, 1120, 1030, 940,
        1675, 1560, 1445, 1330, 1215
    };


    Matrix result = A * B;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixDotTest, Multiplies5x5WithMixedValues) {
    Matrix A(5, 5);
    A.data = {
        1.5f,  -2.0f,  3.25f,  0.0f,   4.5f,
        -1.1f, 2.2f,  -3.3f,   4.4f,  -5.5f,
        6.6f,  -7.7f,  8.8f,  -9.9f,  10.1f,
        0.0f,   1.0f,  0.0f,   1.0f,   0.0f,
        2.5f,   3.5f, -4.5f,   5.5f,  -6.5f
    };

    Matrix B(5, 5);
    B.data = {
        -7.0f,  8.0f,   9.0f,   1.0f,  2.0f,
         3.0f, -2.0f,   0.5f,  -1.5f,  4.5f,
        -5.5f, 6.5f,   -7.5f,   8.5f, -9.5f,
         1.1f, -2.2f,   3.3f,  -4.4f,  5.5f,
         0.0f,  1.0f,  -1.0f,   2.0f, -2.0f
    };

    Matrix expected(5, 5);
    expected.data = {
        -34.375,  41.625, -16.375,  41.125, -45.875,
        37.29,  -49.83,   35.97,  -62.81,   74.25,
        -128.59,  157.28,  -53.22,  156.71, -179.7,
        4.1,    -4.2,     3.8,    -5.9,    10,
        23.8,   -34.85,   82.65,  -78.2,   106.75
    };


    Matrix result = A * B;

    ASSERT_TRUE(matricesAlmostEqual(result, expected));
}

TEST(MatrixDotTest, ThrowsOnDimensionMismatch) {
    Matrix A(3, 4); // 3 rows, 4 cols
    Matrix B(5, 2); // 5 rows, 2 cols (should be 4 rows to match A's cols)

    // Attempting A * B should throw (cols of A != rows of B)
    EXPECT_THROW({
        Matrix C = A * B;
    }, std::invalid_argument);
}
