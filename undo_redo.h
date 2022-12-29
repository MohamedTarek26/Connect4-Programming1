#ifndef UNDO_REDO_H_INCLUDED
#define UNDO_REDO_H_INCLUDED


void undo(int col,int h,int w,int* board[h],int playern,int* curr_round,int max_round)
{
    system("cls");
    if(*curr_round-1 <1)
    {
        printf("YOU CANOT UNDO!\n");
        return;
    }
    int row=calc_row(col,h,w,board);
    board[row-1][col]=0;
    *curr_round=*curr_round-1;

}
void redo(int col,int h,int w,int* board[h],int playern,int* curr_round,int max_round)
{
    system("cls");
    if(*curr_round+1 > max_round)
    {
        printf("YOU CANOT REDO!\n");
        return;
    }
    int row=calc_row(col,h,w,board);
    board[row][col]=playern;
    *curr_round=*curr_round+1;

}


#endif // UNDO_REDO_H_INCLUDED
