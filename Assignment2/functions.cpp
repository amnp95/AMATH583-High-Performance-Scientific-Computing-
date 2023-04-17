
#include <iostream>
#include <vector>

void daxpy(double a , const std::vector<double> &x , std::vector<double> &y ) {
    if (x.size() == y.size())
    {
        for (int i = 0; i < x.size(); i++)
        {
            y[i] = a*x[i] + y[i];
        }
        return;
        
    } else {
        std::cout << "Error : Size of input array must be equal";
        return; 
    }
}
