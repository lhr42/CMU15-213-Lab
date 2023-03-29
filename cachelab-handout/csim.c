#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
// #define DEBUG
char t[1000];
bool verbose;
int opt, s, E, b;
int S;

typedef struct Cacheline{
    bool valid;
    unsigned tag;
    unsigned lrucnt;
}Cacheline;
Cacheline ** cache;
int hitcnt, misscnt, evictioncnt;

void printhelp(){
    printf("help\n");
}

void initcache(int s, int E, int b){
    S = 1 << s;
    
    cache = (Cacheline**) malloc(sizeof(Cacheline*) * S);
    for(int i = 0; i < S; i++){
        cache[i] = (Cacheline*) malloc(sizeof(Cacheline) * E);
        for(int j = 0; j < E; j++){
            cache[i][j].valid = false;
            cache[i][j].lrucnt = 0;
        }
    }
}

void update_lrucnt(int x, int k){
    for(int j = 0; j < E; j++)
        if(cache[x][j].valid)
            cache[x][j].lrucnt++;
    cache[x][k].lrucnt = 0;
}

unsigned get(unsigned address, int b, int s){//get row coordinate of cache
    // unsigned res = 0;
    // address >>= b;
    // for(int i = 0; i < s; i++){
    //     res += (address & 1) << i;
    //     address >>= 1;
    // }
    address >>= b;
    unsigned mask = (1 << s) - 1;//least s bits are all 1
    return address & mask;
    // return res;
}
void insertcache(int i, int j, unsigned tag){
    cache[i][j].valid = true;
    cache[i][j].tag = tag;
    update_lrucnt(i, j);
}

void update_cacheline(unsigned x, unsigned tag){
    // bool isfull = true;
    for(int j = 0; j < E; j++){
        if(cache[x][j].valid && cache[x][j].tag == tag){
            ++hitcnt;
            update_lrucnt(x, j);
            if(verbose)
                printf(" hit");
            return;
        }
        // if(!cache[x][j].valid)
        //     isfull = false;
    }
    
    ++misscnt;
    if(verbose) printf(" miss");
    int leastused = 0;
    for(int j = 0; j < E; j++){
        if(!cache[x][j].valid){
            insertcache(x, j, tag);
            return;
        }
        else if(cache[x][j].lrucnt > cache[x][leastused].lrucnt)
            leastused = j;
    }
    ++evictioncnt;
    if(verbose) printf(" eviction");
    insertcache(x, leastused, tag);
}
void load(unsigned address,int size){
    unsigned x = get(address, b, s);
    unsigned tag = address >> (b + s);
    if(verbose) printf("L %x, %d", address, size);
    update_cacheline(x, tag);
    puts("");
}

void store(unsigned address, int size){
    if(verbose) printf("S %x, %d", address, size);
    unsigned x = get(address, b, s);
    unsigned tag = address >> (b + s);
    #ifdef DEBUG
    printf("x:%x tag:%x\n", x, tag);
    #endif
    update_cacheline(x, tag);
    puts("");
}

void modify(unsigned address, int size){
    if(verbose) printf("M %x, %d", address, size);
    unsigned x = get(address, b, s);
    unsigned tag = address >> (b + s);
    update_cacheline(x, tag);
    update_cacheline(x, tag);
    puts("");
}

int main(int argc, char *argv[])
{
    /*https://www.man7.org/linux/man-pages/man3/getopt.3.html
    optstring is a string containing the legitimate option
       characters.  A legitimate option character is any visible one
       byte ascii(7) character (for which isgraph(3) would return
       nonzero) that is not '-', ':', or ';'.  If such a character is
       followed by a colon, the option requires an argument, so getopt()
       places a pointer to the following text in the same argv-element,
       or the text of the following argv-element, in optarg.*/
    while((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1){
        switch(opt){
            case 'h':
                printhelp();
                break;
            case 'v':
                verbose = true;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strcpy(t, optarg);
                break;
            default:
                printhelp();
        }
    }
    
    // printf("s:%d E:%d b:%d t:%s\n", s, E, b, t);
    initcache(s, E, b);

    FILE * pFile;
    pFile = fopen(t, "r");
    char identifier;
    unsigned address;
    int size;
    while(fscanf(pFile, " %c %x,%d", &identifier, &address, &size) > 0){
        if(identifier == 'I')   continue;
        switch(identifier){
            case 'L':
                load(address, size);
                break;
            case 'S':
                store(address, size);
                break;
            case 'M':
                modify(address, size);
                break;
            default:    break;
        }
    }
    printSummary(hitcnt, misscnt, evictioncnt);
    
    for(int i = 0; i < S; i++)
        free(cache[i]);
    free(cache);
    fclose(pFile);
    return 0;
}
