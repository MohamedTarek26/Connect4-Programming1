#ifndef TIMECOUNTER_H_INCLUDED
#define TIMECOUNTER_H_INCLUDED
int start_time=0,end_time=0;
void timecalc()
{
    int hours,minutes,seconds;

    int ticks;
    ticks=clock();
    seconds=((int)ticks / CLOCKS_PER_SEC)-start_time+end_time;
    // calculating how many hours are in those seconds
    hours=(seconds-seconds%3600)/(3600);

    // calculatintg the remaining minutes
    // despite the minutes calculated before in the hours
    minutes=(seconds-hours*60*60)/60;

    // calculating the rest of seconds
    seconds%=60;
    printf(" Time passed %d:%d:%d\n",hours,minutes,seconds);
}


#endif // TIMECOUNTER_H_INCLUDED
