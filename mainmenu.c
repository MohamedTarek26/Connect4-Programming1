#include <stdio.h>
#include <stdlib.h>


int main()
{
    char check_main_menu;
    int checking_input_menu=1;
    printf("Welcome to connect four\n");
    while(checking_input_menu)
    {
    checking_input_menu=0;
    printf("To start a new game enter 1\n");
    printf("To load a previous game enter 2\n");
    printf("To display the top players enter 3\n");
    printf("To exit press 4\n");
    printf("please enter a choice:");
    scanf("%c",&check_main_menu);
    system("cls");
    switch (check_main_menu)
    {
        case '1':
            printf("Starting a new game function");
            break;
        case '2':
            printf("Loading a saved game");
            break ;
        case '3':
            printf("Displaying top players");
            break;
        case '4':
            printf("Exiting the game");
            break;
        default :
            printf("Enter a valid choice please!!\n");
            checking_input_menu=1;

    }

    }

    return 0;
}
