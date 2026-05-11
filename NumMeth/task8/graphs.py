import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

# Load data using numpy (fast and basic)
data = np.loadtxt('results.txt')
t_vals = data[:, 0]
x_vals = data[:, 1]
y_calc = data[:, 2]
u_exact = data[:, 3]

# Reshape for 3D plotting
# Assuming N and M are the same as in C++
N_pts = len(np.unique(x_vals))
M_pts = len(np.unique(t_vals))

T = t_vals.reshape(M_pts, N_pts)
X = x_vals.reshape(M_pts, N_pts)
Z = y_calc.reshape(M_pts, N_pts)
Z_err = np.abs(y_calc - u_exact).reshape(M_pts, N_pts)

# Plotting 3D Surface
fig = plt.figure(figsize=(21, 6))

ax1 = fig.add_subplot(131, projection='3d')
surf = ax1.plot_surface(X, T, Z, cmap='viridis', edgecolor='none')
ax1.set_title('Numerical Solution u(x, t)')
ax1.set_xlabel('Space x')
ax1.set_ylabel('Time t')
fig.colorbar(surf, ax=ax1, shrink=0.5)

# Plotting Space Convergence O(h^2)
ax2 = fig.add_subplot(132)
data_h = np.loadtxt('conv_h.txt')
h_steps, errors_h = data_h[:, 0], data_h[:, 1]
    
ax2.loglog(h_steps, errors_h, 'ro-', label='Numerical Error')
# Reference line O(h^2)
ax2.loglog(h_steps, errors_h[0]*(h_steps/h_steps[0])**2, 'k--', label='Slope 2 (O(h²))')
    
ax2.set_title('Space Convergence')
ax2.set_xlabel('Step size h')
ax2.set_ylabel('Max Absolute Error')
ax2.grid(True, which="both", ls="-", alpha=0.5)
ax2.legend()

# Plotting Time Convergence O(tau^1)
ax3 = fig.add_subplot(133)
data_tau = np.loadtxt('conv_tau.txt')
tau_steps, errors_tau = data_tau[:, 0], data_tau[:, 1]
    
ax3.loglog(tau_steps, errors_tau, 'bo-', label='Numerical Error')
# Reference line O(tau^1)
ax3.loglog(tau_steps, errors_tau[0]*(tau_steps/tau_steps[0])**1, 'k--', label='Slope 1 (O(τ))')
    
ax3.set_title('Time Convergence')
ax3.set_xlabel('Step size τ')
ax3.set_ylabel('Max Absolute Error')
ax3.grid(True, which="both", ls="-", alpha=0.5)
ax3.legend()

plt.tight_layout()
plt.show()
