#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>


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
   
   // return naive multipication if n is not even
    if (n%2==1) {
        std::vector<std::vector<T>> C(n,std::vector<T>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                C[i][j] = 0.0;
                for (int k = 0; k < n; ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }


    // Divide the matrices into submatrices
    int k = n / 2;
    std::vector<std::vector<T>>  A11(k, std::vector<T>(k));
    std::vector<std::vector<T>>  A22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B11(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  A11pA22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B11pB22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  A21pA22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B12mB22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B21mB11(k, std::vector<T>(k));
    std::vector<std::vector<T>>  A11pA12(k, std::vector<T>(k));
    std::vector<std::vector<T>>  A21mA11(k, std::vector<T>(k));
    std::vector<std::vector<T>>  A12mA22(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B11pB12(k, std::vector<T>(k));
    std::vector<std::vector<T>>  B21pB22(k, std::vector<T>(k));

    // std::vector<std::vector<T>>  A12(k, std::vector<T>(k)); 
    // std::vector<std::vector<T>>  A21(k, std::vector<T>(k)); 
    // std::vector<std::vector<T>>  B12(k, std::vector<T>(k));
    // std::vector<std::vector<T>>  B21(k, std::vector<T>(k));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            // A12[i][j] = A[i][j + k];
            // A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            // B12[i][j] = B[i][j + k];
            // B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];

            A11pA22[i][j] = A[i][j]+A[i + k][j + k];
            B11pB22[i][j] = B[i][j]+B[i + k][j + k];
            A21pA22[i][j] = A[i + k][j]+A[i + k][j + k];
            B12mB22[i][j] = B[i][j + k] - B[i + k][j + k];
            B21mB11[i][j] = B[i + k][j]-B[i][j];
            A11pA12[i][j] = A[i][j] + A[i][j + k];
            A21mA11[i][j] = A[i + k][j] - A[i][j];
            A12mA22[i][j] = A[i][j + k] - A[i + k][j + k];
            B11pB12[i][j] = B[i][j] + B[i][j + k];
            B21pB22[i][j] = B[i + k][j]+ B[i + k][j + k];

        }
    }

    // Recursive calls to compute the submatrices of the product
    std::vector<std::vector<T>> &p1 = B11pB22; 
    std::vector<std::vector<T>> &p2 = B11    ; 
    std::vector<std::vector<T>> &p3 = B12mB22; 
    std::vector<std::vector<T>> &p4 = B21mB11; 
    std::vector<std::vector<T>> &p5 = B22    ; 
    std::vector<std::vector<T>> &p6 = B11pB12; 
    std::vector<std::vector<T>> &p7 = B21pB22; 
    


    p1 = strassen_mm(A11pA22, B11pB22);
    p2 = strassen_mm(A21pA22, B11    );
    p3 = strassen_mm(A11,     B12mB22);
    p4 = strassen_mm(A22,     B21mB11);
    p5 = strassen_mm(A11pA12, B22    );
    p6 = strassen_mm(A21mA11, B11pB12);
    p7 = strassen_mm(A12mA22, B21pB22);


    // Combine the submatrices to form the product matrix
    std::vector<std::vector<T>> C(n, std::vector<T>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
            C[i][j + k]     = p3[i][j] + p5[i][j];
            C[i + k][j]     = p2[i][j] + p4[i][j];
            C[i + k][j + k] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
        }
    }
    return C;
}




// template <typename T>
// std::vector<std::vector<T>> mult(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B ) 
// {
//     int n = A.size();
//     std::vector<std::vector<T>> C(n,std::vector<T>(n));
//         for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j) {
//                 C[i][j] = 0.0;
//                 for (int k = 0; k < n; ++k) {
//                     C[i][j] += A[i][k] * B[k][j];
//                 }
//             }
//         }
//         return C;
// }

int main() {

    std::cout<< "================================================\n";
    std::cout << "performance for stassen recursive for double:\n";
    std::cout<< "================================================\n";

    int ntrials = 5; 
    int n = 1;
    int m = 1;
    int p = 1;
    double lower_bound = 1.0;   // Lower bound of random double numbers
    double upper_bound = 10.0;   // Upper bound of random double numbers
    std::random_device rd;      // Seed for random number generator
    std::mt19937 gen(rd());     // Mersenne Twister random number engine
    std::uniform_real_distribution<double> dis(lower_bound, upper_bound); 
    int count = 0 ;
    double flops[256];
    for (int n = 2; n <=512 ; n+=2)
    {
        int m = n;
        int p = n;
            
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        std::vector<std::vector<double>> B(n, std::vector<double>(n));
        std::vector<std::vector<double>> C(n, std::vector<double>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)  {
                C[i][j] = dis(gen);
                B[i][j] = dis(gen);
                A[i][j] = dis(gen);
            }
        }
   
        auto total_duration = std::chrono::nanoseconds(0);
        for (int j = 0; j < ntrials; j++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            C = strassen_mm(A,B);
            auto end = std::chrono::high_resolution_clock::now();
            // Calculate the duration in microseconds
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            total_duration += duration;
        }
        auto average_duration = total_duration / ntrials;
        double operations = n*n*(2*n-1);
        flops[count] = operations/average_duration.count();
        std::cout << "FLOPS for n="<<n<<" :"<< flops[count]*1e9 << std::endl;
        count++;
    }
    
    std::ofstream myfile ("strassen.txt");
    if (myfile.is_open())
    {
        for(int i = 0; i < 256; i++){
            myfile << flops[i] << "\n" ;
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";
    
    return 0;
}