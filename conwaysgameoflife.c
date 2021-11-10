#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//We start with population of random number in this case 7, on a board of 5 rows x 5 columns
int pop=7;
int rows=5;
int columns=5;
char cell=254;
char empty=' ';

//function to calculate the neighbours (values of 1 around the cell) to a particular position
int neighbours(int arr[][columns], int rows, int columns, int pos_rows, int pos_columns)
{
    int count = 0;
    for(int i= pos_rows-1; i<pos_rows+2; i++)
    {
        for (int j=pos_columns-1; i<pos_columns+2; j++)
        {
            if(i==pos_rows && j== pos_columns){continue;}
            else 
            {
                if(arr[i][j]==1)
                {
                    count++;
                }
                else{continue;}
            }
        }
    }
    return count;
}

int main()
{
    //creating a board that would have at each side a free column (will be useful when counting neighbours that there won't be any random values)
    //the actual board would be from 1 to n and 1 to m (usually it is from 0 to n-1 and 0 to m-1)
    int board[rows+2][columns+2];
    for(int i=0; i<rows+2; i++)
    {
        for (int j=0; j<columns+2; j++)
        {
            board[i][j]=0;
        }
    }

    //creating population of pop on the board 
    srand(time(NULL)*time(NULL));
    int count=0;
    while(count<pop)
    {
       int pos1=rand()%(rows)+1;
       int pos2=rand()%(columns)+1;
       if(board[pos1][pos2]==0)
       {
           board[pos1][pos2]=1;
           count++;
       }
       else{continue;}     
    }
    //main cycle
    char cont='Y';
    while(cont!='N')
    {
        //changing and displaying of one generation
        for (int i=1; i<rows+1; i++)
        {
            for (int j=1; j<columns+1; j++) 
            {
                int nghbrs=neighbours(board[rows+2][columns+2], rows, columns, i,j);
                //The dead cell with ideal neigbours number (3) is relived
                if(board[i][j]==0 && nghbrs==3)
                {
                    board[i][j]=1;
                }
                //The living cell of more than 3 neighbours dies = overpopulation
                //The living cell of less then 2 neighbours dies = underpopulation
                else if((board[i][j]==1 && nghbrs>3) || (board[i][j]==1 && nghbrs<2))
                {
                    board[i][j]=0;
                }
                //The other cells do not change their state, now will be printed the characters set for empty space or cell depending on the value of particular bit
                if(board[i][j]==0)
                {
                    printf("%c", empty);
                }
                else{
                    printf("%c", cell);
                }
                printf("\n");
            }
        }
        cont=fgetc(stdin);
        fputc('\n', stdout);
    }
    
       



    return 0;
}