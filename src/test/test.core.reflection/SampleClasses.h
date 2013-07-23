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

  class BasicMath{
  private:
    std::string _name;
  public:
    BasicMath(const char * name):_name(name){

    }
    BasicMath(std::string name):_name(name){

    }
    BasicMath(){
    }
    /**
    * returns the number one (multiplcation identity)
    */
    double one()const{return 1.0;}

    /**
    * returns the number zero (additive identity)
    */
    double zero()const{return 0.0;


    /**
    * adds two number
    */
    double add(double a, double b)const{return a+b;}

    /**
    * adds three numbers
    */
    double add(double a, double b, double c)const{return add(a,add(b,c));}

    /**
    * negates a number (addition invers element)
    */
    double negate(double a)const{return -a;}

    /**
    *  subtracts element b from a 
    */
    double subtract(double a, double b)const{
      return add(a,negate(b));
    }
    /**
    * multiplies elements a and b
    */
    double multiply(double a, double b)const{
      return a*b;
    }

    };

    public class AccumulatingBasicMath : public BasicMath{
      double accumulator;
    public:
      AccumulatingBasicMath():accumulator(0){}
      AccumulatingBasicMath(double initialValue):accumulator(initialValue){}

      /**
      * adds a to the accumulator
      */
      double add(double a){
        return accumulator = add(accumulator,a);
      }
      double subtract(double a){
        return accumulator = subtract(accumulator,a);
      }
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

      /**
      * a simple method which does nothing
      */
      void simpleMethod()const{}



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