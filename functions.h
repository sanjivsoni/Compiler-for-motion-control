
int matrix[20][20] = {0};
int obstaclesBuffer[100][100];
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
  while(k < obstacles)
  {
    matrix[obstaclesBuffer[k][0]][obstaclesBuffer[k][1]] = 1;
    k++;
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
    for(j=0;j<intColumns;++j)
      {
        printf("%d\t",matrix[i][j]);
      }
  }
}
