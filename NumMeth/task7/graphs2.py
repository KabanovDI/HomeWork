import matplotlib.pyplot as plt
import numpy as np

# 1. Read data skip header: skiprows=1)
# results.txt: x, exact, numerical
try:
    res_data = np.loadtxt('results.txt', delimiter=',', skiprows=1)
    x = res_data[:, 0]
    u_ex = res_data[:, 1]
    u_num = res_data[:, 2]

    # 2. Read data
    # convergence.txt: h, error
    conv_data = np.loadtxt('convergence.txt', delimiter=',', skiprows=1)
    h_vals = conv_data[:, 0]
    err_vals = conv_data[:, 1]
except OSError:
    print("Error: No data!")
    exit()

plt.figure(figsize=(12, 5))

# Left graph: solutions
plt.subplot(1, 2, 1)
plt.plot(x, u_ex, 'b-', label='Exact', linewidth=2)
plt.plot(x, u_num, 'r--', label='Sweep', linewidth=1.5)
plt.title("Comparison")
plt.xlabel("x")
plt.ylabel("u(x)")
plt.legend()
plt.grid(True, alpha=0.3)

# Right graph: convergence
plt.subplot(1, 2, 2)
plt.loglog(h_vals, err_vals, 'o-', label='Practical error', markersize=8)

# Build O(h^2) line
# C = error[0] / h[0]^2
h_ref = np.linspace(min(h_vals), max(h_vals), 100)
err_ref = h_ref**2 * (err_vals[0] / h_vals[0]**2)
plt.loglog(h_ref, err_ref, 'k--', alpha=0.6, label='$O(h^2)$')

plt.title("Convergence order(Log-Log)")
plt.xlabel("Step of grid h")
plt.ylabel("Max Error")
plt.legend()
plt.grid(True, which="both", linestyle='--', alpha=0.5)

plt.tight_layout()
plt.show()