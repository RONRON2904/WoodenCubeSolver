![Image description](wooden_cube.JPG)

# WoodenCubeSolver
This code gives a solution to any wooden cube puzzle. 
At the end a graphic interface helps to reproduce the solution on the true wooden cube puzzle.  

A piece is a set of elementary cube with coordinates (x, y, z): p = [x0, y0, z0, x1, y1, z1, ...].  
In the pieces.txt input file, just have to enter a piece by row
(pieces.txt can serve as an example)

when it's done:  

#### COMPILE COMMAND LINE:  
In the src/ directory:
gcc file_handler.c piece.c cube.c solver.c main.c -o sol

#### EXECUTION : 
In the src/ directory:
./sol

#### SOLUTION:   
pip install -r requirements.txt.   
In the src/ directory:  
python cube_visu.py: shows step by step how to reproduce the solution (by closing the matplotlib figure at each step).  

outputs_img shows the step by step solution given by the python script

#### NOTES: 
This code will work on 99%+ any real wooden cube we can find.
BUT:
* This code is actually limited by the number of combinations by unsigned long long int limit: 18,446,744,073,709,551,615
* In case of a wooden cube with lot more pieces (~=lot more combinations) it will end up with errors.
