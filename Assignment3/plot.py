#%%
import numpy as np
import matplotlib.pyplot as plt

fig,axes = plt.subplots(1,3,figsize=(12,4),sharey=True)
data = np.loadtxt("kij_float_unoptimize.txt")
axes[0].plot(np.arange(0,511,1),data*1000)

data = np.loadtxt("kij_float_03optimized.txt")
axes[1].plot(np.arange(0,511,1),data*1000)

data = np.loadtxt("kij_float_fastmath.txt")
axes[2].plot(np.arange(0,511,1),data*1000)
axes[0].set_ylabel("MFLOPS")
axes[0].set_xlabel("n")
axes[1].set_xlabel("n")
axes[2].set_xlabel("n")
fig.suptitle("GEMM_KIJ (FLOAT)")
axes[0].set_title("O0")
axes[1].set_title("O3")
axes[2].set_title("fast-math")
fig.tight_layout()
fig.savefig("kij_float_2.png")








# %%
fig,axes = plt.subplots(1,1)
data = np.loadtxt("kij_float_unoptimize.txt")
axes.plot(np.arange(0,511,1),data*1000,label="O0")

data = np.loadtxt("kij_float_03optimized.txt")
axes.plot(np.arange(0,511,1),data*1000,label="O3")

data = np.loadtxt("kij_float_fastmath.txt")
axes.plot(np.arange(0,511,1),data*1000,label="fast-math")
axes.set_ylabel("MFLOPS")
axes.set_xlabel("n")
axes.legend()
fig.suptitle("GEMM_KIJ (FLOAT)")
fig.tight_layout()
fig.savefig("kij_float.png")

# %%
fig,axes = plt.subplots(1,1)
data = np.loadtxt("jki_float_unoptimize.txt")
axes.plot(np.arange(0,511,1),data*1000,label="-O0")

data = np.loadtxt("jki_float_03optimized.txt")
axes.plot(np.arange(0,511,1),data*1000,label="-O3")

data = np.loadtxt("jki_float_Ofast.txt")
axes.plot(np.arange(0,511,1),data*1000,label="-Ofast")
axes.set_ylabel("MFLOPS")
axes.set_xlabel("n")
axes.legend()
fig.suptitle("GEMM_jki (FLOAT)")
fig.tight_layout()
fig.savefig("jki_float.png")
# %%
