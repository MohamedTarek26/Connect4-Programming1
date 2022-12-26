#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include "fuctrying.h"
#include "timecounter.h"





int main()
{

    int x,y,h,checking_s_or_m;
    FILE *f1=NULL;
    f1=fopen("configuration.txt","r");
    if(f1!=NULL)
    {
     fscanf(f1,"%d*%d\n%d",&y,&x,&h);
    //system("cls");
    fclose(f1);
    }
    else
        printf("Error file not found\n");

    //printf("%d %d\n%d\n",n,m,h);
    //x=2*n;
    //y=2*m+1;
   // x=n;
   // y=m;
    printf("for single player enter 1 and for multiplayer enter 2:");
    scanf("%d",&checking_s_or_m);
    system("cls");
    char connect[x][y];
    int order =1;
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
        {
           connect[i][j]='-';
        }
    }
    int ticks;
    ticks=clock();
    start_time=((int)ticks / CLOCKS_PER_SEC);
    printing(x,y,connect,order);
    // order=1;
    int *ptrorder=&order;
    //printf("%d\n",*ptrorder+1);
    srand(time(NULL));
    while(order<=(x*y))
    {
        if (checking_s_or_m==1)
           playingsingle(x,y,connect,ptrorder);
        else
           playingmulti(x,y,connect,ptrorder);
        //printf("%d\n",order);
        printing(x,y,connect,order);
        //timecalc();
    }
    printf("End of the game");




    return 0;
}
