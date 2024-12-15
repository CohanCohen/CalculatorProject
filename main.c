#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



double eval(char str[]){
	double res;
	char str1[300] = "#include<stdio.h>\n#include<stdlib.h>\n#include<math.h>\ndouble rnd(double x){double p = (x-floor(x) < 0.5)?0:1;return floor(x)+p;}\nint main(){FILE *f;f=fopen(\"res.txt\", \"w\");double n=(double)";
	strcat(str1, str);
	char str2[60] = ";fprintf(f,\"%%f\",n);fclose(f);return 0;}";
	strcat(str1, str2);
	
	FILE *f;
	f = fopen("res.c", "w");
	fprintf(f, str1);
	fclose(f);
	
	system(".\\tcc\\tcc res.c -o m.exe");
	system(".\\m");
	
	FILE *fres;
	fres = fopen("res.txt", "r");
	fscanf(f, "%lf", &res);
	fclose(f);
	
	return res;
}

int findFirstIns(char *string, char *key){
    
	int len_string = strlen(string);
	int len_key = strlen(key);
	char win[len_key + 1];
	int i, j;
	for (i = 0; i < len_string - len_key + 1; i++){
		for (j = 0; j < len_key; j++){
			win[j] = *(string + i + j);
		}
		//win[j + 1] = NULL;
		if (strcmp(win, key) == 0){
			return i;
		}
	}
	return -1;
}
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
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
double evalf(char *fcontread, double val){
    FILE *fptrFunc;
    char *fname = (char *) malloc(500*sizeof("c"));
    char *fcont = (char *) malloc(500*sizeof("c"));
    char *nfcont = (char *) malloc(500*sizeof("c"));
    char *fans = (char *) malloc(500*sizeof("c"));
    fptrFunc = fopen(fcontread, "r");fscanf(fptrFunc, "%s", fcont);fclose(fptrFunc);
    sprintf(fans, "%lf", val);
    nfcont = str_replace(fcont, "z", fans);
    return eval(nfcont);
}
double derivative(char* fcontread, double val){
    double a = evalf(fcontread, val + 0.00001);
    double b = evalf(fcontread, val);
    return (double)100000 * (a - b);
}
int norm(char *string, double arr[100]){
	int i,j;
	char *nstr = (char *)malloc(500*sizeof("c"));
	char *nstr2 = (char *)malloc(500*sizeof("c"));
    char *nstr3 = (char *)malloc(500 * sizeof("c"));
	for (i = 0; i < 10; i++){
        sprintf(nstr, "%c%d", 97+i/10, i % 10+1);
        sprintf(nstr2, "%lf", arr[i]);
        nstr3 = str_replace(string, nstr, nstr2);
        strcpy(string, nstr3);
		
	}
	ins_star(string);
	return 1;
}
int printtable(double array[]){
	int i,j;
	printf("  \t");
	for (i=0; i<10; i++){
		printf("%d        \t|", i+1);
	}
	printf("\n");
	for (i=0; i<10; i++){
		printf("%c|\t", 65+i);
		for (j=0; j<10; j++){
			printf("%lf\t|", array[i*10 + j]);
		}
		printf("\n");
	}
	return 1;
}
void main(){
    int i,j;
	double array[100];
	for (i = 0; i < 100; i++){
		array[i] = 0;
	}
    system("cls");
	FILE *fptrWrite;
	FILE *fptrRead;
    FILE *fptrFunc;
    FILE *fptrDOC;
	char *command = (char *) malloc(500*sizeof("c"));
	char *sub_command = (char *) malloc(500*sizeof("c"));
	char *sub_sub_command = (char *) malloc(500*sizeof("c"));
	char *file_cont_writ = (char *) malloc(500*sizeof("c"));
    char *file_cont_read = (char *) malloc(5000*sizeof("c"));
	char *ssc2 = (char *) malloc(500*sizeof("c"));
	char *sub_command2 = (char *) malloc(500*sizeof("c"));
    char *fname = (char *) malloc(500*sizeof("c"));
    char *fcont = (char *) malloc(500*sizeof("c"));
    char *nfcont = (char *) malloc(500*sizeof("c"));
    char *fcontread = (char *) malloc(500*sizeof("c"));
    char *fans = (char *) malloc(500*sizeof("c"));
    char *temp1 = (char *) malloc(500*sizeof("c"));
    char *docstirng = (char *) malloc(5000 * sizeof("c"));
    char *tok;
    double temp;
	int a,b, cont = 1;
	printf("Enter command : ");
	scanf("%s %s %s", command, sub_command, sub_sub_command);
	
	while (strcmp(command, "exit") != 0){
		//printf(">>> ");
		i = 0;
		cont = 1;
		if (strcmp(command, "eval") == 0){
            norm(sub_command, array);
			sub_command2 = strlwr(sub_command);
			printf("\n%lf\n", eval(sub_command2));
		}
		else if(strcmp(command, "savetable") == 0){
			fptrWrite = fopen(sub_command, "w");
			for (i = 0; i < 10; i++){
				for (j = 0; j < 10; j++){
					sprintf(file_cont_writ, "%lf", array[i * 10 + j]);
					fprintf(fptrWrite, "%s ", file_cont_writ);
				}
			}
			fclose(fptrWrite);
			printf("\nsaved.\n");
		}

		else if(strcmp(command, "importtable") == 0){
            fptrRead = fopen(sub_command, "r");
            fscanf(fptrRead, "%s", file_cont_read);
            fclose(fptrRead);
            tok = strtok(file_cont_read, " ");
            j = 0;
            while (tok != NULL){
                sscanf(tok, "%lf", &array[j]);
                j ++;
                tok = strtok(NULL, " ");
            }


		}
		else if(strcmp(command, "set") == 0){
			sub_command2 = strlwr(sub_command);
			a = sub_command2[0] - 97;if (a > 10){printf("\ninvalid coordinate.\n");a = 0;cont = 0;}
			sscanf(sub_command2 + 1, "%d", &b);
            if (b > 10 && cont == 1){printf("\ninvalid coordinate.\n");b = 0;cont = 0;}
            if (cont == 1){
			norm(sub_sub_command, array);
			ssc2 = strlwr(sub_sub_command);
			array[a*100 + b - 1] = eval(ssc2);
			printf("\nvalue set.\n");}
		}
		else if(strcmp(command, "printtable") == 0){
			printf("\n");
			printtable(array);
		}
        else if(strcmp(command, "help") == 0){
            fptrDOC = fopen("doc.txt", "r");
            fread(docstirng, 6000, 1, fptrDOC);
            fclose(fptrDOC);
            printf("\n%s\n", docstirng);

        }
        else if (strcmp(command, "let") == 0){
            /*This portion gets a function from the user and saves it.
            after that the function is able to be called and evaluated
            with different inputs. e.g. let f 2sin(z)*/
            sprintf(fname, "%s.txt", sub_command);
            norm(sub_sub_command, array);
            fptrFunc = fopen(fname, "w");fprintf(fptrFunc, "%s", sub_sub_command);fclose(fptrFunc);
            printf("done. note : this version only supports one variable functions with variable z.\n");

        }
        else if (strcmp(command, "evalf") == 0){// eval$function f 14
            //sprintf(fname, "%s.txt", sub_command);
            //sprintf(fcontread, "%s.txt", sub_command);
            strcpy(fcontread, sub_command); strcat(fcontread, ".txt");
            fptrFunc = fopen(fcontread, "r");fscanf(fptrFunc, "%s", fcont);fclose(fptrFunc);
            sprintf(fans, "%lf", eval(sub_sub_command));
            nfcont = str_replace(fcont, "z", fans);
            printf(" \n%lf\n", eval(nfcont));
    
        }
        else if (strcmp(command, "drvt") == 0){
            strcpy(fcontread, sub_command); strcat(fcontread, ".txt");
            temp = eval(sub_sub_command);
            printf("\n%lf\n", derivative(fcontread, temp));
        }
        printf(">>> ");
		scanf("%s %s %s", command, sub_command, sub_sub_command);
	}
    
}