#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int isnumber(char c){
    if (48<=c && c<=57){
        return 1;
    }
    return 0;
}
int isspec(char c){
    if (33<=c && c <= 47 && c != 40 && c != 41){
        return 1;
    }
    return 0;
}
void insert(char *strA, char* strB, int x, char* strC){
    strncpy(strC, strA, x);
    *(strC + x) = '\0';
    strcat(strC, strB);
    strcat(strC, strA + x);
}
void ins_star(char *string){
    int len_string = strlen(string);
    int i;
    int k = len_string - 1;
    char *string2 = (char *) malloc(500 * sizeof("c"));
    for (i = 0; i < k; i++){
        if (isnumber(*(string + i)) + isnumber(*(string + i + 1)) == 1){
            if (*(string + i + 1)!= 41 && *(string + i)!=40 ){
                if (isspec(*(string + i)) + isspec(*(string + i + 1)) == 0){
                    insert(string, "*", i+1, string2);
                    strcpy(string, string2);
                    k++;}
            }
        }
    }
}
int main(){
    char a[300] = "2s(2.2-4/5)";
    ins_star(a);
    printf("%s", a);
}