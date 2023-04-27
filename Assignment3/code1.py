#%%
import numpy as np

def gemm_ijk(alpha, A, B, beta, C):
    assert A.shape[1] == B.shape[0]
    assert A.shape[0] == C.shape[0]
    assert B.shape[1] == C.shape[1]
    m, p = A.shape
    n = B.shape[1]
    for i in range(m):
        for j in range(n):
            sum_ = 0.0
            for k in range(p):
                sum_ += A[i, k] * B[k, j]
            C[i, j] = alpha * sum_ + beta * C[i, j]

def gemm_ikj(alpha, A, B, beta, C):
    assert A.shape[1] == B.shape[0]
    assert A.shape[0] == C.shape[0]
    assert B.shape[1] == C.shape[1]
    m, p = A.shape
    n = B.shape[1]
    for i in range(m):
        for k in range(p):
            temp = alpha * A[i, k]
            for j in range(n):
                if k==0 :
                    C[i, j] *= beta
                C[i, j] += temp * B[k, j]



def gemm_jki(alpha, A, B, beta, C):
    assert A.shape[1] == B.shape[0]
    assert A.shape[0] == C.shape[0]
    assert B.shape[1] == C.shape[1]
    m, p = A.shape
    n = B.shape[1]
    for j in range(n):
        for k in range(p):
            temp = alpha * B[k, j]
            for i in range(m):
                if k==0 :
                    C[i, j] *= beta
                C[i, j] += temp * A[i, k]

def gemm_kij(alpha, A, B, beta, C):
    assert A.shape[1] == B.shape[0]
    assert A.shape[0] == C.shape[0]
    assert B.shape[1] == C.shape[1]
    m, p = A.shape
    n = B.shape[1]
    for k in range(p):
        for i in range(m):
            temp = alpha * A[i, k]
            for j in range(n):
                if k==0 :
                    C[i, j] *= beta
                C[i, j] += temp * B[k, j]


def gemm_kji(alpha, A, B, beta, C):
    assert A.shape[1] == B.shape[0]
    assert A.shape[0] == C.shape[0]
    assert B.shape[1] == C.shape[1]
    m, p = A.shape
    n = B.shape[1]
    for k in range(p):
        for j in range(n):
            temp = alpha * B[k, j]
            for i in range(m):
                if k==0 :
                    C[i, j] *= beta
                C[i, j] += temp * A[i, k]

# Example usage
A = np.random.rand(2, 3)
B = np.random.rand(3, 4)
c = np.random.rand(2, 4)
alpha = 1.0
beta = 0.0
C_dgemm = alpha * np.dot(A, B) + beta * c

C = c.copy()
gemm_ijk(alpha, A, B, beta, C)
print("C (ijk):")
print(C)
print("Are the results equal?", np.allclose(C, C_dgemm))


C = c.copy()
gemm_ikj(alpha, A, B, beta, C)
print("C (ikj):")
print(C)
print("Are the results equal?", np.allclose(C, C_dgemm))


C = c.copy()
gemm_jki(alpha, A, B, beta, C)
print("C (jki):")
print(C)
print("Are the results equal?", np.allclose(C, C_dgemm))


C = c.copy()
gemm_kij(alpha, A, B, beta, C)
print("C (kij):")
print(C)
print("Are the results equal?", np.allclose(C, C_dgemm))


C = c.copy()
gemm_kji(alpha, A, B, beta, C)
print("C (kji):")
print(C)
print("Are the results equal?", np.allclose(C, C_dgemm))






m = 3
n = 4
p = 2
alpha = 0.0
beta = 2.0

A = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]]).T
B = np.array([[7.0, 8.0], [9.0, 10.0], [11.0, 12.0], [13.0, 14.0]]).T
C = np.array([[1,2,3,4],[4,5,6,7],[8,9,10,11]])
C_dgemm = alpha * np.dot(A, B) + beta * C
print("C_dgemm:")
print(C_dgemm)




# %%
