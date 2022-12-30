#ifndef HIGHSCORES_H_INCLUDED
#define HIGHSCORES_H_INCLUDED


#define MAX_HIGH_SCORES 100

int n_players;
typedef struct player{
  char name[10];
  int score;
}player_t;

void InsertionSort(player_t* arr)
{
        player_t key;
    int i,j;
    for ( i = 1; i < MAX_HIGH_SCORES; i++)
    {
        key = arr[i];
        j = i - 1;
        while ( j >= 0 && arr[j].score> key.score)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }

}

int check_names_similarity(char* name1,char*name2)
{
    if((int)strlen(name1)!=(int)strlen(name2))
    {
        return 0;
    }
    else
    {
        for(int i=0;i<(int)strlen(name1);i++)
        {
            if(tolower(name1[i])!=tolower(name2[i]))
              {
                  return 0;
              }
        }
    }
    return 1;
}


void update_highscores(char* name,int score,player_t* arr)
{
    int already=0;
    for(int i=0;i<MAX_HIGH_SCORES;i++)
    {

        if(check_names_similarity(name,arr[i].name))
        {
            if(score>arr[i].score)
            {arr[i].score=score;}
            already=1;break;
        }
    }
    if(!already && score>arr[0].score)
    {
    strcpy(arr[0].name,name);
    arr[0].score=score;
    }

InsertionSort(arr);
}
void write_highscores(player_t* topscores)
{
  FILE *fp;

  fp = fopen("HighScores.bin", "w");

  fwrite(topscores, sizeof(player_t),MAX_HIGH_SCORES, fp);
  fclose(fp);
}
void read_highscores(player_t* topscores)
{
  FILE *fp;


  fp = fopen("HighScores.bin", "r");
  if (fp == NULL){
    write_highscores(topscores);
  }
  n_players = 0;
  while( fread(&topscores[n_players], sizeof(player_t), 1, fp) == 1 ) {
    n_players++;
  }
  fclose(fp);

}
void print_highscores(player_t* topscores,int n)
{

  for (int i=MAX_HIGH_SCORES-1; i>=MAX_HIGH_SCORES-n; i--) {
    printf("%d. %s : %d\n",MAX_HIGH_SCORES-i,topscores[i].name ,topscores[i].score);
  }
  printf("Press Any Key to Continue\n");
getch();
}

#endif // HIGHSCORES_H_INCLUDED
