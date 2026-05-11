import matplotlib.pyplot as plt
import numpy as np


# Load data from files
data_1 = np.loadtxt('solution_1.txt')
data_2 = np.loadtxt('solution_2.txt')
data_3 = np.loadtxt('solution_3.txt')
data_4 = np.loadtxt('solution_4.txt')
data_5 = np.loadtxt('solution_5.txt')
data_exact = np.loadtxt('exact_solution.txt')

# Create figure
fig, axes = plt.subplots(1, 2, figsize=(12, 8))

# Plot exact solution
axes[0].plot(data_exact[:, 0], data_exact[:, 1], 'r-', linewidth=2, label='Exact Solution')
axes[0].set_xlabel('x')
axes[0].set_ylabel('y(x)')
axes[0].legend()
axes[0].grid(True, alpha=0.3)
'''
# Plot first solution
plt.plot(data_1[:, 0], data_1[:, 1], 'c-', markersize=6, 
         linewidth=1.5, label='Automatic Step (method 1)')

# Plot second solution
plt.plot(data_2[:, 0], data_2[:, 1], 'g-', markersize=6, 
         linewidth=1.5, label='Automatic Step (method 2)')

# Plot third solution
plt.plot(data_3[:, 0], data_3[:, 1], 'b-', markersize=6, 
         linewidth=1.5, label='Automatic Step (method 3)')

# Plot constant step solution
plt.plot(data_4[:, 0], data_4[:, 1], 'm-', markersize=6, 
         linewidth=1.5, label='Constant Step')
'''
axes[1].plot(data_5[:, 0], data_5[:, 1], 'k-', markersize=6, 
         linewidth=1.5, label='h/x')
axes[1].set_xlabel('x')
axes[1].set_ylabel('y(x)')
axes[1].legend()
axes[1].grid(True, alpha=0.3)

plt.suptitle('Variant 7: Comparison of Numerical Solutions')
plt.tight_layout()
plt.savefig('variant7_solution_comparison.png', dpi=150)
plt.show()