import numpy as np
import matplotlib.pyplot as plt

# Read data from files
def read_data():
    # Read original points
    x_orig, y_orig = [], []
    with open('in.txt', 'r') as f:
        f.readline()
        for line in f:
            if line.strip():
                x, y = map(float, line.split())
                x_orig.append(x)
                y_orig.append(y)
    
    # Read evaluation points
    x_eval, p_vals, l_vals, err_vals = [], [], [], []
    with open('out.txt', 'r') as f:
        f.readline()
        for line in f:
            if line.strip():
                parts = line.split()
                x_eval.append(float(parts[0]))
                p_vals.append(float(parts[1]))
                l_vals.append(float(parts[2]))
                err_vals.append(float(parts[3]))
    
    return np.array(x_orig), np.array(y_orig), np.array(x_eval), np.array(p_vals), np.array(l_vals), np.array(err_vals)

# Load data
x_orig, y_orig, x_eval, p_vals, l_vals, err_vals = read_data()

# Create continuous x for true function
#x_cont = np.linspace(min(x_orig), max(x_orig), 1000)
#y_cont = np.sin(x_cont)  # Change to your function

# Create plot
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

# Top plot: Interpolation
#ax1.plot(x_cont, y_cont, 'k-', label='True function', linewidth=2, alpha=0.7)
ax1.plot(x_orig, y_orig, 'ro', label='Original points', markersize=8)
ax1.plot(x_eval, p_vals, 'b--', label='Vandermonde', linewidth=2, marker='s', markevery=5)
ax1.plot(x_eval, l_vals, 'g:', label='Lagrange', linewidth=2, marker='^', markevery=5)
ax1.set_ylabel('f(x)')
ax1.set_title('Interpolation Comparison')
ax1.legend()
ax1.grid(True, alpha=0.3)

# Bottom plot: Error
ax2.plot(x_eval, err_vals, 'r-', linewidth=2)
ax2.axhline(y=0, color='k', linestyle='-', linewidth=0.5)
ax2.set_xlabel('x')
ax2.set_ylabel('Error')
ax2.set_title('Interpolation Error')
ax2.grid(True, alpha=0.3)

plt.tight_layout()
plt.show()

# Print statistics
for x in x_orig:
    print(x, " ")
print(f"Max error: {np.max(np.abs(err_vals)):.3e}")
print(f"Mean error: {np.mean(np.abs(err_vals)):.3e}")
