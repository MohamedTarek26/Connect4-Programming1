#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct{
   int boardrows;
   int boardcolumns;
   int score1;
   int score2;
   int orderofplay;
   char connectboard[100][100];
   int timeofplay;
}gamestatsave;


//begining of load
void main()
{
    gamestatsave game[3];
    FILE *floading;
    floading=fopen("savedgames.bin","r");
    if(floading)
    {
       fread(&game,sizeof(gamestatsave),3,floading);
       fclose(floading);
    for(int i=0;i<3;i++)
    {
    printf("game number %d\n",i+1);
    printf("roe:%d\n",game[i].boardrows);
    printf("col:%d\n",game[i].boardcolumns);
    printf("order:%d\n",game[i].orderofplay);
    printf("score1:%d\n",game[i].score1);
    printf("score2:%d\n",game[i].score2);
    printf("time:%d\n",game[i].timeofplay);
    printf("the board:\n");
    for(int k=0;k<game[i].boardrows;k++)
    {
        for(int j=0;j<game[i].boardcolumns;j++)
        {
            printf("%c ",game[i].connectboard[k][j]);
        }
        printf("\n");
    }
    }
    }
    else
        printf("file doesn't exist");

}
//end of load

/*
//begining of save
void main()
{
    gamestatsave game[3];
    int index;
    // assigning the passed parameters in the struct
    int row,col,s1,s2,o,t;
    char board [row][col];
    //initializing the variables
    row=6; col=7; s1=6; s2=7; o=25; t=20989;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            board[i][j]='x';
        }
    }
    //taking input of the structure
    //seeing where to save
    for(int i=0;i<3;i++)
    {
    game[i].boardcolumns=col;
    game[i].boardrows=row;
    game[i].orderofplay=0;
    game[i].score1=0;
    game[i].score2=0;
    game[i].timeofplay=0;
    for(int k=0;k<row;k++)
    {
        for(int j=0;j<col;j++)
        {
            game[i].connectboard[k][j]='o';
        }
    }
    }
    scanf("%d",&index);
    index=index%3;
    //game[index].boardcolumns=col;
    //game[index].boardrows=row;
    game[index].orderofplay=o;
    game[index].score1=s1;
    game[index].score2=s2;
    game[index].timeofplay=t;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            game[index].connectboard[i][j]=board[i][j];
        }
    }

    FILE *fsaving;
    fsaving=fopen("savedgames.bin","wb");
    fwrite(&game,sizeof(gamestatsave),3,fsaving);
    fclose(fsaving);
}
//end of save





/*
  gamestat game[3];
    int i,m,n,scorep1,scorep2,orderp;
    scanf("%d*%d",&m,&n);
    char connectfour[n][m];
    for(int x=0;x<n;x++)
    {
        for(int y=0;y<m;y++)
            connectfour[x][y]='-';
    }

    scanf("%d %d %d",&scorep1,&scorep2,&orderp);

/*    for(int x=0;x<n;x++)
    {
        for(int y=0;y<m;y++)
            game.a[x][y]=connectfour[x][y];
    }
    game.score1=scorep1;
    game.score2=scorep2;
    game.orderofplay=orderp;
    scanf("%d",&i);
    i%=3;
    if(!i)
        i=3;
    switch (i)
    {
    case 1:
        {
        FILE *game1;
        game1=fopen("firstgame.txt","w");
        for(int x=0;x<n;x++)
        {
            for (int y=0;y<m;y++)
              fprintf(game1,"%c ",connectfour[x][y]);
            fprintf(game1,"\n");
        }
        fprintf(game1 ,"%d\n",scorep1);
        fprintf(game1,"%d\n",scorep2);
        fprintf(game1,"%d\n",orderp);
        fclose(game1);
        printf("first file");
        break;
        }
    case 2:
        {
        FILE *game2;
        game2=fopen("secondgame.txt","w");
        for(int x=0;x<n;x++)
        {
            for (int y=0;y<m;y++)
              fprintf(game2,"%c ",connectfour[x][y]);
            fprintf(game2,"\n");
        }
        fprintf(game2,"%d\n",scorep1);
        fprintf(game2,"%d\n",scorep2);
        fprintf(game2,"%d\n",orderp);
        fclose(game2);
        printf("second file");
        break;
        }
    case 3:
        {
        FILE *game3;
        game3=fopen("thirdgame.txt","w");
        for(int x=0;x<n;x++)
        {
            for (int y=0;y<m;y++)
              fprintf(game3,"%c ",connectfour[x][y]);
            fprintf(game3,"\n");
        }
        fprintf(game3 ,"%d\n",scorep1);
        fprintf(game3,"%d\n",scorep2);
        fprintf(game3,"%d\n",orderp);
        fclose(game3);
        printf("third file");
        break;
        }
    }
*/
