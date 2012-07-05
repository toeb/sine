#include "Time.h"

#ifdef WIN32
#include <Windows.h>
namespace IBDS{

static LARGE_INTEGER frequency;
class InitTime{
public:
  InitTime(){
     QueryPerformanceFrequency(&frequency);
  }
};
InitTime __initTime;

 IBDS::Time IBDS::currentTime(){
   LARGE_INTEGER time;
   QueryPerformanceCounter(&time);
   return time.QuadPart /(double)frequency.QuadPart;
 }
}
#elif
 void currentTime(Time & t){
   cerr<< "no timing available" << endl;
 }
#endif
