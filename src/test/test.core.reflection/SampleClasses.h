#pragma once


// some test classes with hierachy/templates and members
namespace uninvasiveReflection{
  class SomeOtherClass{
    int j;
    std::string k;
  };

  template<typename T1,typename T2>
  class SomeTemplateClass{

  };

  class SomeTestClass{
  public:
    //! [SomeTestClass constructors]
    SomeTestClass(){}
    SomeTestClass(std::string name){}
    SomeTestClass(int i, int k){}
    //! [SomeTestClass constructors]
    int i;
    int j;
    std::string str;
    std::shared_ptr<int> iptr;
    std::shared_ptr<SomeTestClass> classPtr;
    int * irawptr;
    SomeOtherClass classmember;

    const int & getI()const{return i;}
    void setI(const int & i){this->i = i;}

    int methodA0(){}
    int methodA0()const{}    
    int methodA0(int a1){}
    int methodA0(int a1)const{}
    int methodA0(double a1){}
    int methodA0(double a1)const{}



    // three method overloads varying in argument types, return types and constness
    double method1(int ka, double d){return ka*d;}
    float method1(int ka, double d)const{return ka*d;}
    float method1(int ka, double d,std::string third){return ka*d;}

    double method2(int ka, double d){return ka*d;}


    template<typename TK>
    double method3(double a, double b){return a+b;}
  };
  class SomeDerivedClass : public SomeTestClass{
  public:
    int k;
    std::string str2;
  };

}