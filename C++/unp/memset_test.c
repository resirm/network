#include <stdio.h>
#include <string.h>

#define LEN 10

int test(){
    int c = 0x01020304; // for little-endian, result would be 4, for big-endian, result would be 1.
    char buf[LEN];
    memset((void *)buf, c, LEN);
    int i = 0;
    for(; i < LEN; ++i){
        printf("%d\n", buf[i]);
    }
}

int main(){
    test();
    return 0;
}