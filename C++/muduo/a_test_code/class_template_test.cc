#include <iostream>
#include <string>

using namespace std;

template<typename T1, typename T2>
class A{
public:
    void operator()(T1&& t1, T2&& t2) const{
        cout << t1 << ", " << t2 << endl;
    }
};

int main(){
    A<int, string> a1;
    a1(2, string("aaa"));
    int i = 3;
    string s("ohhh");
    // a1(i, s);   // error!
    A<int&, string&> a2;
    a2(i, s);
}