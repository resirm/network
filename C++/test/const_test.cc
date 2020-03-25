#include <iostream>

using namespace std;

void test(int*){
    cout << "test" << endl;
}

int main(){
    int a = 3;
    const int& cra = a;
    int &ra = a;
    test(const_cast<int*>(&cra));
    return 0;
}