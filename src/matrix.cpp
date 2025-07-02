#include <iostream>
#include <vector>
#include "matrix.hpp"

#if defined(__AVX__)
    #include <immintrin.h>
#elif defined(__ARM_NEON) || defined(__ARM_NEON__)
    #include <arm_neon.h>
#endif

//TODO: implement Overload -, *, dot product, scalar multiplication

// Matrix Initializer Matrix[rows * cols] = 0
Matrix::Matrix(int rows, int cols, bool random): rows(rows), cols(cols){
    this->total = rows * cols;
    data = std::vector<float>(std::vector<float>(total, 0));

    if (random) {
        for (int i = 0; i < total; i++) {
            data[i] = static_cast<float>(rand()) / RAND_MAX;
            
        }
    }
}


// Matrix Addition
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix dimension mismatch");

    Matrix result(rows, cols);

    #if defined(__AVX__)
        for (int i = 0; i < total; i += 8) {
                __m256 a = _mm256_loadu_ps(&data[i]);
                __m256 b = _mm256_loadu_ps(&other.data[i]);
                __m256 c = _mm256_add_ps(a, b);
                _mm256_storeu_ps(&result.data[i], c);
        }
        for (int i = (total / 8) * 8; i < total; ++i) {
            result.data[i] = data[i] + other.data[i];
        }

    #elif defined(__ARM_NEON) || defined(__ARM_NEON__)
        for (int i = 0; i < total; i += 4) {
                float32x4_t a = vld1q_f32(&data[i]);
                float32x4_t b = vld1q_f32(&other.data[i]);
                float32x4_t c = vaddq_f32(a, b);
                vst1q_f32(&result.data[i], c);
        }
        for (int i = (total / 4) * 4; i < total; ++i) {
            result.data[i] = data[i] + other.data[i];
        }

    #else
        for (int i = 0; i < total; ++i)
                result.data[i] = data[i] + other.data[i];

    #endif

    return result;
}


