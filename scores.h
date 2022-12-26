#ifndef SCORES_H_INCLUDED
#define SCORES_H_INCLUDED

int score(int h,int w,int* board[h],int player_number)
{

    int count =0;
    // horizontal
    for (int j = 1; j<=h-3 ; j++ )
    {
        for (int i = 1; i<=w; i++)
        {
            if (board[i][j] == player_number && board[i][j+1] == player_number && board[i][j+2] == player_number && board[i][j+3] == player_number)
            {
                count++;
            }
        }
    }
    // vertical
    for (int i = 1; i<=w-3 ; i++ )
    {
        for (int j = 1; j<=h; j++)
        {
            if (board[i][j] == player_number && board[i+1][j] == player_number && board[i+2][j] == player_number && board[i+3][j] == player_number)
            {
                count++;
            }
        }
    }
    // ascendingDiagonal
    for (int i=4; i<=w; i++)
    {
        for (int j=1; j<=h-3; j++)
        {
            if (board[i][j] == player_number && board[i-1][j+1] == player_number && board[i-2][j+2] == player_number && board[i-3][j+3] == player_number)
                count++;
        }
    }
    // descendingDiagonal
    for (int i=4; i<=w; i++)
    {
        for (int j=4; j<=h; j++)
        {
            if (board[i][j] == player_number && board[i-1][j-1] == player_number && board[i-2][j-2] == player_number && board[i-3][j-3] == player_number)
                count++;
        }
    }
    return count;
}

#endif // SCORES_H_INCLUDED
