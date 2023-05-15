#%%
import matplotlib.pyplot as plt 
import numpy as np 
#%%
data = np.loadtxt("runtime.txt",delimiter=",")
plt.plot(data[:,0], data[:,-1]/data[:,1],label="write")
plt.plot(data[:,0], data[:,-1]/data[:,2],label="read")
plt.grid(linestyle="--")
plt.legend()
plt.xlabel("Dimension")
plt.ylabel("bandwidth (bytes/second)")
plt.savefig("problem1.png")

# %%
data = np.loadtxt("p2_1.txt",delimiter=",")
plt.plot(data[:,0], data[:,-1]/1e9,label="write")
plt.grid(linestyle="--")
# plt.legend()
plt.xlabel("Threads")
plt.ylabel("Run Time (seconds)")
plt.savefig("problem2_1.png")
# %%
data = np.loadtxt("p2_2.txt",delimiter=",")
plt.loglog(data[:,0], data[:,-1]*100,"o-",label="write")
plt.grid(linestyle="--")
# plt.legend()
plt.xlabel("number of points")
plt.ylabel("error (percent)")
plt.savefig("problem2_2.png")
# %%
