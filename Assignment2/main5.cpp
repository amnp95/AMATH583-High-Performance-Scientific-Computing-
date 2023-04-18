#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "functionsTemplate.cpp"


int main () {
    // ================================================================================
    // axpy performaence 
    // ================================================================================
    {
        std::cout<< "================================================\n";
        std::cout << "performance for axpy for type float:\n";
        std::cout<< "================================================\n";

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
            std::vector<float> a(n); // Create a vector with n elements
            std::vector<float> b(n); // Create b vector with n elements
            float alpha = 2.0;
            for (int ii = 0; ii < n; ii++) {
                a[ii] = dis(gen);
                b[ii] = dis(gen);
            }
            
            auto total_duration = std::chrono::nanoseconds(0);
            for (int j = 0; j < ntrials; j++)
            {
                auto start = std::chrono::high_resolution_clock::now();
                axpy(alpha , a , b);
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

        std::ofstream myfile ("performance_axpy.txt");
        if (myfile.is_open())
        {
            for(int count = 0; count < 512; count ++){
                myfile << flops[count] << "\n" ;
            }
            myfile.close();
        }
        else std::cout << "Unable to open file";
    }
    

    // ================================================================================
    // gemv performaence 
    // ================================================================================
    {
        std::cout<< "================================================\n";
        std::cout << "performance for gemv for type float:\n";
        std::cout<< "================================================\n";


        int ntrials = 20; 
        int n = 1;
        int m = 1;
        double lower_bound = 1.0;   // Lower bound of random double numbers
        double upper_bound = 10.0;   // Upper bound of random double numbers
        std::random_device rd;      // Seed for random number generator
        std::mt19937 gen(rd());     // Mersenne Twister random number engine
        std::uniform_real_distribution<float> dis(lower_bound, upper_bound); // Uniform distribution for double numbers


        // Correctness cheking
        {
            std::cout << "correctness cheking should be : 28, 64, 100\n";
            std::vector<std::vector<float>> myvec = {{1.0, 2.0, 3.0},
                                                    {4.0, 5.0, 6.0}};
            std::vector<float> x = {1.0, 2.0, 3.0};
            std::vector<float> y = {1.0, 2.0};
            float a = 2.0;
            float b = 3.0;

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
            
            std::vector<float> a(n); // Create a vector with n elements
            std::vector<float> b(m); // Create b vector with m elements
            std::vector<std::vector<float>> A(m, std::vector<float>(n));
            float alpha = 2.0;
            float beta  = 3.0;


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


        std::ofstream myfile ("performance_gemv.txt");
        if (myfile.is_open())
        {
            for(int count = 0; count < 512; count ++){
                myfile << flops[count] << "\n" ;
            }
            myfile.close();
        }
        else std::cout << "Unable to open file";
    }
    
    
    
    // ================================================================================
    // gemm performaence 
    // ================================================================================
    {
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
        std::uniform_real_distribution<double> dis(lower_bound, upper_bound); // Uniform distribution for double numbers


        // Correctness cheking
        {
            std::cout << "correctness cheking should be : 28, 64, 100\n";
            // Define input matrices A and B
            std::vector<std::vector<float>> A{{1., 2., 3.}, {4., 5., 6.}};
            std::vector<std::vector<float>> B{{7., 8.}, {9., 10.}, {11., 12.}};

            // Define output matrix C
            std::vector<std::vector<float>> C{{13., 14.}, {15., 16.}};

            // Define scalar factors a and b
            float a = 2.0;
            float b = 3.0;

            // Compute expected result
            std::vector<std::vector<float>> expected{{155., 170.}, {323., 356.}};

            // Call dgemm
            gemm(a, A, B, b, C);
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
            
            std::vector<std::vector<float>> A(m, std::vector<float>(p));
            std::vector<std::vector<float>> B(p, std::vector<float>(n));
            std::vector<std::vector<float>> C(m, std::vector<float>(n));
            float alpha = 2.0;
            float beta  = 3.0;


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
                gemm (alpha , A, B , beta , C);
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


        std::ofstream myfile ("performance_gemm.txt");
        if (myfile.is_open())
        {
            for(int count = 0; count < 512; count ++){
                myfile << flops[count] << "\n" ;
            }
            myfile.close();
        }
        else std::cout << "Unable to open file";

    }

    return 0;
}