#include <iostream>
#include <vector>
#include "hw3_p1_header.hpp"

template <typename T>
void print (const char* str, std::vector<T> D) {

    std::cout << str <<"= ";
    for (int i = 0; i < D.size(); ++i) {
        std::cout << D[i] << " ";
    }
    std::cout << std::endl;
}



int main() {


    const int m = 3;
    const int n = 4;
    const int p = 2;
    const double a = 1.2;
    const double b = 2.1;

    std::vector<double> A = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::vector<double> B = {7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0};
    std::vector<double> C = {1.0, 4.0, 8.0, 2.0, 5.0, 9.0, 3.0, 6.0, 10.0, 4.0, 7.0, 11.0 };
    std::vector<double> D;



    D = C;
    gemm_ijk(a, A, B, b, D,m, p, n);
    print("gemm_ijk", D);

    D = C;
    gemm_jik(a, A, B, b, D,m, p, n);
    print("gemm_jik", D);

    D = C;
    gemm_jki(a, A, B, b, D,m, p, n);
    print("gemm_jki", D);

    D = C;
    gemm_ikj(a, A, B, b, D,m, p, n);
    print("gemm_ikj", D);

    D = C;
    gemm_kij(a, A, B, b, D,m, p, n);
    print("gemm_kij", D);

    D = C;
    gemm_kji(a, A, B, b, D,m, p, n);
    print("gemm_kji", D);
    return 0;
}