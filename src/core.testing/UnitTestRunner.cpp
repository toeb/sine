#include "UnitTestRunner.h"

using namespace nspace;

bool UnitTestRunner::runTaskReturnSuccess(){
  setTotalProgress(RegisteredTests().size());
  setFailedTestCount(0);

  RegisteredTests().foreachElement([this](UnitTest* test){
    test->run();
    if(test->getFailedTests()>0) setFailedTestCount(getFailedTestCount()+1);
    incrementProgress(1);
    logMessage("Progress: " << percent()<<" % done",3);
  });      

  return true;
}

void UnitTestRunner::toString(std::ostream & out)const{

  out << "Testrunner: " << (RegisteredTests().size()-getFailedTestCount()) << "/"<<RegisteredTests().size() <<" succeeded ("<<getFailedTestCount()<<" Failures)"<<std::endl;
  RegisteredTests().foreachElement([&](UnitTest* test){
    out << test<<std::endl;
  });
}