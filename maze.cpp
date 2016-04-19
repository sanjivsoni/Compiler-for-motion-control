//
//  maze.cpp
//  path_algorithm
//
//  Created by Sanjiv Soni on 15/04/16.
//  Copyright © 2016 sunjiv. All rights reserved.
//


#include<queue>
#include<stack>
#include<iostream>
#include<vector>
#include<fstream>

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

        if(x < rows && y< columns)
        {
            this -> startX = x;
            this -> startY = y;
        }
        else
        {
            printf("Semantic Error : Invalid Start Point\n");
            exit(0);
        }
        }

    // Node where robot ends
    void setEndPoint(int x, int y)
    {
        if(x < rows && y< columns)
        {
            this -> endX = x;
            this -> endY = y;
        }
        else
        {
            printf("Map Error : Invalid End Point\n");
            exit(0);
        }
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
            printf("Map Error : Obstacle out of bounds\n");
            exit(0);
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
        return (i * columns + j);
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
    bool traverseBreadthFirst()
    {
        int node,top,bottom,left,right,destination;
        bool pathFoundFlag = false;
        queue<int> nodeQueue;

        // Start from Start node
        node = getNodeNumber(startX, startY);
        destination = getNodeNumber(endX, endY);
        // Add start node to queue
        nodeQueue.push(node);
        map[node].status = true;
        map[node].origin = -1;

        // BFS
        while(!nodeQueue.empty())
        {
            node = nodeQueue.front();
            nodeQueue.pop();

            if(node == destination)
            {
                //printf("\nDestination to Source %d ",node);
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
                printf("IN  %d T %d\n",node,top);

            }
            if(checkValidStep(node, node - 1))
            {
                left = node - 1;
                map[left].status = true;
                map[left].origin = node;
                nodeQueue.push(left);
                printf("IN  %d L %d\n",node,left);
            }
            if(checkValidStep(node, node + columns))
            {
                bottom = node + columns;
                map[bottom].status = true;
                map[bottom].origin = node;
                nodeQueue.push(bottom);
                printf("IN  %d B %d\n",node,bottom);
            }

            if(checkValidStep(node, node + 1))
            {
                right = node + 1;
                map[right].status = true;
                map[right].origin = node;
                nodeQueue.push(right);
                printf("IN  %d R %d\n",node,right);
            }
        }

        if(pathFoundFlag == false)
        {
            printf("\nDestination is not reachable.\n");
            return false;
        }
        return true;
    }

    // Backtrack back to origin starting from destination node
    // Generates path.
    void backTrackPath(int destination)
    {
        bool stop = false;
        stack<int> path;
        
        path.push(destination);
        
        int previousStep = 0,nextStep = destination;
        while(stop == false)
        {
            previousStep = map[nextStep].origin;
            //cout<<previousStep<<" ";
            
            
            // Start node
            if(previousStep == -1)
            {
                stop = true;
                //path.push(nextStep);
                break;
            }
            
            path.push(previousStep);
            
            //printf("%d ",pre);
            nextStep = previousStep;
        }
        
        ofstream fout("finalPath.h");
        
        if(fout == NULL)
        {
            printf("Cannot write to File 'finalPath.h'");
            exit(0);
        }
        
        fout<< "char path[] = \"";
        
        int current = 0,next;
        int turn = 0, roboTurn = 0;
        current = path.top();
        path.pop();
        
        while(!path.empty())
        {
            next = path.top();
            path.pop();
            
            if(current == next - 1)
            {
                turn = 90;
            }
            if(current == next + 1)
            {
                turn = -90;
            }
            if(current == next + columns)
            {
                turn = 0;
            }
            if(current == next - columns)
            {
                turn = 180;
            }
            
            if(turn - roboTurn == 90 || turn - roboTurn == -270 )
            {
                fout<<"R";
                roboTurn = turn;
            }
            
            else if(turn - roboTurn == 0)
            {
                fout<<"S";
                roboTurn = turn;
            }
            else if(turn - roboTurn == 180 || turn - roboTurn == -180)
            {
                fout<<"U";
                roboTurn = turn;
            }
            else if(turn - roboTurn == -90 || turn - roboTurn == 270)
            {
                fout<<"L";
                roboTurn = turn;
            }
            
            
            //printf("C:%d N:%d T:%d R:%d\n",current,next,turn,roboTurn);
            
            current = next;
        }
        
        fout<<"\";";
        
        fout.close();
        printf("Succesfully written path to 'finalPath.h'\n");
        
    }
};
