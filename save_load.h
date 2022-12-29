#ifndef SAVE_LOAD_H_INCLUDED
#define SAVE_LOAD_H_INCLUDED

typedef struct{
   int boardrows;
   int boardcolumns;
   int Current_Round;
   int board[100][100];
   int mode;
   int hours;
   int minutes;
   int seconds;
}game_t;

int n_games = 0;
void update_save(game_t* saves,game_t game,int load_number,int saved_now)
{
    if(saved_now && !load_number)
    {
        saves[1]=game;
        return;
    }
    if(load_number == 0)
    {game_t game1= saves[1];
    game_t game2= saves[2];
    saves[3]=game2;
    saves[2]=game1;
    saves[1]=game;}
    else
    {
       saves[load_number]=game;
    }

}
void write_save(game_t* saves)
{
  FILE *fp;

  fp = fopen("save.bin", "w");

  fwrite(saves, sizeof(game_t),5, fp);
  fclose(fp);
}
void read_save(game_t* saves)
{
  FILE *fp;


  fp = fopen("save.bin", "r");
  if (fp == NULL){
    write_save(saves);
  }
  int i=0;
  while( fread(&saves[i], sizeof(game_t), 1, fp) == 1 ) {
    if(saves[i].Current_Round != 0)
    {
    n_games++;
    }
    i++;
  }
  printf("nagemes:%d",n_games);
  fclose(fp);

}
void print_saves(game_t* saves)
{
  for (int i=1; i<=3; i++) {
    printf("%d \n",saves[i].Current_Round);
  }
}
#endif // SAVE_LOAD_H_INCLUDED
