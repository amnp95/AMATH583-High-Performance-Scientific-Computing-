#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "daxpy.cpp"


int main () {

    int ntrials = 100; 
    int n = 1;
    double lower_bound = 0.0;   // Lower bound of random double numbers
    double upper_bound = 1.0;   // Upper bound of random double numbers
    std::random_device rd;      // Seed for random number generator
    std::mt19937 gen(rd());     // Mersenne Twister random number engine
    std::uniform_real_distribution<double> dis(lower_bound, upper_bound); // Uniform distribution for double numbers

    double flops[512];
    for (int i = 1; i <=512 ; i++)
    {
        n = i*2;
        std::vector<double> a(n); // Create a vector with n elements
        std::vector<double> b(n); // Create b vector with n elements
        double alpha = 2.0;
        for (int ii = 0; ii < n; ii++) {
            a[ii] = dis(gen);
            b[ii] = dis(gen);
        }
        
        auto total_duration = std::chrono::nanoseconds(0);
        for (int j = 0; j < ntrials; j++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            daxpy(alpha , a , b);
            auto end = std::chrono::high_resolution_clock::now();
                // Calculate the duration in microseconds
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            total_duration += duration;
            // Print the time taken
            // std::cout << "Time taken: " << duration << " microseconds" << std::endl;
        }
        auto average_duration = total_duration / ntrials;
        // Print the average time taken
        double operations = 2*n;
        flops[i-1] = operations/average_duration.count();
        std::cout << "Average time taken for n="<<n<<" :"<< flops[i-1]<< " nanoseconds" << std::endl;
    }

    std::ofstream myfile ("example1.txt");
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