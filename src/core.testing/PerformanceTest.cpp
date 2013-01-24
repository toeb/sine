#include "PerformanceTest.h"

using namespace nspace;



void PerformanceTest::propertyChanging(long, Repeats){}
void PerformanceTest::propertyChanging(Time, ExecutionTime){}


PerformanceTest::PerformanceTest(const std::string  &name):UnitTest(name),_Repeats(0),_ExecutionTime(5.0){}

