#include <iostream>
#include <vector>

template <typename T>
void gemm_ijk(const int m, const int n, const int p, const T alpha, const T beta, const std::vector<T>& A, const std::vector<T>& B, std::vector<T>& C) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            T sum = 0.0;
            for (int k = 0; k < p; ++k) {
                sum += A[k * m + i] * B[j * p + k];
            }
            C[j * m + i] = alpha * sum + beta * C[j * m + i];
        }
    }
}

int main() {
    const int m = 3;
    const int n = 4;
    const int p = 2;
    const double alpha = 3.1;
    const double beta = 2.4;

    std::vector<double> A = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::vector<double> B = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0};
    std::vector<double> C = {1.0, 4.0, 8.0, 2.0, 5.0, 9.0, 3.0, 6.0, 10.0, 4.0, 7.0, 11.0 };

    gemm_ijk(m, n, p, alpha, beta, A, B, C);

    std::cout << "C = ";
    for (int i = 0; i < m * n; ++i) {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}