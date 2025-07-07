#pragma once
#include "../../include/neural.hpp"
#include <cmath>

inline bool matricesAlmostEqual(const Matrix& A, const Matrix& B, float atol = 1e-4f, float rtol = 1e-4f) {
    if (A.rows != B.rows || A.cols != B.cols) return false;
    for (size_t i = 0; i < A.data.size(); ++i) {
        float diff = std::fabs(A.data[i] - B.data[i]);
        float max_abs = std::max(std::fabs(A.data[i]), std::fabs(B.data[i]));
        if (diff > (atol + rtol * max_abs))
            return false;
    }
    return true;
}

