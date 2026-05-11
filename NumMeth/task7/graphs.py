import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 1. Read data
res = pd.read_csv('results.txt')

plt.figure(figsize=(12, 5))

# Solution`s graphs
plt.subplot(1, 2, 1)
plt.plot(res['x'], res['exact'], 'b-', label='Exact', linewidth=2)
plt.plot(res['x'], res['numerical'], 'r--', label='Sweep')
plt.title("Compare exact and numerical solutions")
plt.xlabel("x")
plt.ylabel("u(x)")
plt.legend()
plt.grid(True)

# 2. Read data
conv = pd.read_csv('convergence.txt')

plt.subplot(1, 2, 2)
plt.loglog(conv['h'], conv['error'], 'o-', label='Fact error')
# Add O(h^2) line
h_ref = conv['h'].values
err_ref = h_ref**2 * (conv['error'].values[0] / h_ref[0]**2)
plt.loglog(h_ref, err_ref, 'k--', alpha=0.5, label='$O(h^2)$')

plt.title("Convergence order (Log-Log)")
plt.xlabel("Step of grid h")
plt.ylabel("L_inf error")
plt.legend()
plt.grid(True, which="both")

plt.tight_layout()
plt.show()
