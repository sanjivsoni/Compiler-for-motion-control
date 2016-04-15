
#include "dijkstra.h"

int matrix[20][20] = {0};
int row_1D_matrix[20] = {0};
int col_1D_matrix[20] = {0};
int obstaclesBuffer[100][100];
int adjacency[100][100]= {0};
int path =0 ;
char *rows, *columns, *coordinateX, *coordinateY ;


int obstacles = 0;

void storeObstacles(char* x, char *y)
{
  static int  row = 0;

  obstaclesBuffer[row][0] = atoi(x);
  obstaclesBuffer[row][1] = atoi(y);

  row++;
  obstacles++;
}

void createSparse()
{
  int k = 0;
  int rowNo, colNo, intRows = atoi(rows),intColumns = atoi(columns);
  while(k < obstacles)
  {
    rowNo = obstaclesBuffer[k][0];
    colNo = obstaclesBuffer[k][1];
    row_1D_matrix[rowNo*intRows + colNo] = 1;
    //col_1D_matrix[rowNo + colNo*intColumns] = 1;
    matrix[rowNo][colNo] = 1;
    k++;
  }

}



void findedge(int row,int col)
{
    int intRows = atoi(rows);
    int intColumns = atoi(columns);

    //To Find Right Edge
    if(col+1<intColumns && row_1D_matrix[row*intRows + (col+1)] == 0 && row_1D_matrix[row*intRows + col]==0)
     {
       //Check if the edge exists already, if not proceed
       if(adjacency[row*intRows + (col+1)][row*intRows + col] != 1)
       {
         //Mark both directions in adjacency matrix because if a edge exists
         //from Point 1 to 2, there exists a edge from 2 to 1.
         adjacency[row*intRows + (col+1)][row*intRows + col] = 1;
         adjacency[row*intRows + col][row*intRows + (col+1)] = 1;
         //printf("Found right edge(%d,%d)\n",row,col);
         findedge(row,col+1);
       }
     }
     //To Find Bottom Edge
   if(row + 1<intRows && row_1D_matrix[(row+1)*intRows + col]==0 && row_1D_matrix[row*intRows + col]==0)
    {
      //Check if the edge exists already, if not proceed
      if(adjacency[(row+1)*intRows + col][row*intRows + col] != 1)
      {
        //Mark both directions in adjacency matrix because if a edge exists
        //from Point 1 to 2, there exists a edge from 2 to 1.
      adjacency[(row+1)*intRows + col][row*intRows + col] = 1;
      adjacency[row*intRows + col][(row+1)*intRows + col] = 1;
      //printf("Found bottom edge(%d,%d)\n",row,col);
      findedge(row+1,col);
    }
    }
    //To Find Left Edge
    if(col-1>=0 && row_1D_matrix[row*intRows + (col-1)]==0 && row_1D_matrix[row*intRows + col]==0)
      {
        //Check if the edge exists already, if not proceed
        if(adjacency[row*intRows + (col-1)][row*intRows + col] != 1)
        {
          //Mark both directions in adjacency matrix because if a edge exists
          //from Point 1 to 2, there exists a edge from 2 to 1.
        adjacency[row*intRows + (col-1)][row*intRows + col] = 1;
        adjacency[row*intRows + col][row*intRows + (col-1)] = 1;
        //printf("Found left edge(%d,%d)\n",row,col);
        findedge(row,col-1);
        }
      }
      //To Find Top Edge
    if(row-1>=0 && row_1D_matrix[(row-1)*intRows + col]==0 &&row_1D_matrix[row*intRows + col]==0)
      {
        //Check if the edge exists already, if not proceed
        if(adjacency[(row-1)*intRows + col][row*intRows + col] != 1)
        {
          //Mark both directions in adjacency matrix because if a edge exists
          //from Point 1 to 2, there exists a edge from 2 to 1.
          adjacency[(row-1)*intRows + col][row*intRows + col] = 1;
          adjacency[row*intRows + col][(row-1)*intRows + col] = 1;
          //printf("Found top edge(%d,%d)\n",row,col);
          findedge(row-1,col);
        }
      }


    return ;

}


void printAdjacency()
{
  int i,j;
  printf("\n");
  for(i=0;i<path;++i)
    {
      for(j=0;j<path;++j)
      printf("%d  ",adjacency[i][j] );
      printf("\n");
    }
}

void displayMatrix()
{
  int i,j;
  int intRows = atoi(rows);
  int intColumns = atoi(columns);

  printf("\nThe matrix is");
  for(i=0;i<intRows;++i)
  {
    printf("\n");
    for(j=0;j<intColumns;j++)
    printf("%d  ",matrix[i][j] );


}

  path = (intRows * intColumns) - obstacles;
//  startDijkstra(matrix, intRows,intColumns, path);
printf("\n");
findedge(0,0);
printAdjacency();
}
