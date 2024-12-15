#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double rnd(double x){double p = (x-floor(x) < 0.5)?0:1;return floor(x)+p;}
int main(){FILE *f;f=fopen("res.txt", "w");double n=(double)2*sin(1.5*3.14)+5*sin(1.57);fprintf(f,"%f",n);fclose(f);return 0;}