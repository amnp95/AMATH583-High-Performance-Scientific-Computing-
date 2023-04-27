#include <iostream>
#include <vector>
#include "hw3_p1_header.hpp"


template <typename T>
void gemm_ijk(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            T sum = 0.0;
            for (int k = 0; k < p; ++k) {
                sum += A[k * m + i] * B[j * p + k];
            }
            C[j * m + i] = a * sum + b * C[j * m + i];
        }
    }
}

template void gemm_ijk(double a, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>& C, int m, int p, int n);
template void gemm_ijk(float a,  const std::vector<float>& A,  const std::vector<float>& B,  float b,  std::vector<float>& C,  int m, int p, int n);
template void gemm_ijk(int a,    const std::vector<int>& A,    const std::vector<int>& B,    int b,    std::vector<int>& C,    int m, int p, int n);





template <typename T>
void gemm_jik(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n) {
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            T sum = 0.0;
            for (int k = 0; k < p; ++k) {
                sum += A[k * m + i] * B[j * p + k];
            }
            C[j * m + i] = a * sum + b * C[j * m + i];
        }
    }
}

template void gemm_jik(double a, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>& C, int m, int p, int n);
template void gemm_jik(float a,  const std::vector<float>& A,  const std::vector<float>& B,  float b,  std::vector<float>& C,  int m, int p, int n);
template void gemm_jik(int a,    const std::vector<int>& A,    const std::vector<int>& B,    int b,    std::vector<int>& C,    int m, int p, int n);





template <typename T>
void gemm_jki(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n) {
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < p; ++k) {
            T tmp = a*B[j * p + k];
            for (int i = 0; i < m; ++i) {
                if (k==0) 
                    C[j * m + i] *= b;
                C[j * m + i] += tmp * A[k * m + i];
            }
        }
    }
}

template void gemm_jki(double alpha, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>& C, int m, int p, int n);
template void gemm_jki(float alpha,  const std::vector<float>& A,  const std::vector<float>& B,  float b,  std::vector<float>& C,  int m, int p, int n);
template void gemm_jki(int alpha,    const std::vector<int>& A,    const std::vector<int>& B,    int b,    std::vector<int>& C,    int m, int p, int n);




template <typename T>
void gemm_ikj(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n) {
    for (int i = 0; i < m; ++i) {
        for (int k = 0; k < p; ++k) {
            T tmp = a*A[k*m + i];
            for (int j = 0; j < n; ++j) {
                if (k==0) 
                    C[j * m + i] *= b;
                C[j * m + i] += tmp * B[j * p + k];
            }
        }
    }
}

template void gemm_ikj(double alpha, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>& C, int m, int p, int n);
template void gemm_ikj(float alpha,  const std::vector<float>& A,  const std::vector<float>& B,  float b,  std::vector<float>& C,  int m, int p, int n);
template void gemm_ikj(int alpha,    const std::vector<int>& A,    const std::vector<int>& B,    int b,    std::vector<int>& C,    int m, int p, int n);




template <typename T>
void gemm_kij(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n) {
    for (int k = 0; k < p; ++k) {
        for (int i = 0; i < m; ++i) {
            T tmp = a*A[k*m + i];
            for (int j = 0; j < n; ++j) {
                if (k==0) 
                    C[j * m + i] *= b;
                C[j * m + i] += tmp * B[j * p + k];
            }
        }
    }
}

template void gemm_kij(double alpha, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>& C, int m, int p, int n);
template void gemm_kij(float alpha,  const std::vector<float>& A,  const std::vector<float>& B,  float b,  std::vector<float>& C,  int m, int p, int n);
template void gemm_kij(int alpha,    const std::vector<int>& A,    const std::vector<int>& B,    int b,    std::vector<int>& C,    int m, int p, int n);


template <typename T>
void gemm_kji(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n) {
    for (int k = 0; k < p; ++k) {
        for (int j = 0; j < n; ++j) {
            T tmp = a*B[j * p + k];
            for (int i = 0; i < m; ++i) {
                if (k==0) 
                    C[j * m + i] *= b;
                C[j * m + i] += tmp * A[k * m + i];
            }
        }
    }
}

template void gemm_kji(double alpha, const std::vector<double>& A, const std::vector<double>& B, double b, std::vector<double>& C, int m, int p, int n);
template void gemm_kji(float alpha,  const std::vector<float>& A,  const std::vector<float>& B,  float b,  std::vector<float>& C,  int m, int p, int n);
template void gemm_kji(int alpha,    const std::vector<int>& A,    const std::vector<int>& B,    int b,    std::vector<int>& C,    int m, int p, int n);

