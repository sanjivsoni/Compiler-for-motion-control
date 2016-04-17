//
//  maze.cpp
//  path_algorithm
//
//  Created by Sanjiv Soni on 15/04/16.
//  Copyright © 2016 sunjiv. All rights reserved.
//

#include "maze.hpp"
#include<queue>
#include<iostream>
#include<vector>

using namespace std;

struct Node
{
    // obstacle present or absent
    bool clear;
    // Visited or univisted
    bool status;
    // Parent node
    int origin;
};

class Maze
{
private:
    Node *map;
    // Dimension of matrix
    int rows, columns;
    // Starting Coordinates
    int startX, startY;
    // Ending Coordinates
    int endX, endY;
    // Total nodes in graph
    int nodeCount;
    
public:
    
    // Constructor
    Maze(int rows, int columns)
    {
        nodeCount = rows * columns;
        
        map = new Node[nodeCount];
        
        for(int i = 0; i < nodeCount ; i++)
        {
            map[i].clear = true;
            map[i].status = false;
            map[i].origin = -1;
        }
        
        this->rows = rows;
        this->columns = columns;
        
        // Default Start and End
        this->startX = 0;
        this->startY = 0;
        this->endX = rows - 1;
        this->endY = columns - 1;
    }
    
    void setStartPoint(int x, int y)
    {
        this -> startX = x;
        this -> startY = y;
    }
    
    // Node where robot ends
    void setEndPoint(int x, int y)
    {
        this -> endX = x;
        this -> endY = y;
    }
    
    // set obstacle at node
    bool setObstacle(int node)
    {
        // boundary condition
        if(node < (nodeCount - 1))
        {
            // set obstacle
            map[node].clear = false;
        }
        else
        {
            return false;
        }
        return true;
    }
    
    // Define obstacles based on list of nodes
    bool setObstaclesFromList(int *nodes, int count)
    {
        if(count < nodeCount)
        {
            for(int i = 0 ; i < count ; i++)
            {
                setObstacle(nodes[i]);
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    
    bool setObstacleFromVector(vector<int> vectorOfX, vector<int> vectorOfY)
    {
        
        if(vectorOfX.size() < nodeCount && vectorOfY.size() < nodeCount )
        {
            if(vectorOfY.size() == vectorOfX.size())
            {
                for(int i = 0 ; i < vectorOfY.size() ; i++)
                {
                    setObstacle(getNodeNumber(vectorOfX[i],vectorOfY[i]));
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    
    
    int getNodeNumber(int i, int j)
    {
        return (i * rows + j);
    }
    
    // Convert nodes coordinates to
    void getMatrixIndex(int node, int &i, int &j)
    {
        i = node / columns;
        j = node - i * columns;
    }
    
    int getNodeRowIndex(int node)
    {
        return node / columns;
    }
    
    int getNodeColumnIndex(int node)
    {
        return node - node / columns * columns;
    }
    
    // Print maze to console
    // or file (maze too large)
    // girls like it too large ;)
    void printMaze(bool destination)
    {
        if(destination == true)
        {
            printf("\n");
            for(int i = 0 ; i < nodeCount ; i++)
            {
                if(i%columns == 0)
                {
                    printf("\n");
                }
                printf("%d ",map[i].clear);
            }
            printf("\n");
            
        }
    }
    
    // check for valid step from current to next node
    bool checkValidStep(int currentNode, int nextNode)
    {
        // Extreme bounds for both the nodes
        if(nextNode >= 0 && nextNode < nodeCount && currentNode >= 0 && nextNode < nodeCount)
        {
            // next node should be in Same row or same column
            if(getNodeRowIndex(currentNode) == getNodeRowIndex(nextNode) || getNodeColumnIndex(currentNode) == getNodeColumnIndex(nextNode))
            {
                // Block is clear and unvisited
                if(map[nextNode].clear == true && map[nextNode].status == false)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    
    // Check for valid and clear node
    bool checkValidNode(int node)
    {
        if(node >= 0 && node < nodeCount && map[node].clear == true)
        {
            return true;
        }
        else
        {
            return false;
        }
        return true;
    }

    // Perform BFS starting from source to destination.
    bool traverseBreadthFirst(int node)
    {
        int top,bottom,left,right,destination;
        bool pathFoundFlag = false;
        queue<int> nodeQueue;
        
        if(checkValidNode(node))
        {
                nodeQueue.push(node);
                map[node].status = true;
                map[node].origin = -1;
        }
        else
        {
            printf("Map Error : Invalid start node ");
            return false;
        }
        
        
        destination = getNodeNumber(endX, endY);
        
        if(!checkValidNode(destination))
        {
            printf("Map Error : Invalid destination node ");
            return false;
        }
        
        // BFS
        while(!nodeQueue.empty())
        {
            node = nodeQueue.front();
            nodeQueue.pop();
            
            if(node == destination)
            {
                printf("\nDestination to Source %d ",node);
                pathFoundFlag = true;
                backTrackPath(destination);
                break;
            }
            
            //printf("OUT %d\n",node);
            
            // Check for top, bottom, left, and right node
            if(checkValidStep(node,node - columns))
            {
                top = node - columns;
                map[top].status = true;
                map[top].origin = node;
                nodeQueue.push(top);
                //printf("IN  %d T %d\n",node,top);
                
            }
            if(checkValidStep(node, node - 1))
            {
                left = node - 1;
                map[left].status = true;
                map[left].origin = node;
                nodeQueue.push(left);
                //printf("IN  %d L %d\n",node,left);
            }
            if(checkValidStep(node, node + columns))
            {
                bottom = node + rows;
                map[bottom].status = true;
                map[bottom].origin = node;
                nodeQueue.push(bottom);
                //printf("IN  %d B %d\n",node,bottom);
            }
            
            if(checkValidStep(node, node + 1))
            {
                right = node + 1;
                map[right].status = true;
                map[right].origin = node;
                nodeQueue.push(right);
                //printf("IN  %d R %d\n",node,right);
            }
        }
        
        if(pathFoundFlag == false)
        {
            printf("\nDestination not reachable\n");
        }
        return true;
    }
    
    // Backtrack back to origin starting from destination node
    // Generates path.
    void backTrackPath(int destination)
    {
        int pre = 0;
        while(pre != -1)
        {
            pre = map[destination].origin;
            printf("%d ",pre);
            destination = pre;
        }
    }
};