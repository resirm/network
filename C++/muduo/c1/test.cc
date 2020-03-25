#include <iostream>
#include <memory>
using namespace std;

class Foo{

};

int main(){
    shared_ptr<Foo> *p = new shared_ptr<Foo>(new Foo); // WRONG semantic
}