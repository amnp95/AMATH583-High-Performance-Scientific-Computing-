#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

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



int main() {
    std::cout<< "================================================\n";
    std::cout << "performance for gemm for type float:\n";
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

    double flops[511];
    for (int n = 2; n <=512 ; n++)
    {
        int m = n;
        int p = n;
            
        std::vector<float> A(n*n);
        std::vector<float> B(n*n);
        std::vector<float> C(n*n);

        float a = 2.0;
        float b  = 3.0;


        for (int i = 0; i < n*n; i++) {
            C[i] = dis(gen);
            B[i] = dis(gen);
            A[i] = dis(gen);
        }
   
        auto total_duration = std::chrono::nanoseconds(0);
        for (int j = 0; j < ntrials; j++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            gemm_jki(a , A, B , b , C, m, p, n);
            auto end = std::chrono::high_resolution_clock::now();
            // Calculate the duration in microseconds
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            total_duration += duration;
        }
        auto average_duration = total_duration / ntrials;
        double operations = 2*n*n*(n+1);
        flops[n-2] = operations/average_duration.count();
        std::cout << "FLOPS for n="<<n<<" :"<< flops[n-2]*1e9 << std::endl;
        

        std::ofstream myfile ("jki_float_.txt");
        if (myfile.is_open())
        {
            for(int count = 0; count < 511; count ++){
                myfile << flops[count] << "\n" ;
            }
            myfile.close();
        }
        else std::cout << "Unable to open file";

    }

   
 

  

    return 0;
}
