#include <iostream>

using namespace std;

int main(){
    int buf[32] = {2}; // buf[0]=2, 其余为0; 如果不写 = {2}, 则全部值不确定.
    for(int i = 0; i < 32; ++i){
        cout << buf[i];
    }
}