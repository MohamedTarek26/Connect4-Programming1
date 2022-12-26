#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED

#include"my_utils.h"
#include"undo_redo.h"
#include"scores.h"

char name[10];
int score_winner;
char* getname()
{return name;}

int get_winnerScore()
{
    return score_winner;
}
int calc_row(int col,int h,int w,int* board[h])
{
    int row=0;
    for(int i=h; i>=1; i--)
    {
        if(board[i][col]!=0)
        {
            row=i+1;
            break;
        }
        row=1;
    }
    return row;
}

void print_board(int h,int w,int* board[h])
{
    for(int i=h; i>=1; i--)
    {
        for(int j=1; j<=w; j++)
        {
            printf("% d ",board[i][j]);
        }
        printf("\n");
    }
}

void play(int*actions,int col,int h,int w,int* board[h],int playern,int* curr_round,int* max_round)
{
    actions[*curr_round]=col;
    for(int i=*curr_round+1; i<=*max_round; i++)
        actions[i]=0;
    *curr_round=*curr_round+1;
    *max_round=*curr_round;
    int row=calc_row(col,h,w,board);
    printf("%d %d\n",row,col);
    board[row][col]=playern;
    print_board(h,w,board);
}



void game_loop(int h,int w)
{
    int* board[h+1];
    for(int i=1; i<=h; i++)
        board[i]=(int*)calloc(w+1,sizeof(int));

    int* actions=(int*)calloc(w*h+1,sizeof(int));
    int curr_round=1;
    int max_round=1;
    int score1=0;
    int score2=0;
    int playern=1;
    while (curr_round!=(w*h+1))
    {
        if(curr_round==0)
            curr_round=1;
        playern= (curr_round%2==0)? 2:1;
        printf("Player %d choose a column:",playern);
        printf("Type -1 for undo , -2 for redo");
        printf(" CURRENT ROUND : %d \n",curr_round);
        int col;
        scanf("%d",&col);
        //check validity
        if(col==-1)
        {
            undo(actions[curr_round-1],h,w,board,playern,&curr_round,max_round);
        }
        else if(col==-2)
        {
            redo(actions[curr_round],h,w,board,playern,&curr_round,max_round);
        }
        else
        {
            play(actions,col,h,w,board,playern,&curr_round,&max_round);
        }
        score1=score(h,w,board,1);
        score2=score(h,w,board,2);
        printf("Player 1 : %d Player 2 : %d\n",score1,score2);
    }

    if(score1>score2)
    {
        printf("Player %d is the winner \n Please enter your name : ",1);
        scanf(" %s",&name);
        score_winner=score1;
    }
    else if(score2>score1)
    {
        printf("Player %d is the winner \n Please enter your name : ",2);
        scanf(" %s",&name);
        score_winner=score2;
    }
    else
    {
        printf("It is a tie\n");
        score_winner=0;
    }
}

// 1 2 3 4 1 2 3 4 1 2 4 3 1 3 2 4
#endif // GAMELOOP_H_INCLUDED
