#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "dgemv.cpp"


int main () {

    int ntrials = 20; 
    int n = 1;
    int m = 1;
    double lower_bound = 1.0;   // Lower bound of random double numbers
    double upper_bound = 10.0;   // Upper bound of random double numbers
    std::random_device rd;      // Seed for random number generator
    std::mt19937 gen(rd());     // Mersenne Twister random number engine
    std::uniform_real_distribution<double> dis(lower_bound, upper_bound); // Uniform distribution for double numbers


    // Correctness cheking
    {
        std::cout << "correctness cheking should be : 28, 64, 100\n";
        std::vector<std::vector<double>> myvec = {{1.0, 2.0, 3.0},
                                                  {4.0, 5.0, 6.0}};
        std::vector<double> x = {1.0, 2.0, 3.0};
        std::vector<double> y = {1.0, 2.0};
        double a = 2.0;
        double b = 3.0;

        dgemv(a, myvec, x, b, y);
        // Print the result
        for (int i = 0; i < y.size(); i++) {
            std::cout << y[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "====================\n";
    }


    double flops[512];
    for (int i = 1; i <=512 ; i++)
    {
        n = i*2;
        m = n;
        
        std::vector<double> a(n); // Create a vector with n elements
        std::vector<double> b(m); // Create b vector with m elements
        std::vector<std::vector<double>> A(m, std::vector<double>(n));
        double alpha = 2.0;
        double beta  = 3.0;


        for (int ii = 0; ii < n; ii++) {
            a[ii] = dis(gen);
        }
        for (int ii = 0; ii < m; ii++) {
            b[ii] = dis(gen);
        }
        for (int ii = 0; ii < m; ii++) {
            for (int jj = 0; jj < n; jj++) {
                A[ii][jj] = dis(gen);
            }
        }
         
        auto total_duration = std::chrono::nanoseconds(0);
        for (int j = 0; j < ntrials; j++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            dgemv (alpha , A, a , beta , b);
            auto end = std::chrono::high_resolution_clock::now();
            // Calculate the duration in microseconds
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            total_duration += duration;
            // Print the time taken
            // std::cout << "Time taken: " << duration << " microseconds" << std::endl;
        }
        auto average_duration = total_duration / ntrials;
        // Print the average time taken
        double operations = 2*m*(n+1);
        flops[i-1] = operations/average_duration.count();
        std::cout << "FLOPS for n="<<n<<" :"<< flops[i-1]*1e9 << std::endl;


    }


    std::ofstream myfile ("example3.txt");
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