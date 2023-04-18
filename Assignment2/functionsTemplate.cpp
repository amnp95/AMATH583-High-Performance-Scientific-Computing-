#include <iostream>
#include <vector>

template <typename T>
void axpy (T alpha , const std::vector<T> &x , std::vector<T> &y ) {
    if (x.size() == y.size())
    {
        for (int i = 0; i < x.size(); i++)
        {
            y[i] = alpha*x[i] + y[i];
        }
        return;
        
    } else {
        std::cout << "Error : Size of input array must be equal";
        return; 
    }
}




template <typename T>
void gemm(T a, const std::vector<std::vector<T>>& A,
           const std::vector<std::vector<T>>& B, T b,
           std::vector<std::vector<T>>& C) {


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



template <typename T>
void dgemv (T a , const std::vector<std::vector<T>> &A,const std::vector<T> &x , T b , std::vector<T> &y) {

    double res=0;
    if (A[0].size() == x.size() ) {

        if (A.size() == y.size())
        {
            for (int i = 0; i < A.size(); i++)
            {
                res = 0; 
                for (int j = 0; j< x.size(); j++) {
                    res = res + A[i][j]*x[j];
                }
                y[i] = res*a + b*y[i];

            }

        } else
        {
            std::cout << "A matrix and Y vector are not comaptible.\n";
            return;
        }

    } else
    {
        std::cout << "A matrix and X vector are not compatible\n";
        return;
    }
}