//
//  main.cpp
//  path_algorithm
//
//  Created by Sanjiv Soni on 15/04/16.
//  Copyright © 2016 sunjiv. All rights reserved.
//

#include <iostream>
#include "maze.cpp"
#include<time.h>

using namespace std;
int main(int argc, const char * argv[]) {
    
    clock_t time;
    time = clock();
    
    int obstacles[] = {5, 15, 25, 35, 45, 55, 65, 75, 85 };
    
    Maze maze = Maze(10,10);
    maze.setObstacles(obstacles, 10);
    maze.setStart(0, 0);
    maze.setEnd(9, 9);
    //maze.printMaze(true);
    maze.traverseBreadthFirst(0);
    
    
    time = clock() - time;
    
    printf("\n%f\n",((float)time)/CLOCKS_PER_SEC);
    
    return 0;
}
