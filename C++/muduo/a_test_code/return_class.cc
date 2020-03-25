#include <iostream>

using namespace std;

class A{
public:
    A(int a = 0):a_(a){}
    static A invalid(){ return A(); }
    void print(){ cout << a_ << endl; }
private:
    int a_;
};

int main(){
    auto a = A::invalid();
    a.print();
    A a2 = A(1);
    a2.print();
    A a3{};
}