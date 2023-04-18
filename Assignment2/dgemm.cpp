
#include <iostream>
#include <vector>

// void dgemm(double a , const std::vector<std::vector<double>> &A,
// const std::vector<std::vector<double>> &B, double b ,
// std::vector<std::vector<double>> &C) {
// }

void dgemm(double a, const std::vector<std::vector<double>>& A,
           const std::vector<std::vector<double>>& B, double b,
           std::vector<std::vector<double>>& C) {


    double sum = 0.0;
    // Check matrix dimensions
    if (A.size() == C.size() && B[0].size() == C[0].size() && A[0].size() == B.size()) {

        // Compute matrix product aA * B and add to b*C
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < B[0].size(); j++) {
                sum = 0.0;
                for (int k = 0; k < B.size(); k++) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = a * sum + b* C[i][j];
            }
        }
    } else {

        std::cout << "Dimensions are not compatible\n";
        return;

    }

}