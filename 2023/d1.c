#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

uint32_t p1(FILE *fp);
uint32_t p2(FILE *fp);
int sindex(char * str, char * subs, int offs);

typedef struct {
    char * str;
    int val;
} lookup_t;

lookup_t table[] = {
    {"one", 1},
    {"1", 1},
    {"two", 2},
    {"2", 2},
    {"three", 3},
    {"3", 3},
    {"four", 4},
    {"4", 4},
    {"five", 5},
    {"5", 5},
    {"six", 6},
    {"6", 6},
    {"seven", 7},
    {"7", 7},
    {"eight", 8},
    {"8", 8},
    {"nine", 9},
    {"9", 9},
};

int sindex(char * str, char * subs, int offs){
    char * locp = strstr(str, subs);
    if(locp != NULL){
        int loci = locp - str;
        return loci + offs;
    }
    return -1;
}

uint32_t p1(FILE *fp){
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    uint32_t total = 0;

    while((read = getline(&line, &len, fp)) != -1){
        char ds[3] = "\0";
        for(size_t i=0; i<read; i++){
            if(isdigit(line[i])){
                if(ds[0] == '\0'){
                    ds[0] = line[i];
                }
                ds[1] = line[i];
            }
        }
        total += atoi(ds);
    }
    if (line)
        free(line);
    return total;

}

uint32_t p2(FILE *fp){
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    uint32_t total = 0;

    while((read = getline(&line, &len, fp)) != -1){
        int ileft = -1;
        int iright = -1;
        int vleft = -1;
        int vright = -1;
        printf("%s", line);
        for(int i=0; i<18; i++){
            int slider = 0;
            int si;
            while((si = sindex(line + slider, table[i].str, slider)) != -1){
                printf("found %s at %d\n", table[i].str, si);
                if(ileft == -1){
                    ileft = si; 
                    iright = si;
                    vleft = table[i].val;
                    vright = table[i].val;
                }
                else if (si < ileft){
                    ileft = si;
                    vleft = table[i].val;
                }
                else if (si > iright){
                    iright = si;
                    vright = table[i].val;
                }
                slider += 1;
            }
        }
        printf("%d , %d\n", vleft, vright);
        printf("line val: %d\n", vleft * 10 + vright);
        total += vleft * 10 + vright;
    }
    if (line)
        free(line);
    return total;

}

int main(void){
    FILE * fp;

    fp = fopen("d1input.txt", "r");

    //uint32_t total = p1(fp);
    uint32_t total2 = p2(fp);

    printf("TOTAL: %u\n", total2);
    fclose(fp);
    exit(EXIT_SUCCESS);

}
