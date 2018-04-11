#include <stdio.h>

#include <stdlib.h>

#define N 3

int h[N][N];   //created an heuristics of grids

int counter=1;

int uc=0;

int i,j;

int start_x,end_x,start_y,end_y;
void main()
{
    //for input of starting and ending
    printf("ENTER THE STARTING X CORDINATE");
    scanf("%d",&start_x);

    printf("ENTER THE STARTING Y CORDINATE");
    scanf("%d",&start_y);

    printf("ENTER THE ENDING X CORDINATE");
    scanf("%d",&end_x);

    printf("ENTER THE ENDING Y CORDINATE");
    scanf("%d",&end_y);


    for(i=0;i<N;i++)//i stands for x
    {
        for(j=0;j<N;j++)//j stands for y
        {
            h[i][j]=abs(end_x-i)+abs(end_y-j);
        }
    }//gets all the eucelidian h values
    printf("THE EUCELEDIAN HEURISTICS IS AS FOLLOWS: \n");
    for(i=N-1;i>=0;i--)
    {
        for(j=0;j<N;j++)
        {
            printf("%d\t",h[j][i]);
        }
        printf("\n");
    }//prints the output


    for(i=0;i<abs(end_x-start_x);i++)
    {
        //printf("HELLO");
        if((end_x-start_x)<0)
        {
            printf("left\t");
        }
        else
        {
            printf("right\t");
        }
    }

    for(i=0;i<abs(end_y-start_y);i++)
    {
       // printf("HELLO");
        if((end_y-start_y)<0)
        {
            printf("down\t");
        }
        else
        {
            printf("up\t");
        }
    }


    ///////////////////////////best way to go without blocks

}

