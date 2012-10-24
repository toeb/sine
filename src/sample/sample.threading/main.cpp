#include <thread>
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;
int main(int argc, char ** argv){

  bool iterate = true;


  auto p = high_resolution_clock::period();
  std::cout << p.num<<"/"<<p.den<<endl;
  p = system_clock::period();
  std::cout << p.num<<"/"<<p.den<<endl;
  p = steady_clock::period();
  std::cout << p.num<<"/"<<p.den<<endl;


  thread t1([&iterate](){ while(iterate) ; });

  thread t2([&iterate](){ while(iterate) ; });
  thread t3([&iterate](){ while(iterate) ; });
  thread t4([&iterate](){ while(iterate) ; });
  thread t5([&iterate](){ while(iterate) ; });
  thread t6([&iterate](){ while(iterate) ; });
  thread t7([&iterate](){ while(iterate) ; });
  thread t8([&iterate](){ while(iterate) ; });


  char c;
  // cin.get(c);
  this_thread::sleep_for(chrono::seconds(2));
  iterate = false;


  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
  return 0;
}