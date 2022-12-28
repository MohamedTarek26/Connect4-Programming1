#ifndef TIME_COUNTER_H_INCLUDED
#define TIME_COUNTER_H_INCLUDED
int seconds,minutes,hours;
int start_time=0,end_time=0;
void timecalculate(int hours_i,int minutes_i,int seconds_i)
{
    int ticks;
    ticks=clock();
    seconds=(((int)ticks / CLOCKS_PER_SEC))+seconds_i-start_time+end_time;
    // calculating how many hours are in those seconds
    hours=((seconds-seconds%3600)/(3600))+hours_i;

    // calculatintg the remaining minutes
    // despite the minutes calculated before in the hours
    minutes=((seconds-hours*60*60)/60)+minutes_i;

    // calculating the rest of seconds
    seconds%=60;
    printf(" Time passed %d:%d:%d\n",hours,minutes,seconds);

}


#endif // TIME_COUNTER_H_INCLUDED
