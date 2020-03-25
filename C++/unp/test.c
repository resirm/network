#include <stdio.h>
#include <string.h>

int main(){
    char a[] = "happy";
    char b[] = "not happy";
    printf("%s\n", a);
    int i;
    const char **p;
    p[0] = a;
    p[1] = b;
    p[2] = NULL;
    // for(i = 0; i < strlen(a); ++i){
    //     printf("%c ", a[i]);
    // }
    // printf("--");
    
    const char **idx;
    for(idx = p; *idx != NULL; idx++){
        printf("%s\n", *idx);
    }
    return 0;
}