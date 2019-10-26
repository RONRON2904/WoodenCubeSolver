# WoodenCubeSolver
This code gives a solution to any wooden cube puzzle. 
At the end a graphic interface helps to reproduce the solution on the true wooden cube puzzle.  

A piece is a set of elementary cube with coordinates (x, y, z): p = [x0, y0, z0, x1, y1, z1, ...].  
In the pieces.txt input file, just have to enter a piece by row
(pieces.txt can serve as an example)

when it's done:  

#### COMPILE COMMAND LINE:  
gcc file_handler.c piece.c cube.c solver.c main.c -o sol
EXECUTION : ./sol

#### SOLUTION:   
python cube_visu.py: shows step by step how to reproduce the solution (by closing the matplotlib figure at each step).  
(In my piece.txt case, I have one element missing from one piece so it is normal to not see the cube fully fulled).  

outputs_img shows the step by step solution given by the python script
