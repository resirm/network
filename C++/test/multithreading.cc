#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
#include <chrono>

using std::cout; using std::endl; using std::cerr;
using std::thread;
using std::vector;
using namespace std::chrono;

class Task{
public:
    void operator()(int i){
        cout << "new thread: " << std::this_thread::get_id() << ", " << i*100 << endl;
    }
};

class tagNode
{
public:
    int a;
    int b;
    tagNode(){
        a = 1;
        b = 2;
    }
};

void func(tagNode &node)
{
    node.a = 10;
    node.b = 20;
}

void f()
{
    tagNode node;

    thread t(func, std::ref(node));
    t.join();
    // t.detach();

    cout << node.a << endl ;
    cout << node.b << endl ;
}

int main(){
    vector<thread*> vt;
    for(int i = 0; i < 10; ++i){
        Task task;
        auto t = new thread{task, i};
        vt.push_back(t);
        // cerr << "thread id: " << t->get_id() << "." << endl;
        // t.detach();
        // t.join();
    }
    
    std::for_each(vt.begin(), vt.end(), [](auto &c)->void{ c->detach(); delete c; });

    // f();
}