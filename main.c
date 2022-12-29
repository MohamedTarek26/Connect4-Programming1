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
#include "save_load.h"
void main_menu(game_t* saves,player_t* topscores)
{
        int check_main_menu;
    int checking_input_menu=1;
    printf("Welcome to connect four\n");
    while(checking_input_menu)
    {
    checking_input_menu=0;
    printf("To start a new single player game enter 1\n");
    printf("To start a new multiplayer player game enter 2\n");
    printf("To load a previous game enter 3\n");
    printf("To display the top players enter 4\n");
    printf("To exit press 5\n");
    printf("please enter a choice:");


    check_main_menu=integercheck();


    system("cls");
    int ticks;
    switch (check_main_menu)
    {
        case 1:
            ticks=clock();
            start_time=((int)ticks / CLOCKS_PER_SEC);
            end_time=0;
            game_loop(Height,Width,0,0,saves);
            system("cls");
            break;
        case 2:
            ticks;
            ticks=clock();
            start_time=((int)ticks / CLOCKS_PER_SEC);
            end_time=0;
            game_loop(Height,Width,1,0,saves);
            system("cls");
            break;
        case 3:
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
            int L;
            L=integercheck();

            while(L<=0 || L>3 || L>n_games)
            {
                printf("enter a valid load\n");
                scanf("%d",&L);
            }
            game_loop(saves[L].boardrows,saves[L].boardcolumns,saves[L].mode,L,saves);
            printf("Loading a saved game");
            system("cls");
            break ;
        case 4:
            printf("Displaying top players\n");
            print_highscores(topscores,HighScores);
            system("cls");

            break;
        case 5:
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

    Load_Config();    //Loads data from xml


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

    /*for main menu
    1.single player  game_loop(Height,Width,0,0,saves)
    2.multiplayer player  game_loop(Height,Width,1,0,saves)
    3.loaded game player  game_loop(saves[L].boardrows,saves[L].boardcolumns,saves[L].mode,L,saves)
    4.High Scores print_highscores(topscores,HighScores)
    */

    while(true)
    {
    main_menu(saves,topscores);
    if(score_winner!=0)//after each game loop we save the score and name of the winner if there is a winner
        {
            char* s=name;
            int sc=score_winner;
            update_highscores(s,sc,topscores);//update highscores array
            write_highscores(topscores);//writes new highscore data
            print_highscores(topscores,HighScores);//print rankings
        }
    }
    system("cls");


    return 0;
}
