#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std; // For time_t, time and ctime;

int main(){
    time_t now = time(0);
    auto t = ctime(&now);
    cout << t << endl;
    this_thread::sleep_for(chrono::seconds(1));
    now = time(0);
    t = ctime(&now);
    cout << t << endl;
}
