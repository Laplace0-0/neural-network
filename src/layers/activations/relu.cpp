#include "neural.hpp"

#if defined(__AVX__)
    #include <immintrin.h>
#elif defined(__ARM_NEON) || defined(__ARM_NEON__)
    #include <arm_neon.h>
#endif


void NeuralNetwork::relu(Matrix& x) {

    #if defined(__AVX__)
        for (int i = 0; i < x.total; i += 8) {
                __m256 a = _mm256_loadu_ps(&x.data[i]);
                __m256 b = _mm256_set1_ps(0.0f);
                __m256 c = _mm256_max_ps(a, b);
                _mm256_storeu_ps(&x.data[i], c);
        }
        for (int i = (x.total / 8) * 8; i < x.total; ++i) {
            x.data[i] = std::max(0.0f, x.data[i]);
        }
        return;

    #elif defined(__ARM_NEON) || defined(__ARM_NEON__)
        for (int i = 0; i < x.total; i += 4) {
                float32x4_t a = vld1q_f32(&x.data[i]);
                float32x4_t b = vdupq_n_f32(0.0f);
                float32x4_t c = vmaxq_f32(a, b);
                vst1q_f32(&x.data[i], c);
        }
        for (int i = (x.total / 4) * 4; i < x.total; ++i) {
            x.data[i] = std::max(0.0f, x.data[i]);
        }
        return;

    #endif

    for (int i = 0; i < x.total; ++i) {
        x.data[i] = std::max(0.0f, x.data[i]);
    }
}  