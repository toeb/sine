#include "UnitTest.h"
#include <core.testing/UnitTestRunner.h>
using namespace nspace;


UnitTest::UnitTest(const std::string & name){
  setTestName(name);
}


 void UnitTest::RunTest(){run();}
    void UnitTest::propertyChanging(std::string, TestName){}
    void UnitTest::propertyChanging(SourceInfo*, Info){}
    void UnitTest::propertyChanging(bool, IsInitialized){}    
    void UnitTest::propertyChanging(double, Time){}
    void UnitTest::propertyChanging(int, FailedTests){}
    void UnitTest::propertyChanging(time_t, TestStartTime){}
    void UnitTest::propertyChanging(time_t, TestEndTime){}
    void UnitTest::itemAdded(UnitTestResult*,Results){if(item->getFailed())setFailedTests(_FailedTests+1);}
    void UnitTest::itemRemoved(UnitTestResult*,Results){if(item->getFailed())setFailedTests(_FailedTests-1);}




    UnitTest::~UnitTest(){
      for(uint i=0; i < Results(); i++){
        delete Results().at(i);
      }
      /* removed for backwards compatibility
      for(auto test : Results().elements()){
        delete test;
      }*/
      Results().clear();
    }

    void UnitTest::reset(){
      if(getIsInitialized())destroy();
      setIsInitialized(false);    
    }

     void UnitTest::initialize(){}
     void UnitTest::destroy(){}

    bool UnitTest::runTaskReturnSuccess(){
      reset();
      initialize();
      setIsInitialized(true);
      runTest();
      destroy();



      return true;
    }

     void UnitTest::toString(std::ostream & out)const{
      out << "Test '"<< getTestName()<<"' executed in "<< std::fixed<<getAccumulatedTime()<<"s ";
      Results().foreachElement([&](UnitTestResult* result){
        out << std::endl<<"  "<<*result;
      });

    }

     void UnitTest::runTest(){      
      tick();
      test();
      tock();
    }



