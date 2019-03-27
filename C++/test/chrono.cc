#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>

using std::cout; using std::endl; using std::cerr;
using namespace std::chrono;
using std::thread;


int main(){
    typedef duration<int> sec;
    typedef duration<int, std::milli> msec;
    typedef duration<int, std::ratio<1,1000*1000>> musec;
    typedef duration<double, std::nano> nsec;
    typedef duration<int, std::ratio<3600>> hr;
    typedef duration<int, std::ratio<3600*24>> day;
    typedef duration<int, std::ratio<3600*24*365>> yr;
    hr hr_aday(24);
    sec sec_aday(24*3600);
    msec ms_aday(24*3600*1000);
    cout << hr_aday.count() << ", " << sec_aday.count() << ", " << ms_aday.count() << endl;
    // sec sec_ahour(3600);
    // msec ms_ahour(sec_ahour);
    // hr hr_ahour(duration_cast<hr>(sec_ahour));
    hr hr_ahour(1);
    sec sec_ahour(hr_ahour);
    msec ms_ahour(sec_ahour);
    
    cout << hr_ahour.count() << ", " << sec_ahour.count() << ", " << ms_ahour.count() << endl;

    time_point<system_clock, yr> tp(time_point_cast<yr>(system_clock::now()));
    cout << tp.time_since_epoch().count() << endl;

    // time_point<system_clock, nsec> beg(time_point_cast<nsec>(system_clock::now()));
    steady_clock::time_point beg = steady_clock::now();
    // std::this_thread::sleep_for(sec(1));
    int i = 1000, j = 1;
    while(i > 0){
        j += i--;
    }
    // time_point<system_clock, nsec> end(time_point_cast<nsec>(system_clock::now()));
    steady_clock::time_point end = steady_clock::now();
    nsec dura = end-beg;
    cout << dura.count() << endl;

    time_point <system_clock,msec> tp_seconds (duration<int>(1));
    cout << tp_seconds.time_since_epoch().count() << endl;

    return 0;
}
