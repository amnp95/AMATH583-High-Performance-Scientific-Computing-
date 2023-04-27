#include <iostream>
#include <vector>



template <typename T>
std::vector<std::vector<T>> strassen_mm ( const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B )
{
    int n = A.size();
    
    if (n==2) {
        std::vector<std::vector<T>> C(2,std::vector<T>(2));
        T p1 = (A[0][0]+A[1][1])*(B[0][0]+B[1][1]);
        T p2 = (A[1][0]+A[1][1])*B[0][0];
        T p3 = A[0][0]*(B[0][1]-B[1][1]);
        T p4 = A[1][1]*(B[1][0]-B[0][0]);
        T p5 = (A[0][0]+A[0][1])*B[1][1];
        T p6 = (A[1][0]-A[0][0])*(B[0][0]+B[0][1]);
        T p7 = (A[0][1]-A[1][1])*(B[1][0]+B[1][1]);
        C[0][0] = p1 + p4 - p5 + p7;
        C[0][1] = p3 + p5;
        C[1][0] = p2 + p4;
        C[1][1] = p1 + p3 - p2 + p6;
        return C;
    }

    // Divide the matrices into submatrices
    int k = n / 2;
    std::vector<std::vector<T>>  A11(k, std::vector<T>(k));
    std::vector<std::vector<T>>  A12(k, std::vector<T>(k)); 
    std::vector<std::vector<T>>  A21(k, std::vector<T>(k)); 
    std::vector<std::vector<T>>  A22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B11(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B12(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B21(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B22(k, std::vector<T>(k));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Recursive calls to compute the submatrices of the product
    std::vector<std::vector<T>> C11(k, std::vector<T>(k)); 
    std::vector<std::vector<T>> C12(k, std::vector<T>(k)); 
    std::vector<std::vector<T>> C21(k, std::vector<T>(k));
    std::vector<std::vector<T>> C22(k, std::vector<T>(k));
    C11 = strassen_mm(A11, B11) + strassen_mm(A12, B21);
    C12 = strassen_mm(A11, B12) + strassen_mm(A12, B22);
    C21 = strassen_mm(A21, B11) + strassen_mm(A22, B21);
    C22 = strassen_mm(A21, B12) + strassen_mm(A22, B22);


    // Combine the submatrices to form the product matrix
    std::vector<std::vector<T>> C(n, std::vector<T>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
    return C;
}




int main() {

    std::vector<std::vector<int>> A = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> B = {{5, 6}, {7, 8}};

    // Compute the product of the matrices using recursive matmul
    std::vector<std::vector<int>> C = strassen_mm(A, B);
    // strassen_mm(A, B);
    std::cout << C[0][0] << " " <<C[0][1]<<"\n"; 
    std::cout << C[1][0] << " " <<C[1][1]<<"\n"; 
    return 0;
}