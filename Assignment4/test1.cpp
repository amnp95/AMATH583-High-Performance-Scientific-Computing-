#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>


void write(std::vector<double>& matrix, int m, int n) {
    std::ofstream outputFile("data.bin", std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.write(reinterpret_cast<char*>(matrix.data()), m*n* sizeof(double));
    } else {
        std::cout << "Failed to open the output file." << std::endl;
        return;
    }

    outputFile.close();
}

void read(std::vector<double>& matrix, int m, int n) {
    std::ifstream outputFile("data.bin", std::ios::binary);
    if (outputFile.is_open()) {
        outputFile.read(reinterpret_cast<char*>(matrix.data()), sizeof(double)*m*n);
    } else {
        std::cout << "Failed to open the output file." << std::endl;
        return;
    }

    outputFile.close();
}

int main() {
    std::ofstream file("runtime.txt");
    double write_time(10); 
    double read_time(10); 
    std::random_device rd;   // Obtain a random seed from the hardware
    std::mt19937 gen(rd());  // Initialize the random number generator
    std::uniform_real_distribution<double> dis(0.0, 1.0); // Define the range of random numbers
    file << "# n, write time, readtime, bytes\n";
    for (int i=5; i<=14; i++) {
        int m = std::pow(2,i) ;
        int n = m;

        std::vector<double> data(m*n);
        for (int i=0; i<m*n; i++) {
            data[i] = dis(gen);
        }
        std::vector<double> data_r(m*n);
        auto start = std::chrono::high_resolution_clock::now();
        write(data, m,n);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        read(data, m,n);
        end = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        
        file << n << "," << duration1 << "," << duration2 <<","<<sizeof(double)*m*n<<"\n";
    }
    file.close();
    return 0;

}