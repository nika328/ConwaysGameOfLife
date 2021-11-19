#include <stdio.h>
#include <time.h>
#include <stdlib.h>


//THE NEIGHBOURS FUNCTION, COUNTS THE LIVING CELLS IN A MATRIX AROUND THE CELL, EXCEPT FROM THE CELL ITSELF
int neighbours(int rows, int columns, int pos_rows, int pos_columns, int arr[][columns+2])
{
    int count = 0;
    {
        for(int i=pos_rows-1; i<=pos_rows+1; i++)
        {

            for (int j=pos_columns-1; j<=pos_columns+1; j++)
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
    }
    return count;
}

int main(void) {
  printf("======================================================\n");
  printf("      WELCOME TO THE CONWAY'S GAME OF LIFE\n");
  printf("      To see the next generation - press c\n");
  printf("       To terminate the program - press n.\n");
  printf("======================================================\n");
  printf("Let's start .... \n");
  int rows, columns;
  printf("Enter the number of rows: ");
  scanf("%d", &rows);
  int*prows=&rows;
  printf("\nEnter the number of columns: ");
  scanf("%d", &columns);
  srand(time(NULL)*time(NULL));
  //srand(5);

  // DEFINING A BOARD WITH ONE ACCESSIVE ROW AND COLUMNS AT EACH SIDE:
  //printf("The board with 1 more row and 1 more column at each side is: \n");
  int board[rows+2][columns+2];
    for(int i=0; i<rows+2; i++)
    {
        for (int j=0; j<columns+2; j++)
        {
            board[i][j]=0;
            //printf("%d", board[i][j]);
        }
        //printf("\n");
    }
    

    //SYMBOLS FOR EMPTY AS WELL AS LIVING CELL ARE ARBITRARY, CAN BE CHANGED TO ANYTHING
    char empty='-';
    char cell='#';

    //INPUT FROM USER TO DECIDE WHETHER WE SHOULD CONTINUE, RIGHT NOW IS SET TO 'a', TRUE
    char input='a';

    //THE ASSIGNMENT WAS TO SET DEFAULT POPULATION TO 7 CELLS
    //PUTTING THE INITIAL CELLS RANDOMLY AT THE BOARD
    const int pop=7;
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
    
    /*printf("\nThe board after filled pop:\n");
    for(int i=0; i<rows+2; i++)
    {
        for (int j=0; j<columns+2; j++)
        {
            
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
    */
   //PRINTING THE INITIAL BOARD (WITHOUT THE ACCESSIVE ROWS AND COLUMNS)
   //printf("\nJust the part of the 'real' board: \n");
    printf("\n");
    for(int i=1; i<rows+1; i++)
    {
        for (int j=1; j<columns+1; j++)
        {
            if(board[i][j]==0)
            {printf("%c", empty);}
            else{printf("%c", cell);}
        }
        printf("\n");
    } 
    //FIRST INPUT FROM THE USER   
    scanf(" %c", &input);
    if(input=='n')
      {
        exit(88);
      }
    //NEW LINES,THEY SHOULD MOVE THE CONTENT TO THE HEAD OF A NEW 'PAGE'
    //MAY WORK DIFFERENTLY IN A DIFFERENT CONSOLE :(
    for (int x=0; x<20; x++)
    {printf("\n");}
    
    //I HAD TO CREATE A NEW 2D ARRAY WHERE WILL BE THE OUTPUT COPPIED, BECAUSE IF YOU CHANGE IT DIRECTLY ON A BOARD, THE CELL HAVING FOR EXAMPLE 3 NEIGHBOURS BUT ONE DYING IN THE SAME ROUND WILL NOT BE REINCARNATED AS AT THE TIME OF THE EXECUTION WILL ONLY HAVE 2 
    int output[rows][columns];
    //THE MAIN LOOP
    while (input!='n') 
    {
        for (int i=1; i<rows+1; i++)
        {
            for (int j=1; j<columns+1; j++)
            {

                int nghbrs=neighbours(rows, columns, i,j, board);
                //The dead cell with ideal neigbours number (3) is relived
                if(board[i][j]==0 && nghbrs==3)
                {
                    output[i-1][j-1]=1;
                    board[i][j]=1;
                }
                //The living cell of more than 3 neighbours dies = overpopulation
                //The living cell of less then 2 neighbours dies = underpopulation
                else if((board[i][j]==1 && nghbrs>3) || (board[i][j]==1 && nghbrs<2))
                {
                    output[i-1][j-1]=0;
                    board[i][j]=0;
                }
                //The other cells do not change their state
                else
                {
                    output[i-1][j-1]=board[i][j];
                    continue;
                }        
            }
        }
        //PRINTING THE CURRENT GENERATION
        for(int i=0; i<rows; i++)
        {
            for (int j=0; j<columns; j++)
            {
                if(output[i][j]==1){
                    printf("%c", cell);
                }
                else{
                    printf("%c",empty);
                }
            }
            printf("\n");
        }
        //MOVING TO THE NEXT 'PAGE'
        //THIS FORMULA WORKED FOR REPL.IT BUT ANYTIME YOU SHRINK OR EXPAND THE VIEWING TABLE IT WILL BE DIFFERENT
       for (int x=0; x<25-(rows-5); x++)
         {printf("\n");}
        //THE USER'S INPUT, BTW IT CAN BE ANYTHING EXCEPT FROM 'n' TO CONTINUE
        scanf(" %c", &input); 
    }
  return 0;
}