#include <iostream>
#include <vector>


void dgemv (double a , const std::vector<std::vector<double>> &A,const std::vector<double> &x , double b , std::vector<double> &y) {

    double res=0;
    if (A[0].size() == x.size() ) {

        if (A.size() == y.size())
        {
            for (int i = 0; i < A.size(); i++)
            {
                res = 0; 
                for (int j = 0; j< x.size(); j++) {
                    res = res + A[i][j]*x[j];
                }
                y[i] = res*a + b*y[i];

            }

        } else
        {
            std::cout << "A matrix and Y vector are not comaptible.\n";
            return;
        }

    } else
    {
        std::cout << "A matrix and X vector are not compatible\n";
        return;
    }
    


}