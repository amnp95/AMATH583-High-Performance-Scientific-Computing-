#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "dgemm.cpp"


int main () {

    int ntrials = 5; 
    int n = 1;
    int m = 1;
    int p = 1;
    double lower_bound = 1.0;   // Lower bound of random double numbers
    double upper_bound = 10.0;   // Upper bound of random double numbers
    std::random_device rd;      // Seed for random number generator
    std::mt19937 gen(rd());     // Mersenne Twister random number engine
    std::uniform_real_distribution<double> dis(lower_bound, upper_bound); // Uniform distribution for double numbers


    // Correctness cheking
    {
        std::cout << "correctness cheking should be : 28, 64, 100\n";
        // Define input matrices A and B
        std::vector<std::vector<double>> A{{1., 2., 3.}, {4., 5., 6.}};
        std::vector<std::vector<double>> B{{7., 8.}, {9., 10.}, {11., 12.}};

        // Define output matrix C
        std::vector<std::vector<double>> C{{13., 14.}, {15., 16.}};

        // Define scalar factors a and b
        double a = 2.0;
        double b = 3.0;

        // Compute expected result
        std::vector<std::vector<double>> expected{{155., 170.}, {323., 356.}};

        // Call dgemm
        dgemm(a, A, B, b, C);
        std::cout << C[0][0] << " " << C[0][1]<< "\n";
        std::cout << C[1][0] << " " << C[1][1]<<"\n";
        std::cout << std::endl;
        std::cout << "====================\n";
    }


    double flops[512];
    for (int i = 1; i <=512 ; i++)
    {
        n = i*2;
        m = n;
        p = 10;
        
        std::vector<std::vector<double>> A(m, std::vector<double>(p));
        std::vector<std::vector<double>> B(p, std::vector<double>(n));
        std::vector<std::vector<double>> C(m, std::vector<double>(n));
        double alpha = 2.0;
        double beta  = 3.0;


        for (int ii = 0; ii < m; ii++) {
            for (int jj = 0; jj < n; jj++) {
                C[ii][jj] = dis(gen);
            }
        }
        for (int ii = 0; ii < p; ii++) {
            for (int jj = 0; jj < n; jj++) {
                B[ii][jj] = dis(gen);
            }
        }
        for (int ii = 0; ii < m; ii++) {
            for (int jj = 0; jj < p; jj++) {
                A[ii][jj] = dis(gen);
            }
        }
         
        auto total_duration = std::chrono::nanoseconds(0);
        for (int j = 0; j < ntrials; j++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            dgemm (alpha , A, B , beta , C);
            auto end = std::chrono::high_resolution_clock::now();
            // Calculate the duration in microseconds
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            total_duration += duration;
            // Print the time taken
            // std::cout << "Time taken: " << duration << " microseconds" << std::endl;
        }
        auto average_duration = total_duration / ntrials;
        // Print the average time taken
        double operations = 2*m*n*(p+1);
        flops[i-1] = operations/average_duration.count();
        std::cout << "FLOPS for n="<<n<<" :"<< flops[i-1]*1e9 << std::endl;
    }


    std::ofstream myfile ("example4.txt");
    if (myfile.is_open())
    {
        for(int count = 0; count < 512; count ++){
            myfile << flops[count] << "\n" ;
        }
        myfile.close();
    }
    else std::cout << "Unable to open file";



    return 0;
}