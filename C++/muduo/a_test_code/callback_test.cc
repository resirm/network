#include <iostream>
#include <functional>
#include <memory>
#include "..\muduo-master\muduo-master\muduo\base\WeakCallback.h"

using namespace std;

class A{
public:
    int& get(){
        cout << "get called: " << a_ << endl; 
        return a_;
    }
    void set(int a){
        a_ = a;
    }
    static void set2(A* obj, int a){
        obj->get() = a;
    }
    void remove(A* obj, int a){
        obj->get() = a;
        cout << "remove called: " << a << endl;
        // delete obj;
    }
    static void remove2(A* obj, int a){
        obj->get() = a;
        cout << "remove2 called: " << a << endl;
        // delete obj;
    }
private:
    int a_;
};

int main(){
    {
        using afunc = void(A::*)(int, A*);
        // afunc af = &A::remove;
        void(A::*af2)(A*, int) = &A::remove;
        // function<afunc> func2(af2);
        // shared_ptr<A> sp(new A, std::bind(func2, 666, placeholders::_1));
        shared_ptr<A> sp2(new A);
        auto wc = muduo::makeWeakCallback(sp2, &A::remove);
        auto wc2 = muduo::WeakCallback<A, A*, int>(sp2, &A::remove);
        // sp->set(45);
        auto pp = sp2.get();
        wc(pp, 666);
        wc2(pp, 778);
        auto fff = wc2.get();
        fff(sp2.get(), pp, 789);
        // std::function<void(A*)> f = std::bind(wc, 666, placeholders::_1);
        // f(sp2.get());
        shared_ptr<A> sp(new A, [&wc](A* a){return wc(std::move(a), 777);});
        shared_ptr<A> sp3(new A, [&sp2](A* a){return muduo::makeWeakCallback(sp2, &A::remove)(a, 787);});
        // shared_ptr<A> sp3(new A, std::bind(wc, 666, placeholders::_1));
        sp->set(555);
    }
    
    // A a;
    // function<void(int)> func1(std::bind(&A::set, &a, placeholders::_1));
    // func1(77);
    // a.get();
    
    // func2(a, 88);
    // a.get();
}