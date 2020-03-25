#include <stdio.h>

void test(){
    unsigned int ip = 0x9003a8c0;
    const unsigned char* p = &ip;
    char rst[16];
    snprintf(rst, sizeof(rst), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    int i = 0;
    for( ; i < sizeof(rst); ++i){
        printf("%c", rst[i]);
    }
}

int main(){
    test();
    return 0;
}