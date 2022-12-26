#ifndef FUCTRYING_H_INCLUDED
#define FUCTRYING_H_INCLUDED
#define MAXSIZE 1000

typedef struct {
int score;
int moves;
char name[10];
}players;
void passingstructtrying(players player1,players player2)
{
    printf("compiled sucessfuly");
}


bool checkvalid(int x,int y,char connect[][y],int col,char player)
{
    int i=x-1,j=col-1;
    if(j>=0&&j<y)
    {
    while(i>=0)
    {
        if(connect[i][j]=='-')
        {
            connect[i][j]=player;
            return true;
        }
        else
            i--;
    }
    printf("Enter an empty column!!!\n");
    return false;
    }
    else
    {
        printf("Enter a valid column!!!\n");
        return false;
    }
}

bool checkvalidcompu(int x,int y,char connect[][y],int col,char player)
{
    int i=x-1,j=col-1;
    if(j>=0&&j<y)
    {
    while(i>=0)
    {
        if(connect[i][j]=='-')
        {
            connect[i][j]=player;
            return true;
        }
        else
            i--;
    }
    return false;
    }
    else
    {
        return false;
    }
}

void printing(int x,int y, char connect[][y],int ordercolor)
{
    //clrscr();
     bool flagprint=true;
     blue();
    for(int printingnumber=0;printingnumber<y;printingnumber++)
    {
        printf("   %d  ",printingnumber+1);

      /*
        if(alphabet<26)
            printf("   %c  ",65+alphabet);
        else if (alphabet<52)
            printf("   %c  ",71+alphabet);
        else
        {
            flagprint=false;
            printf("Out of characters!!");
        }
      */

    }
    printf("\n");
    if (flagprint)
    {
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
            if (connect[i][j]=='x')
            {
                printf("%c  ",186);
                red();
                printf("%c  ",connect[i][j]);
                blue();
                //system("COLOR 01");
            }
            else if (connect[i][j]=='o')
            {
                printf("%c  ",186);
                yellow();
                printf("%c  ",connect[i][j]);
                blue();
            }
            else
                printf("%c  %c  ",186,connect[i][j]);
        }
        printf("%c",186);
        printf("\n");
        for(int k=0;k<6*y+1;k++)
            putchar(205);
        printf("\n");

    }
    }
    reset();
    red();
    printf(" player 1 score:%d         ",0);
    yellow();
    printf("player 2 score:%d\n",0);
    red();
    printf(" player 1 moves:%d         ",0);
    yellow();
    printf("player 2 moves:%d\n",0);
    reset();
    timecalc();
}
void playingmulti(int x,int y,char connect[][y],int * ptrorder)
{
    char player;
    int col,order;
    bool check;
    order=*ptrorder;
    if(order%2!=0)
    {
        player='x';
        printf("Player one choose column:");
        col=integercheck(x,y,connect,order);
        //scanf("%d",&col);
        system("cls");
        check=checkvalid(x,y,connect,col,player);
        if(check)
            *ptrorder=order+1;
    }
    else
    {
        player='o';
        printf("Player two choose column:");
        col=integercheck(x,y,connect,order);
        //scanf("%d",&col);
        system("cls");
        check=checkvalid(x,y,connect,col,player);
        if(check)
            *ptrorder=order+1;
    }


}
int random_col_selection(int x,int y,char connect[][y])
{
    int col,lower=1,upper;
    //scanf("%d*%d",&m,&n);
    upper=y;
    //srand(time(NULL));
    //printf("%d\n",time(NULL));
    //printf("%d\n",rand());
    //printf("%d\n",);
    col = rand()%(upper-lower+1)+lower;
    //printf("%d\n",col);
    return col;
}
void playingsingle(int x,int y,char connect[][y],int * ptrorder)
{
    bool checkcomp=false,check;
    char player;
    int col,order;
    order=*ptrorder;
    if(order%2!=0)
    {
        player='x';
        printf("Player one choose column:");
        col=integercheck(x,y,connect,order);
        //scanf("%d",&col);
        system("cls");
        check=checkvalid(x,y,connect,col,player);
        if(check)
            *ptrorder=order+1;
    }
    else
    {
        player='o';

        /*printf("Player two choose column:");
        scanf("%d",&col);*/
        while(!checkcomp)
        {
         col=random_col_selection(x,y,connect);
         system("cls");
         checkcomp=checkvalidcompu(x,y,connect,col,player);
        }

        *ptrorder=order+1;
    }

}

void red (){printf("\033[1;31m");}
void blue(){printf("\033[0;34m");}
void yellow(){printf("\033[1;33m");}
void reset (){printf("\033[0m");}





int integercheck(int x,int y,char connect[][y],int order)
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
  while (isspace(buffer[i])) i++;

  // get the length of the string
  int length = strlen(buffer);

  // if the entire string was just whitespace characters ("a blank string")
  // we'll have reached the end of the string and we can return false as the
  // string did not contain an integer
  if (length == i) checkint= false;

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
    if (!isdigit(buffer[i])) checkint= false;
  }

  // loop through characters until we reach the end of the string or a trailing
  // whitespace character
  while (i < length && !isspace(buffer[i]))
  {
    // if we encounter anything that is not a digit, we do not have a valid int
    // in the string
    if (!isdigit(buffer[i])) checkint =false;

    // store the next character into the buffer, advance both indexes
    integer_buffer[integer_chars] = buffer[i];
    integer_chars++;
    i++;
  }

  // put a null terminator onto the end of the buffer to make it a proper string
  integer_buffer[integer_chars] = '\0';

  // loop through any trailing whitespace characters
  while (isspace(buffer[i])) i++;

  // if after doing so, we are NOT at the end of the string, then the string
  // does not contain a valid integer
  if (buffer[i] != '\0') checkint= false;

  // atoi converts the string representation of our integer to an int type
  // value in C, and we de-reference integer to "return" the value via a pointer
  integer = atoi(integer_buffer);

    // if the input was not a valid integer, tell the user this
    if (!checkint)
    {
        system("cls");
      printf("Enter an integer value!\n");
      printing(x,y,connect,order);
      if(order%2!=0)
        printf("player one choose column:");
      else
        printf("player two choose column:");

    }

      //end of fun

  } while (!checkint);


  return integer;
}

#endif // FUCTRYING_H_INCLUDED
