# WoodenCubeSolver
This code gives a solution to any wooden cube puzzle. 
At the end you have a graphic interface helping you to reproduce the solution on your wooden cube puzzle.  

A piece is a set of elementary cube with coordinates (x, y, z): p = [x0, y0, z0, x1, y1, z1, ...].  
In the pieces.txt input file, you just have to enter a piece by row

when it's done:  

#### COMPILE COMMAND LINE:  
gcc file_handler.c piece.c cube.c solver.c main.c -o sol
EXECUTION : ./sol

#### SOLUTION:   
python cube_visu.py: shows you step by step how to reproduce the solution (close the matplotlib figure at each step).  
(In my piece.txt case, I have one element missing from one piece so it is normal to not see the cube fully full).
