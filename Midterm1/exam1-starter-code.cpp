// exam 1
// write the methods for
// operator*
// operator+
// transpose
// infinityNorm

#include <vector>
#include <stdexcept>
#include <iostream>
#include <cmath>

template <typename T>
class Matrix
{
public:
    Matrix(int numRows, int numCols)
        : num_rows(numRows), num_cols(numCols), data(numRows * numCols) {}

    T &operator()(int i, int j)
    {
        return data[i * num_cols + j];
    }

    const T &operator()(int i, int j) const
    {
        return data[i * num_cols + j];
    }

    Matrix<T> operator*(const Matrix<T> &other) const
    {
        // write your code
    }

    Matrix<T> operator+(const Matrix<T> &other) const;

    Matrix<T> transpose() const
    {
        // write your code
    }

    int numRows() const
    {
        return num_rows;
    }

    int numCols() const
    {
        return num_cols;
    }

    T infinityNorm() const
    {
        T norm = 0;
        // write your code
        return norm;
    }

private:
    int num_rows;
    int num_cols;
    std::vector<T> data;
};

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
{
    Matrix<T> result(num_rows, num_cols);
    // write your code
    return result;
}

int main()
{
    Matrix<double> A(2, 3);
    A(0, 0) = 1.0;
    A(0, 1) = 2.0;
    A(0, 2) = 3.0;
    A(1, 0) = 4.0;
    A(1, 1) = 5.0;
    A(1, 2) = 6.0;

    Matrix<double> B(3, 2);
    B(0, 0) = 7.0;
    B(0, 1) = 8.0;
    B(1, 0) = 9.0;
    B(1, 1) = 10.0;
    B(2, 0) = 11.0;
    B(2, 1) = 12.0;

    Matrix<double> C = A * B;

    std::cout << "Matrix product:\n";
    for (int i = 0; i < C.numRows(); i++)
    {
        for (int j = 0; j < C.numCols(); j++)
        {
            std::cout << C(i, j) << " ";
        }
        std::cout << "\n";
    }

    Matrix<double> CT = C.transpose();

    std::cout << "\nMatrix transpose:\n";
    for (int i = 0; i < CT.numRows(); i++)
    {
        for (int j = 0; j < CT.numCols(); j++)
        {
            std::cout << CT(i, j) << " ";
        }
        std::cout << "\n";
    }

    Matrix<double> D = C + CT;
    std::cout << std::endl
              << "Matrix sum:\n";
    for (int i = 0; i < D.numRows(); i++)
    {
        for (int j = 0; j < D.numCols(); j++)
        {
            std::cout << D(i, j) << " ";
        }
        std::cout << "\n";
    }

    double mat_norm = A.infinityNorm();

    std::cout << "\nMatrix infinity norm: " << mat_norm << "\n";

    return 0;
}
