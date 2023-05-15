#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <cmath>
#include <chrono>
#include <fstream> 
#include <mpi.h>



void calc_len(double &sum, std::mutex &sum_mutex, double a, double h, int n, int nthreads, int index) {
    double s = 0;
    int start = (index == 0) ? 0:(n/nthreads)*index+1;
    int end = (index == nthreads-1) ? n : (n/nthreads)*(index+1);
    for(int j=start; j<end ; ++j) {
        double x = a + j*h;
        double t = 1/x + x/4;
        s += t;
    }
    sum_mutex.lock();
    sum += s;
    sum_mutex.unlock();
    // std::cout << "thread " << index << " from " << start << " " << end << "\n"; 
    
}


int main(int argc, char* argv[]) {
    MPI_Init()
    double a = 1;
    double b = 6; 
    int    n = 1e8;
    double sum = 0;
    double h = (b-a)/n;
    
    std::ofstream file("p2_1.txt");
    for (int nthreads =1; nthreads<=6; nthreads++) {
        sum = 0;
        auto start = std::chrono::high_resolution_clock::now();
        sum = length (a, b, n, nthreads);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        file<< nthreads <<"," <<sum << "," <<duration<<"\n";
    }
    file.close();


    double analytical_soulotion=std::log(6) + (35.0/8.0);
    file.open("p2_2.txt");
    std::cout << analytical_soulotion <<"\n";
    for (int n=10; n<=1e6; n*=10) {
        sum = 0;
        sum = length (a, b, n, 2);
        file<< n <<"," <<sum << "," <<std:: abs(analytical_soulotion - sum)<<","<<std:: abs(analytical_soulotion - sum)/analytical_soulotion<<"\n";        
    }
    file.close();
    return 0;
}