# Compiler-for-motion-control
Compiler for motion control of mobile robots

This is a small-scale compiler for a simple differential drive robot.
The input is a config file with format like this:
rows/columns
columns/rows
Coordinates of start/end
Coordinates of end/start
Coordinates of the obstacles,if any

For eg.
rows = 4
columns = 10
start = (0,0)
end = (9,9)
obstacles = (3,7) (1,6)

The scope of the surrounding environment has been limited to a 2D maze with few obstacles on it.

Once the input config file is parsed it generates a shortest path from source to destination.
Shortest Path generation is done using Breadth First Search.

To make input data more simpler, we also designed a frontend based on HTML/CSS/jQuery/JavaScript.


Usage:
1. Open the illustrator.html
2. Enter the size of the maze.
3. Click on any white tile to make it black or vice versa.  
4. Click on red tile/green tile and relocate it anywhere in the grid by clicking again on any white surface.
5. Once you are done just press the export button and it will download the cofig.in file which will act as an input to the parser.
6. In the terminal, change the directory to the project directory.
7. Enter the command "make motionController". This command will make the parser.
8. Next, run the motionController and provide the previously downloaded config.in as the input, "./motionController config.in".
9. The path will be generated,if exists and written to "finalPath.h"
10. This "finalPath.h", then can be uploaded into the robot's microcontroller to make it run on that path.

If you run into any problems/bugs, please feel free to contact the developers.
Thank You.
