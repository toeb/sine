#include "Time.h"

#ifdef WIN32
#include <Windows.h>
namespace nspace{

static LARGE_INTEGER frequency;
class InitTime{
public:
  InitTime(){
     QueryPerformanceFrequency(&frequency);
  }
};
InitTime __initTime;

 nspace::Time nspace::systemTime(){
   LARGE_INTEGER time;
   QueryPerformanceCounter(&time);
   if(!frequency.QuadPart)return 0.0;
   return time.QuadPart /(double)frequency.QuadPart;
 }
}
#else
#include <sys/time.h>
namespace nspace{
 Time systemTime(){
     timeval t;
     gettimeofday(&t,0);
   Time result =  t.tv_sec+t.tv_usec /1000000.0;
   return result;
 }
}
#endif
namespace nspace{

 const nspace::Time __startUpTime=nspace::systemTime();

 nspace::Time startupTime(){
   return __startUpTime;
 }

 nspace::Time applicationTime(){
   Time result = nspace::systemTime()-__startUpTime;
   
   return result;
 }
}
