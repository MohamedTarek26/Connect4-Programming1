#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "gameloop.h"
#include "highscores.h"
#include "XMLConfig.h"

int g=1;

void main_menu(game_t* saves,player_t* topscores)
{
    int check_main_menu;
    int checking_input_menu=1;
    printf("Welcome to connect four\n");
    read_save(saves);

    while(checking_input_menu)
    {
    checking_input_menu=0;
    printf("To start a new single player easy game enter 1\n");
    printf("To start a new single player hard game enter 2\n");
    printf("To start a new multiplayer player game enter 3\n");
    printf("To load a previous game enter 4\n");
    printf("To display the top players enter 5\n");
    printf("To exit press 6\n");
    printf("please enter a choice:");


    check_main_menu=integercheck();


    system("cls");
    int ticks;
    g=1;
    switch (check_main_menu)
    {

        case 1:
            ticks=clock();
            start_time=((int)ticks / CLOCKS_PER_SEC);
            end_time=0;
            game_loop(my_configs.Height,my_configs.Width,1,0,saves);
            system("cls");
            break;

        case 2:
            ticks=clock();
            start_time=((int)ticks / CLOCKS_PER_SEC);
            end_time=0;
            game_loop(my_configs.Height,my_configs.Width,2,0,saves);
            system("cls");
            break;

        case 3:
            ticks;
            ticks=clock();
            start_time=((int)ticks / CLOCKS_PER_SEC);
            end_time=0;
            game_loop(my_configs.Height,my_configs.Width,0,0,saves);
            system("cls");
            break;

        case 4:
            ticks;
            ticks=clock();
            start_time=((int)ticks / CLOCKS_PER_SEC);
            end_time=0;

            printf("Enter Load number\n");

            if(n_games==0)
            {
                printf("There is't any loaded game\n");
                printf("Press Any Key to Continue\n");
                getch();
                system("cls");
                continue;
            }

            for(int k=1;k<=n_games;k++)
            {
                printf("%d: game %d\n",k,k);
            }
            printf("To go back press 0\n");

            int L;


            do
            {
                L=integercheck();
                printf("enter a valid load\n");
            }while(L<0 || L>3 || L>n_games);
            system("cls");
            if(!L)
            {
                break;
            }
            game_loop(saves[L].boardrows,saves[L].boardcolumns,saves[L].mode,L,saves);
            printf("Loading a saved game");
            system("cls");
            break ;

        case 5:
            g=0;
            printf("Displaying top players\n");
            print_highscores(topscores,my_configs.HighScores);
            system("cls");

            break;

        case 6:
            printf("Exiting the game");
            exit(0);
            break;

        default :
            printf("Enter a valid choice please!!\n");
            checking_input_menu=1;

    }

    }
}


int main()
{
    //intializes default values for configuration before reading the xml

    Load_Config();    //Loads data from xml if any


    player_t  topscores[MAX_HIGH_SCORES]; //defines topscores array

    game_t saves[5]; //defines saves array

    for(int i=0;i<MAX_HIGH_SCORES;i++) //intializes topscores array
    {
        topscores[i].score=0;
        strcpy(topscores[i].name,"-");
    }


    read_save(saves);//read saves array from save.bin
    read_highscores(topscores);//read scores array from HighScores.bin
    system("cls"); // for clearing


    while(true)
    {
    main_menu(saves,topscores);
    if(score_winner!=0 && g)//after each game loop we save the score and name of the winner if there is a winner
        {
            char* s=name;
            int sc=score_winner;
            update_highscores(s,sc,topscores);//update highscores array
            write_highscores(topscores);//writes new highscore data
            print_highscores(topscores,my_configs.HighScores);//print rankings
        }
        system("cls");
    }



    return 0;
}
