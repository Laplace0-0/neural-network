#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "matrix.hpp"

#if defined(__AVX__)
    #include <immintrin.h>
#elif defined(__ARM_NEON) || defined(__ARM_NEON__)
    #include <arm_neon.h>
#endif

// Matrix Initializer Matrix[rows * cols] = 0
Matrix::Matrix(int rows, int cols): rows(rows), cols(cols), total(rows * cols), data(total, 0.0f) {}

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

// Matrix Subtraction
Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix dimension mismatch");
    
    Matrix result(rows, cols);

    #if defined(__AVX__)
        for (int i = 0; i < total; i += 8) {
                __m256 a = _mm256_loadu_ps(&data[i]);
                __m256 b = _mm256_loadu_ps(&other.data[i]);
                __m256 c = _mm256_sub_ps(a, b);
                _mm256_storeu_ps(&result.data[i], c);
        }
        for (int i = (total / 8) * 8; i < total; ++i) {
            result.data[i] = data[i] - other.data[i];
        }

    #elif defined(__ARM_NEON) || defined(__ARM_NEON__)
        for (int i = 0; i < total; i += 4) {
                float32x4_t a = vld1q_f32(&data[i]);
                float32x4_t b = vld1q_f32(&other.data[i]);
                float32x4_t c = vsubq_f32(a, b);
                vst1q_f32(&result.data[i], c);
        }
        for (int i = (total / 4) * 4; i < total; ++i) {
            result.data[i] = data[i] - other.data[i];
        }

    #else
        for (int i = 0; i < total; ++i)
                result.data[i] = data[i] - other.data[i];

    #endif

    return result;
}

// Matrix Multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Matrix dimension mismatch");

    Matrix result(rows, other.cols);

    if ((cols < 4) || (rows < 4)){
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                float sum = 0;
                for (int k = 0; k < cols; ++k) {
                    sum += data[i * cols + k] * other.data[k * other.cols + j];
                }
                result.data[i * other.cols + j] = sum;
            }
        }

        return result;
    }

    #if defined(__ARM_NEON) || defined(__ARM_NEON__)

        Matrix B_T = other;
        B_T.tp();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                float sum = 0.0f;

                float32x4_t sum_vec = vdupq_n_f32(0.0f);
                int k = 0;
                for (; k + 3 < cols; k += 4) {
                    float32x4_t a = vld1q_f32(&data[i * cols + k]);
                    float32x4_t b = vld1q_f32(&B_T.data[j * B_T.cols + k]);
                    sum_vec = vmlaq_f32(sum_vec, a, b);
                }

                sum += vaddvq_f32(sum_vec);

                for (; k < cols; ++k) {
                    sum += data[i * cols + k] * B_T.data[j * B_T.cols + k]; 
                }

                result.data[i * other.cols + j] = sum;
            }
        }

        return result;
    #else
        // Scalar fallback
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                float sum = 0.0f;
                for (int k = 0; k < cols; ++k) {
                    sum += data[i * cols + k] * other.data[k * other.cols + j];
                }
                result.data[i * other.cols + j] = sum;
            }
        }
        return result;

    #endif

}

// Matrix scalar Multiplication
Matrix Matrix::operator*(float scalar) const {
    Matrix result(rows, cols);

    #if defined(__AVX__)
        for (int i = 0; i < total; i += 8) {
                __m256 a = _mm256_loadu_ps(&data[i]);
                __m256 b = _mm256_set1_ps(scalar);
                __m256 c = _mm256_mul_ps(a, b);
                _mm256_storeu_ps(&result.data[i], c);
        }
        for (int i = (total / 8) * 8; i < total; ++i) {
            result.data[i] = data[i] * other.data[i];
        }

    #elif defined(__ARM_NEON) || defined(__ARM_NEON__)
        for (int i = 0; i < total; i += 4) {
                float32x4_t a = vld1q_f32(&data[i]);
                float32x4_t c = vmulq_f32(a, vdupq_n_f32(scalar));
                vst1q_f32(&result.data[i], c);
        }
        for (int i = (total / 4) * 4; i < total; ++i) {
            result.data[i] = data[i] * scalar;
        }

    #else

        for (int i = 0; i < total; ++i)
            result.data[i] = data[i] * scalar;

    #endif

    return result;
}

void Matrix::tp() {
    Matrix result(cols, rows); // Transpose will flip dimensions

    if ((cols < 4) || (rows < 4)) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j * rows + i] = data[i * cols + j];
            }
        }
    }
    else {
    #if defined(__ARM_NEON) || defined(__ARM_NEON__)
        for (int i = 0; i < rows; ++i) {
            int j = 0;
            for (; j + 3 < cols; j += 4) {
                float32x4_t a = vld1q_f32(&data[i * cols + j]);

                result.data[(j + 0) * rows + i] = vgetq_lane_f32(a, 0);
                result.data[(j + 1) * rows + i] = vgetq_lane_f32(a, 1);
                result.data[(j + 2) * rows + i] = vgetq_lane_f32(a, 2);
                result.data[(j + 3) * rows + i] = vgetq_lane_f32(a, 3);
            }

            // Handle remaining elements
            for (; j < cols; ++j) {
                result.data[j * rows + i] = data[i * cols + j];
            }
        }
    #endif
    }

    std::swap(rows, cols);
    data = std::move(result.data);
}

// Print Matrix
void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        std::cout << "[ ";
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i * cols + j] << " ";
        }
        std::cout << "]\n";
    }
}

