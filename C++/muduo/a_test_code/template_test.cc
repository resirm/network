#include <iostream>

using namespace std;

template<typename T>
void test(T arg){
    cout << arg << endl;
}

template
void test(int arg);