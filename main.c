#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*
int main()
{
 int n,check=1,digits=0,l;
 scanf("%d",&n);
 int x=n,z=n;
 while(x)
 {
     x=x/10;
     digits++;
 }
int y=digits;
int num[digits];
for (int i=0;y>0;i++,y--)
{
    l=pow(10,y-1);
    num[i]=z/l;
    z=z%l;


}
 for (int i=0;i<digits;i++)
 {
     if(num[i]==num[digits-1-i])
     {
         continue;
     }
     else
     {
         check=0;
         break;
     }
 }
 if (check)
 {

     printf("%d is a palindrome number",n);
 }
 else
 {
     printf("%d is not a palindrome number",n);
 }
    return 0;
} */
/* #include <stdio.h>
int main() {
  int n, reversed = 0, remainder, original;
    printf("Enter an integer: ");
    scanf("%d", &n);
    original = n;

    // reversed integer is stored in reversed variable
    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }

    // palindrome if orignal and reversed are equal
    if (original == reversed)
        printf("%d is a palindrome.", original);
    else
        printf("%d is not a palindrome.", original);

    return 0;
}
*/
int main ()
{
    int x,y,z,rem;
    scanf("%d",&x);
    y=x;
    z=0;
    while (y)
    {
        rem=y%10;
        z=z*10+rem;
        y/=10;
    }
    if (x==z)
    printf("PALINDROME YA ME3ALEM");
    else
    printf("KHERHA FE 8ERHA");
    return 0;
}


