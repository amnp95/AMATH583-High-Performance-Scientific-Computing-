#%%
import numpy as np
import matplotlib.pyplot as plt


#%%
data = np.loadtxt("example1.txt")
n = np.array(list(range(1,513)),dtype=int)*2
plt.plot(n,data*1000000000)
plt.xlabel("n")
plt.ylabel("FLOPs")
plt.show()

# %%
data = np.loadtxt("example3.txt")
n = np.array(list(range(1,513)),dtype=int)*2
plt.plot(n,data*1000000000)
plt.xlabel("n")
plt.ylabel("FLOPs")
plt.show()
# %%
data = np.loadtxt("example4.txt")
n = np.array(list(range(1,513)),dtype=int)*2
plt.plot(n,data*1000000000)
plt.xlabel("n")
plt.ylabel("FLOPs")
plt.show()
# %%
data = np.loadtxt("performance_axpy.txt")
n = np.array(list(range(1,513)),dtype=int)*2
plt.plot(n,data*1000000000)
plt.xlabel("n")
plt.ylabel("FLOPs")
plt.show()
# %%
data = np.loadtxt("performance_gemv.txt")
n = np.array(list(range(1,513)),dtype=int)*2
plt.plot(n,data*1000000000)
plt.xlabel("n")
plt.ylabel("FLOPs")
plt.show()
# %%
data = np.loadtxt("performance_gemm.txt")
n = np.array(list(range(1,513)),dtype=int)*2
plt.plot(n,data*1000000000)
plt.xlabel("n")
plt.ylabel("FLOPs")
plt.show()