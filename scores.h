#ifndef SCORES_H_INCLUDED
#define SCORES_H_INCLUDED

int score(int h,int w,int* board[h],int player)
{
int  c=0;
    // horizontalCheck
    for (int j = 1; j<=h-3 ; j++ ){
        for (int i = 1; i<=w; i++){
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player){
                c++;
            }
        }
    }
    // verticalCheck
    for (int i = 1; i<=w-3 ; i++ ){
        for (int j = 1; j<=h; j++){
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player){
                c++;
            }
        }
    }
    // ascendingDiagonalCheck
    for (int i=4; i<=w; i++){
        for (int j=1; j<=h-3; j++){
            if (board[i][j] == player && board[i-1][j+1] == player && board[i-2][j+2] == player && board[i-3][j+3] == player)
                c++;
        }
    }
    // descendingDiagonalCheck
    for (int i=4; i<=w; i++){
        for (int j=4; j<=h; j++){
            if (board[i][j] == player && board[i-1][j-1] == player && board[i-2][j-2] == player && board[i-3][j-3] == player)
                c++;
        }
    }


return c;
}

#endif // SCORES_H_INCLUDED
