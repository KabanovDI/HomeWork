
import matplotlib.pyplot as plt
import numpy as np


DATA_DIR = "data"
OUTPUT_DIR = "graphs"


A_values = [1, 10, 100]
schemes = range(1, 6)

fig, axes = plt.subplots(3, 6, figsize=(20, 12))
fig.suptitle('Dependence of ln(1/error) on ln(1/h)', fontsize=16)

for A in A_values:
    fig2, axes2 = plt.subplots(2, 3, figsize=(15, 10))
    axes2 = axes2.flatten()
    fig2.suptitle(f'All schemes for A={A}', fontsize=14)

    for scheme_num in schemes:
        filename = f'{DATA_DIR}/scheme_{scheme_num}_A_{A}.txt'
        ax = axes2[scheme_num-1]

        try:
            data = np.loadtxt(filename)
            if data.size > 0:
                x = data[:, 0]
                y = data[:, 1]
                ax.plot(x, y, 'o-', linewidth=2, markersize=4)
                ax.set_title(f'Scheme {scheme_num}')
                ax.grid(True, alpha=0.3)
        except:
            pass

    plt.tight_layout()
    separate_png = f'{OUTPUT_DIR}/schemes_A_{A}.png'
    plt.savefig(separate_png, dpi=300, bbox_inches='tight')
    print(f'Separate graph saved to {separate_png}')
    plt.close(fig2)
        
