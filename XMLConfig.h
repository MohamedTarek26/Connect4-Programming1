#ifndef XMLCONFIG_H_INCLUDED
#define XMLCONFIG_H_INCLUDED

int Height=9;
int Width=7;
int HighScores=10;

int convert_int(char* s,int len)
{

    for(int i=0;i<len;i++)
    {

        if(!isdigit(s[i]))
            {return 0;}
    }

    if(atoi(s)<=0 || atoi(s) >100)
    {
        printf("TOO BIG VALUE\n");
        return 0;
    }

    return atoi(s);
}
int getVal(char*s,char*s1,char*s2)
{
    if(strstr(s,s1) && strstr(s,s2))
    {
    int start = strstr(s, s1) + strlen(s1);

    int End =strstr(s, s2);
    if(End>=start)
    {
    char* substrs = malloc(End-start);
    strncpy(substrs, strstr(s, s1)+strlen(s1), End-start);
    if(convert_int(substrs,End-start))
    {return convert_int(substrs,End-start);}else{printf("ERROR: Invalid %s\n",s1);return 0;}


    return 1;
    }
    else
    {
        printf("ERROR: Couldn't Find %s\n",s1);
        return 0;
    }
    }
    else
    {
        printf("ERROR: Couldn't Find %s\n",s1);
        return 0;
    }

}

int ValidateXML(char*s)
{
    printf("I went here %s\n",s);
     if(strstr(s,"<Configuration>") && strstr(s,"</Configuration>"))
 {
    int start = strstr(s, "<Configuration>") + strlen("<Configuration>");
    int End =strstr(s, "</Configuration>");

    if(End-start >=0)
    {
    char* substrC = malloc(End-start);
    strncpy(substrC, strstr(s,"<Configuration>")+strlen("<Configuration>"),End-start);

    int h=getVal(substrC,"<Height>","</Height>");
    int w=getVal(substrC,"<Width>","</Width>");
    int hs=getVal(substrC,"<HighScores>","</HighScores>");

    if(!h || !w || !hs)
    {
        printf("Invalid XML\n");
        return 0;
    }
    if (h<4 || w<4)
    {
        printf("Too small dimensions\n");
        return 0;
    }
    Height=h;
    Width=w;
    HighScores=hs;

    free(substrC);
    }
    else
    {
        printf("ERROR: Couldn't Find Configuration\n");
        return 0;
    }
 }
 else
 {
     printf("ERROR: Couldn't Find Configuration\n");
     return 0;
 }
 return 1;
}
void Load_Config()
{
    FILE* fp;
 int b=1;
 char s[2048];
 fp = fopen("config.xml", "r");

 if ( fp == NULL ){ b=0;printf("File error, can't read! \n");}
 else
 {

 do
 {
 char ch=fgetc(fp);
 if(isgraph(ch))
 {
     strncat(s, &ch, 1);
 }
 }while( !feof(fp) );
 fclose(fp);
 }
 bool tamam=ValidateXML(s);
if (!b || !tamam)
{
for(int i=0;i<3;i++){
    printf("Enter a path to a valid Configuration file : \n");
    int b=1;
    char path[100];
    scanf("%s",path);
    FILE* fp;
    char ss[2048]=" ";
    fp = fopen(path, "r");
    if ( fp == NULL ){ b=0;printf("File error, can't read! \n");}
    else
    {

    do
    {
    char ch=fgetc(fp);
    if(isgraph(ch))
    {
        strncat(ss, &ch, 1);
    }
    }while( !feof(fp) );
    fclose(fp);
 }
 tamam=ValidateXML(ss);
    if(b && tamam)
    {
        break;
    }
}

}

    if(!b||!tamam)
    {
        printf("Then we use default values\nwidth=7\nheight=9\nhighscores=10\n");
    }
    else
   {
       printf("Values are:\nwidth=%d\nheight=%d\nhighscores=%d\n",Width,Height,HighScores);
   }
     printf("Press Any Key to Continue\n");
getch();
}
#endif // XMLCONFIG_H_INCLUDED
