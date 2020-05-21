import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import numpy as np
from mpl_toolkits.mplot3d import Axes3D  
import random


def get_piece_coords(solution_df, p_id):
    piece = solution_df[solution_df['p_id'] == p_id]
    return piece.x.values, piece.y.values, piece.z.values

def get_piece(coords):
    x, y, z = np.indices((SIZE, SIZE, SIZE))
    x_vals, y_vals, z_vals = coords[0], coords[1], coords[2]
    piece = (x == x_vals[0]) & (y == z_vals[0]) & (z == y_vals[0])
    for i in range(1, x_vals.shape[0]):
        piece += (x == x_vals[i]) & (y == z_vals[i]) & (z == y_vals[i])
    return piece

def plot_pieces(voxels):
    p_colors = [name.split('tab:')[1] for i, name in enumerate(list(mcolors.TABLEAU_COLORS))]
    colors = np.empty(voxels.shape, dtype=object)
    for p in range(len(pieces)):
        colors[pieces[p]] = p_colors[p]

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.voxels(voxels, facecolors=colors, edgecolor='k')

    plt.show()

if __name__ == '__main__':
    sol_df = pd.read_csv('../solution.txt', sep=' ')
    sol = sol_df[sol_df['p_id'] >= 0]
    
    SIZE = len(sol.x.unique())

    p_ids = sol.p_id.unique().tolist()
    pieces = [get_piece(get_piece_coords(sol, p_id)) for p_id in p_ids]

    voxels = pieces[0]

    for i in range(1, len(pieces)):
        voxels = voxels | pieces[i]
        plot_pieces(voxels)