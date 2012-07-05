#include "Timer.h"
#include <iostream>
using namespace IBDS;


Timer::Timer(Time timeout, bool repeat):_timeout(timeout), _repeat(repeat), _fire(true){

}

bool Timer::initializeObject(){
  _targetTime = currentTime()+_timeout;
  return true;
}
void Timer::restart(){
  stop();
  start();
}
void Timer::start(){
  if(isRunning())return;
  // if timer is not already running set to a time in the futer set it to a time in the future
  _targetTime = currentTime()+_timeout;
  _fire = true;
}
void Timer::stop(){
  //set target time to zero
  _targetTime = 0;
  _fire = false;
}
bool Timer::isRunning()const{
  // return true as long target time is ahead of system time
  Time systemTime = currentTime();
  if(_targetTime > systemTime)return true;
  return false;
}

void Timer::afterStep(Time t, Time h){
  //solong target time is not reached return.
 Time systemTime = currentTime();
// std:: cout << "tsim" <<(long)_targetTime << "\ntsys" << (long)systemTime<<"\n";

 //nothing to do if target time is not reached.
 if(_targetTime >= systemTime) return;

 // call timeout
 if(_fire){
  timeout(systemTime, t);
  _fire = false;

 }
 // if repeat then start timer again
 if(_repeat){
   start();
 }
}
  

