//100 fr block

//0 for node

//-1 for start
//1 for end



#include <stdio.h>

#include <stdbool.h>

int c_left=0;
int c_right=0;
int c_up=0;
int c_down=0;

int c_x=0;
int c_y=0;

int i,j;

int blocks=0;

int block_x,block_y;

int start_x,start_y,end_x,end_y;

int grid[3][3];

void input(int grid[][3])
{
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
            {
                grid[i][j]=0;
            }
    }//all are initialised as zero

    printf("ENTER THE STARTING X CORDINATE\n");
    scanf("%d",&start_x);

    printf("ENTER THE STARTING Y CORDINATE\n");
    scanf("%d",&start_y);

    printf("ENTER THE ENDING X CORDINATE\n");
    scanf("%d",&end_x);

    printf("ENTER THE ENDING Y CORDINATE\n");

    scanf("%d",&end_y);

    printf("ENTER THE NUMBER OF BLOCKS\n");
    scanf("%d",&blocks);

    grid[start_x][start_y]=-1;
    grid[end_x][end_y]=1;

    for(i=0;i<blocks;i++)
    {
        printf("ENTER THE X CORDINATE\n");
        scanf("%d",&block_x);

        printf("ENTER THE Y CORDINATE\n");
        scanf("%d",&block_y);

        grid[block_x][block_y]=100;

    }


}

bool isBlock(int grid[][3],int x, int y)
{
    if(grid[x][y]==100)     //100 is the block
    {
        return true;
    }
    else
    {
        return false;
    }
}//end of block check

void right()
{
    printf("RIGHT\n");
}

void left()
{
    printf("LEFT\n");
}

void up()
{
    printf("UP\n");
}


void down()
{
    printf("DOWN\n");
}


void co_diff()
{

    for(i=0;i<abs(end_x-start_x);i++)
    {
        //printf("HELLO");
        if((end_x-start_x)<0)
        {
            c_left++;
        }
        else
        {
            c_right++;
        }
    }

    for(i=0;i<abs(end_y-start_y);i++)
    {
       // printf("HELLO");
        if((end_y-start_y)<0)
        {
            c_down++;
        }
        else
        {
            c_up++;
        }
    }

    c_x=c_left+c_right;
    c_y=c_up+c_down;
}

/*void start_end(int grid[][3])
{
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(grid[i][j]==-1)
            {
                start_x=i;
                start_y=j;
            }
            else if(grid[i][j]==1)
            {
                end_x=i;
                end_y=j;
            }
        }
    }
}*/


void move(int grid[][3],int x,int y,int val)
{

    if((x==end_x)&&(y==end_y))
    {
        printf("END BRO");
        return;
    }
    //val==-1 means x direction
    if(val==-1)
    {
        if(c_x>0)
        {
            //checks left or right
            if(c_left>0)
            {
                //bot has to go left
                //check for block
                if(isBlock(grid,x-1,y))
                {
                    //block handling
                    move(grid,x,y,1);
                }
                else
                {
                    c_left--;
                    c_x--;
                    left();
                    move(grid,x-1,y,-1);
                }

            }
            else if(c_right>0)
            {
                //bot has to go right
                //check for block
                if(isBlock(grid,x+1,y))
                {
                    //block handling
                    move(grid,x,y,1);
                }
                else
                {
                    c_right--;
                    c_x--;
                    right();
                    move(grid,x+1,y,-1);
                }
            }

            //printf("x counter %d",c_x);
        }
        else
        {
            move(grid,x,y,1);
        }

    }//end of val check

    //val==1 means y direction

    if(val==1)
    {
        if(c_y>0)
        {
            //checks up or down
            if(c_up>0)
            {
                //bot has to go up
                //check for block
                if(isBlock(grid,x,y+1))
                {
                    //block handling
                    move(grid,x,y,-1);
                }
                else
                {
                    c_up--;
                    c_y--;
                    up();
                    move(grid,x,y+1,1);
                }
            }
            else if(c_down>0)
            {
                //bot has to go down
                //check for block
                if(isBlock(grid,x,y-1))
                {
                    //block handling
                    move(grid,x,y,-1);
                }
                else
                {
                    c_down--;
                    c_y--;
                    down();
                    move(grid,x,y-1,1);
                }
            }
        }

        else
        {

            move(grid,x,y,-1);
        }
    }//end of y direction


}

void output(int grid[][3])
{

    for(i=2;i>=0;i--)
    {
        for(j=0;j<3;j++)
        {
            printf("%d \t",grid[j][i]);
        }
        printf("\n");
    }
}


void main()
{
       input(grid);
       output(grid);
   //    start_end(grid);
       co_diff();
       move(grid,start_x,start_y,-1);
}
//better
