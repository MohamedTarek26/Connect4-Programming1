#ifndef GAMELOOP_H_INCLUDED
#define GAMELOOP_H_INCLUDED

#define MAXSIZE 1000


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


int seconds,minutes,hours;
int start_time=0,end_time=0;
void timecalculate(int hours_i,int minutes_i,int seconds_i)
{
    // calculating ticks since start of the game
    int ticks;
    ticks=clock();
    // calculating the seconds and minusing the time till begining of the game
    // and adding the seconds of the loaded game if it was loaded
    seconds=(((int)ticks / CLOCKS_PER_SEC))+seconds_i-start_time+end_time;
    // calculating how many hours are in those seconds
    hours=((seconds-seconds%3600)/(3600))+hours_i;

    // calculatintg the remaining minutes
    // despite the minutes calculated before in the hours
    minutes=((seconds-hours*60*60)/60)+minutes_i;

    // calculating the rest of seconds
    seconds%=60;
    printf("Time passed %d:%d:%d\n",hours,minutes,seconds);

}




int n_games = 0;

void update_save(game_t* saves,game_t game,int load_number,int saved_now)
{
    if(saved_now && !load_number)
    {
        saves[1]=game;
    }
    //the shifting concept in the game
    else if(load_number == 0)
    {
        game_t game1= saves[1];
        game_t game2= saves[2];

        saves[3]=game2;

        saves[2]=game1;
        saves[1]=game;
    }

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

  // if file corrupted or doesn't exist the make a new one
  if (fp == NULL)
    {
      write_save(saves);
    }
  int i=0;
  n_games=0;

  // reading the saved games
  while( fread(&saves[i], sizeof(game_t), 1, fp) == 1 )
  {
    if(saves[i].Current_Round != 0)
    {
       n_games++;
    }
    i++;
  }
  fclose(fp);

}


// checking th input name when user enters there's
bool name_check(char* s)
{
    if(!strlen(s))
    {
        printf("Name too small\n");
        return false;
    }
    if(strlen(s)>10)
    {
        printf("Name too big\n");
        return false;
    }
    for(int i=0;i<10;i++)
    {
        if(isspace(s[i]))
        {
            printf("Name can't include spaces\n");

            return false;
        }
    }

    return true;
}


// calculating score
int score(int h,int w,int* board[h],int player)
{
    int  c=0;
    // horizontalCheck
    for (int i = 1; i<=h-3 ; i++ )
    {
        for (int j = 1; j<=w; j++)
        {
            if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player)
            {
                c++;
            }
        }
    }

    // verticalCheck
    for (int j = 1; j<=w-3 ; j++ )
    {
        for (int i = 1; i<=h; i++)
        {
            if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player)
            {
                c++;
            }
        }
    }

    // ascendingDiagonalCheck
    for (int j=4; j<=w; j++)
    {
        for (int i=1; i<=h-3; i++)
        {
            if (board[i][j] == player && board[i+1][j-1] == player && board[i+2][j-2] == player && board[i+3][j-3] == player)
                c++;
        }
    }
    // descendingDiagonalCheck
    for (int j=4; j<=w; j++)
    {
        for (int i=4; i<=h; i++)
        {

            if (board[i][j] == player && board[i-1][j-1] == player && board[i-2][j-2] == player && board[i-3][j-3] == player)
                c++;
        }
    }


    return c;
}

void undo(int col,int h,int w,int* board[h],int playern,int* curr_round,int max_round)
{
    system("cls");
    // seeing if he can undo
    if(*curr_round-1 <1)
    {
        printf("YOU CANOT UNDO!\n");
        return;
    }

    // making undo concept
    int row=calc_row(col,h,w,board);
    board[row-1][col]=0;
    *curr_round=*curr_round-1;

}
void redo(int col,int h,int w,int* board[h],int playern,int* curr_round,int max_round)
{
    system("cls");

    // seeing if he can redo
    if(*curr_round+1 > max_round)
    {
        printf("YOU CANOT REDO!\n");
        return;
    }

    // making redo concept
    int row=calc_row(col,h,w,board);
    board[row][col]=playern;
    *curr_round=*curr_round+1;

}

char name[12];
int score_winner;

void green ()
{
    printf("\033[0;32m");
}

void red ()
{
    printf("\033[1;31m");
}
void blue()
{
    printf("\033[0;34m");
}
void yellow()
{
    printf("\033[1;33m");
}
void reset ()
{
    printf("\033[0m");
}
int random_col_selection(int y)
{
    int col,lower=1,upper;
    upper=y;
    col = rand()%(upper-lower+1)+lower;
    return col;
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
    blue();
    for(int printingnumber=0; printingnumber<w; printingnumber++)
    {
        if (printingnumber>9)
            printf("  %d  ",printingnumber+1);
        else
            printf("   %d  ",printingnumber+1);

    }
    printf("\n");
    for(int i=h; i>=1; i--)
    {
        for(int j=1; j<=w; j++)
        {
            if (board[i][j]==1)
            {
                printf("%c  ",186);
                red();
                printf("%c  ",'X');
                blue();
            }
            else if (board[i][j]==2)
            {
                printf("%c  ",186);
                yellow();
                printf("%c  ",'o');
                blue();
            }
            else
                printf("%c  %c  ",186,'-');
        }
        printf("%c",186);
        printf("\n");
        for(int k=0; k<6*w+1; k++)
            putchar(205);
        printf("\n");

        printf("\n");
    }
    reset();

}

void play(int*actions,int col,int h,int w,int* board[h],int playern,int* curr_round,int* max_round)
{


    actions[*curr_round]=col;
    for(int i=*curr_round+1; i<=*max_round; i++)
        actions[i]=0;
    *curr_round=*curr_round+1;
    *max_round=*curr_round;
    int row=calc_row(col,h,w,board);
    board[row][col]=playern;
}

int integercheck()
{
    int integer = 0;
    bool checkint;
    do
    {
        checkint=true;
        // prompt the user for the integer

        char buffer[MAXSIZE];
        fgets(buffer, MAXSIZE, stdin);


        //start of fun
        // i will keep our current index into the string as we loop through it
        // one character at a time
        int i = 0;

        // move through any leading whitespace
        while (isspace(buffer[i]))
            i++;

        // get the length of the string
        int length = strlen(buffer);

        // if the entire string was just whitespace characters ("a blank string")
        // we'll have reached the end of the string and we can return false as the
        // string did not contain an integer
        if (length == i)
            checkint= false;

        // the integer chars will be stored into integer_buffer, we'll use
        // integer_chars to keep track of our index into this buffer as we store
        // each character
        char integer_buffer[MAXSIZE];
        int integer_chars = 0;

        // in the case of a negative integer, the first char may be - symbol
        if (buffer[i] == '-')
        {
            // store the symbol into the buffer, and advance both indexes into the
            // string and buffer
            integer_buffer[integer_chars] = '-';
            integer_chars++;
            i++;

            // if the - character is not followed by a digit, the string does not
            // contain a valid integer
            if (!isdigit(buffer[i]))
                checkint= false;
        }

        // loop through characters until we reach the end of the string or a trailing
        // whitespace character
        while (i < length && !isspace(buffer[i]))
        {
            // if we encounter anything that is not a digit, we do not have a valid int
            // in the string
            if (!isdigit(buffer[i]))
                checkint =false;

            // store the next character into the buffer, advance both indexes
            integer_buffer[integer_chars] = buffer[i];
            integer_chars++;
            i++;
        }

        // put a null terminator onto the end of the buffer to make it a proper string
        integer_buffer[integer_chars] = '\0';

        // loop through any trailing whitespace characters
        while (isspace(buffer[i]))
            i++;

        // if after doing so, we are NOT at the end of the string, then the string
        // does not contain a valid integer
        if (buffer[i] != '\0')
            checkint= false;

        // atoi converts the string representation of our integer to an int type
        // value in C, and we de-reference integer to "return" the value via a pointer
        integer = atoi(integer_buffer);

        // if the input was not a valid integer, tell the user this
        if (!checkint )
        {

            printf("Enter an integer value!\n");


        }

        //end of fun

    }
    while (!checkint);


    return integer;
}

bool checkvalid(int x,int y,int* connect[y],int col,int mode,int playern)
{
    if(col==-1 || col==-2 || col==-3 || col==0 || col == -4 || (col==-5 && mode==1))
        return true;
    int i=x-1,j=col;
    if(j>=1&&j<=y)
    {
        if(calc_row(col,x,y,connect) <=x)
            return true;
        else
        {
            if(!mode || (mode && playern==1))
            {
                printf("Enter an empty column!!!\n");
            }
            return false;
        }
    }
    else
    {
        if(!mode || (mode && playern==1))
        {
            printf("Enter a valid column!!!\n");
        }
        return false;
    }
}


int med_comp_move(int h,int w,int* board[h])
{

    int results[w+1];
    int score1_i=score(h,w,board,1);
    int score2_i=score(h,w,board,2);

    for(int i=1;i<=w;i++)
    {

        if(checkvalid(h,w,board,i,1,2))
        {

            int points=0;
            int score1_f,score2_f;
            int row = calc_row(i,h,w,board);

            board[row][i]=2;
            score2_f=score(h,w,board,2);

            if(score2_f>score2_i)
                {points+=1;}
            board[row][i]=1;
            score1_f=score(h,w,board,1);

            if(score1_f>score1_i)
                {points++;}
            board[row][i]=0;
            results[i]=points;

        }


    }
    for(int i=1;i<=w;i++)
        {
            if(results[i]==2)
                return i;
        }
    for(int i=1;i<=w;i++)
        {
            if(results[i]==1)
                return i;
        }
        int rmove;
    while(true)
            {
                rmove=random_col_selection(w);
                if(checkvalid(h,w,board,rmove,1,2))
                    break;
            }
        return rmove;
}
void game_loop(int h,int w,int mode,int Load_number,game_t* saves)
{

    game_t game;
    bool is_saved=0;
    int* board[h+3];

    for(int i=1; i<=h; i++)
        board[i]=(int*)calloc(w+3,sizeof(int));

    // initializing the values of the game with zeros
    int intial_round=0;
    int h_i=0,s_i=0,m_i=0,moves2=0,moves1=0,playern=1, score1=0,score2=0,max_round=1,curr_round=1;
    int* actions=(int*)calloc(w*h+1,sizeof(int));

    // if loaded initializing the values of the game with the value of the loaded game
    if(Load_number)
    {
        curr_round=saves[Load_number].Current_Round;
        h_i=saves[Load_number].hours,s_i=saves[Load_number].seconds,m_i=saves[Load_number].minutes;

        for(int o=1; o<=h; o++)
        {

            for(int j=1; j<=w; j++)
            {

                if(o>=1 && o<=h && j>=1 && j<=w)
                {

                    board[o][j]=(saves[Load_number]).board[o][j];
                }
                else
                {
                    board[o][j]=0;
                }

            }
        }
        // calculating the score
        score1=score(h,w,board,1);
        score2=score(h,w,board,2);
        intial_round=curr_round;

    }
    //print_board(h,w,board);
    bool paused=0;
    bool show_best_move=0;
    while (curr_round!=(w*h+1))
    {
        print_board(h,w,board);
        if(curr_round==0)
            curr_round=1;
        playern= (curr_round%2==0)? 2:1;

        // printing the game info in this round
        red();
        printf("player 1 score:%d         ",score1);
        yellow();
        printf("player 2 score:%d\n",score2);

        red();


        printf("player 1 moves:%d         ",(curr_round/2));
        yellow();
        printf("player 2 moves:%d\n",((curr_round-1)/2));
        // seeing if it was single easy game
        if (playern==1)
            red();
        else
            yellow();
        if (!mode || playern==1)
        {
        printf("Player %d choose a column\n",playern);
        }
        green();
        if(show_best_move)
        {printf("best move is %d\n",med_comp_move(h,w,board));show_best_move=0;}
        timecalculate(h_i,m_i,s_i);
        printf("Type 0 to close \nType -1 for undo  \nType -2 for redo  \nType -3 for save\nType -4 to go back to main menu\n");
        if(mode==1)
        {
            printf("Type -5 for best move \n");
        }
        printf("CURRENT ROUND : %d \n",curr_round);
        reset();
        int col=0;

        if(!mode || (mode&& playern==1))
        {
            while(true)
            {
                col=integercheck();
                if(checkvalid(h,w,board,col,mode,playern))
                    break;
            }
        }
        else
        {
            if(mode==1)
            {

            while(true)
            {
                col=random_col_selection(w);
                if(checkvalid(h,w,board,col,mode,playern))
                    break;
            }
            }
            else
            {
                col = med_comp_move(h,w,board);
            }
        }

        // undo
        if(col==-1)
        {
            //checking if undo mode is valid
            if(curr_round-1<intial_round && Load_number)
            {

                system("cls");
                printf("YOU CAN'T UNDO!!\n");
                continue;
            }
            // checking if the game is multiplayer or single
            if(!mode)
                undo(actions[curr_round-1],h,w,board,playern,&curr_round,max_round);
            else
            {
                undo(actions[curr_round-1],h,w,board,playern,&curr_round,max_round);

                undo(actions[curr_round-1],h,w,board,playern,&curr_round,max_round);
            }
        }
        //redo
        else if(col==-2)
        {
            // checking if the game is multiplayer or single
            if(!mode)
                redo(actions[curr_round],h,w,board,playern,&curr_round,max_round);
            else
            {
                redo(actions[curr_round],h,w,board,1,&curr_round,max_round);

                redo(actions[curr_round],h,w,board,2,&curr_round,max_round);
            }
        }
        // saving
        else if(col==-3)
        {
            // taking the value of the game to be saved

            for(int o=0; o<=99; o++)
            {
                for(int j=0; j<=99; j++)
                {
                    if(o>=1 && o<=h && j>=1 && j<=w)
                    {
                        (game).board[o][j]=board[o][j];
                    }
                    else
                    {
                        (game).board[o][j]=0;
                    }

                }
            }
            game.mode=mode;
            game.boardcolumns=w;
            game.boardrows=h;
            game.Current_Round=curr_round;
            game.hours=hours;
            game.seconds=seconds;
            game.minutes=minutes;
            update_save(saves,game,Load_number,is_saved);//update saves array
            write_save(saves);
            read_save(saves);
            is_saved=1;
            system("cls");
        }
        // exiting the game
        else if(col==0)
        {
            exit(0);
        }
        // returmimg back to the main menu
        else if(col==-4)
        {
            score_winner=0;
            paused=1;
            break;
        }
        // showing the best move if it was easy single game
        else if(col==-5 && mode ==1 )
        {
            show_best_move=1;
            system("cls");
        }
        // playing the chosen/computed column
        else
        {
            system("cls");
            play(actions,col,h,w,board,playern,&curr_round,&max_round);


        }

        // calculating the scores pf this round
        score1=score(h,w,board,1);
        score2=score(h,w,board,2);

    }
    // Printing the game info after the game ends
    print_board(h,w,board);
    reset();
    red();
    printf("player 1 score:%d         ",score1);
    yellow();
    printf("player 2 score:%d\n",score2);
    red();
    printf("player 1 moves:%d         ",(curr_round/2));
    yellow();
    printf("player 2 moves:%d\n",((curr_round-1)/2));
    reset();
    timecalculate(h_i,m_i,s_i);

    // checking if he chose to go back to main menu or not
    if(!paused)
    {
        char trash[10];// an array to store the trash values inputed by the user

        // calculating the game result and asking the winner player to enter their name
        // if the game was multi player or single and the player wins
        if(score1>score2)
        {

            printf("Player %d is the winner \n",1);

            do
            {
                printf("Please enter your name : ");
                scanf("%s",name);
                gets(trash);
                name[strlen(name)]='\0';


            }
            while(!name_check(name));
            score_winner=score1;
        }
        else if(score2>score1 && mode==0)
        {
            printf("Player %d is the winner \n",2);
            do
            {
                printf("Please enter your name : ");
                scanf("%s",name);
                gets(trash);

            }
            while(!name_check(name));
            score_winner=score2;
        }
        else if(score1==score2)
        {
            printf("It is a tie\n");
            score_winner=0;
            printf("To go back to main menu press any key!!");
            getch();


        }
        else
        {
            printf("YOU LOSE\n");
            printf("To go back to main menu press any key!!");
            getch();
        }
    }
}

#endif // GAMELOOP_H_INCLUDED
