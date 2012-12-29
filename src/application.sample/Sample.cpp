#include "Sample.h"
using namespace nspace;

Sample::Sample():_application(0){}
void Sample::setApplication(SampleApplication & application){_application = &application;}
SampleApplication & Sample::application(){return *_application;}