
#ifndef HW3_P1_HEADER_HPP
#define HW3_P1_HEADER_HPP

#include <iostream>
#include <vector>



template <typename T>
void gemm_ijk(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n);

template <typename T>
void gemm_jik(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n);

template <typename T>
void gemm_ikj(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n);

template <typename T>
void gemm_jki(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n);

template <typename T>
void gemm_kij(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n);

template <typename T>
void gemm_kji(T a, const std::vector<T>& A, const std::vector<T>& B, T b, std::vector<T>& C,int m, int p, int n);

#endif