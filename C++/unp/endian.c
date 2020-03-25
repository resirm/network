#include <stdio.h>

void getEndian(){
    union {
        short s;
        char c[sizeof(short)];
    } un;
    un.s = 0x0102;
    if(sizeof(short) == 2){
        if(un.c[0] == 0x01 && un.c[1] == 0x02){
            printf("This computer is big-endian.\n");
        }else if(un.c[0] == 0x02 && un.c[1] == 0x01){
            printf("This computer is little-endian.\n");
        }else{
            printf("This computer is unknown-endian.\n");
        }
    }else{
        printf("sizeof short is: %lld", sizeof(short));
    }
}

int main(){
    getEndian();
    return 0;
}