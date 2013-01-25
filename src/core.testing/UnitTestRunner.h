/**
* Copyright (C) 2013 Tobias P. Becker
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the  rights to use, copy, modify, merge, publish, distribute,
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* More information at: https://dslib.assembla.com/
*
*/
#pragma once
#include <core.testing/UnitTest.h>
namespace nspace {

  class CommandLineArgumentDefinition:public PropertyChangingObject{
    REFLECTABLE_OBJECT(CommandLineArgumentDefinition);
    PROPERTYCOLLECTION(std::string,Aliases,{},{});
    PROPERTY(std::string, Description){}
    PROPERTY(std::string, Name){}
  public:
    CommandLineArgumentDefinition(){}
    CommandLineArgumentDefinition(const std::string & name,const std::string & description="", const std::string & alias=""){
      setName(name);
      setDescription(description);
      if(alias!="")Aliases()|=alias;
    }

    bool isIdentifiedBy(const std::string & name)const{
      if(getName()==name)return true;
      if(Aliases().any([&name](std::string alias){return name==alias;}))return true;
      return false;
    }
  };
  
  /*
  template<typename T>
  class TypeInfo<std::vector<T>>:public Type{
    TEMPLATEDSINGLETON(TypeInfo,<std::vector<T> >){
      setCreateInstanceFunction([](){return new std::vector<T>();});
      setDeleteInstanceFunction([](void * v){delete static_cast<std::vector<T>*>(v);});
      
      setName(DS_INLINE_STRING("std::vector<"<<typeof(T)->getName()<<">"));
    }
  };
  //need serializers
  */

  class CommandLineArgument : public PropertyChangingObject{
    REFLECTABLE_OBJECT(CommandLineArgument);
    OBJECTPOINTERPROPERTY(CommandLineArgumentDefinition, ArgumentDefinition){}
  private:
    std::vector<std::string> _Tokens;
  public:
    std::vector<std::string> & Tokens(){
      return _Tokens;
    }
    const std::vector<std::string> & Tokens()const{
      return _Tokens;
    }
    template<typename T>
    std::unique_ptr<T> parse(int i=0)const{
      if(_Tokens.size()<=i)return std::unique_ptr<T>();
      T result;
      if(!nspace::parse(result,_Tokens[i]))return std::unique_ptr<T>();
      return std::unique_ptr<T>(new T(result));
    }

  };
  class CommandLineArgumentParser:public PropertyChangingObject{
    REFLECTABLE_OBJECT(CommandLineArgumentParser);
    OBJECTPOINTERCOLLECTION(CommandLineArgumentDefinition,Definitions,{},{});
    OBJECTPOINTERCOLLECTION(CommandLineArgument, Arguments,{},{});     
    PROPERTY(std::string, ExecutablePath){}
  private:
    std::vector<std::string> _tokens;
  public:

    typedef std::unique_ptr<CommandLineArgument> ArgumentPtr;
    void parse(const int argc, const char *const* argv){

      _tokens.clear();
      setExecutablePath("");
      if(!argc)return;
      setExecutablePath(*argv);
      for(int i=1; i < argc; i++){
        _tokens.push_back(argv[i]);
      }


    }

    CommandLineArgumentDefinition* Definition(const std::string & nameOrAlias){
      return Definitions().first([&](CommandLineArgumentDefinition* definition){return definition->isIdentifiedBy(nameOrAlias);});
    }

    ArgumentPtr Argument(CommandLineArgumentDefinition & definition){
      CommandLineArgument arg;

      auto it = _tokens.begin();
      auto end = _tokens.end();
      std::vector<std::string> tokens;
      bool definitionStarted = false;
      while(it!=end){
        if(definition.isIdentifiedBy(*it)){
          definitionStarted = true;
        }else if(definitionStarted){
          if(Definition(*it)){
            break;
          }
          tokens.push_back(*it);
        }
        it++;
      }
      if(it==end&&!definitionStarted)return ArgumentPtr();

      arg.setArgumentDefinition(&definition);
      arg.Tokens() =tokens;

      auto ptr = ArgumentPtr(new CommandLineArgument(arg));
      return ptr;
    }

    ArgumentPtr Argument(const std::string & nameOrAlias){
      auto definition =Definition(nameOrAlias);
      if(!definition)return ArgumentPtr();
      return Argument(*definition);

    }





  };

  /**
  * \brief Unit test runner.
  *
  */
  class UnitTestRunner : public StatefulTask, public ProgressReporter {
    REFLECTABLE_OBJECT(UnitTestRunner);

    /**
    * \brief currently this runner is only available as a singleton
    *
    */
    SINGLETON(UnitTestRunner) : _FailedTestCount(0){
      setName("UnitTestRunner");
    }

    /**
    * \brief Contains all tests
    */
    OBJECTPOINTERCOLLECTION(UnitTest,RegisteredTests,{},{});

    /**
    * \brief Number of Tests which failed during run.
    *
    */
    PROPERTY(int, FailedTestCount){}


  public:
    Set<UnitTest*> Tests(const std::string & name){
      return RegisteredTests().subset([&](UnitTest* test){return stringtools::startWithIgnoreCase(test->getTestName(), name);});
    }
    UnitTest* Test(const unsigned int index){
      if(index < RegisteredTests().size())return RegisteredTests().at(index);
      return 0;
    }
    static int runCommandLine(int argc=0, char** argv=0){      
      CommandLineArgumentParser parser;
      parser.Definitions()|=new CommandLineArgumentDefinition("--test-count","prints the number of tests to std out", "-c");
      parser.Definitions()|=new CommandLineArgumentDefinition("--test-name","--test-name <index> prints the name of test at index to std out", "-n");
      parser.Definitions()|= new CommandLineArgumentDefinition("--run-test","-run-test <index|name|'all'> runs the test at index i or name", "-r" );
      parser.Definitions()|=new CommandLineArgumentDefinition("--verbose", " shows the output", "-v");
      parser.Definitions()|=new CommandLineArgumentDefinition("--list-all", " shows all tests", "-l");
      auto & runner = *instance();
      parser.parse(argc,argv);
      int logLevel=0;
      auto arg = parser.Argument("--verbose");
      if(arg){
        logLevel = 10;
      }

      runner.setLoggingLevel(logLevel);

      arg = parser.Argument("--test-count");
      if(arg){
        std::cout << runner.RegisteredTests().size();
        return 0;
      }
      arg = parser.Argument("--test-name");
      if(arg){
        auto val = arg->parse<unsigned int>();
        if(val){
          auto test = runner.Test(*val);
          if(!test){
            std::cerr << " test not found";
            return 0;
          }

          std::cout << test->getTestName();;

          return 0;
        }else{
          std::cerr << "no index given";

          return 1;
        }
      }

      arg = parser.Argument("--list-all");
      if(arg){
        int i=0;
        runner.RegisteredTests().foreachElement([&i](UnitTest * test){
          std::cout << i<<": "<< test->getTestName()<<std::endl;
          i++;
        });

        return 0;
      }

      arg = parser.Argument("--run-test");
      if(arg){
       Set< UnitTest *> tests;
        auto index = arg->parse<unsigned int>();
        /*if(!index){*/
        //  hack:because of bug in parse method that returns true even if string was unparsable...
        if(index&&*index==0&&*arg->parse<std::string>()!="0"){

          auto name = arg->parse<std::string>();
          if(!name){
            std::cerr << "could not find test";
            return 1;
          }
          tests|=runner.Tests(*name);
        }else{
          tests |= runner.Test(*index);
        }        
        if(tests.empty()){
          std::cerr<< "no test found"<<std::endl;
          return 1;
        }
        
        int failures =0;

        tests.foreachElement([&](UnitTest* test){
          test->setLoggingLevel(logLevel);
          test->run();
          if(parser.Argument("--verbose")){
            std::cout << *test<<std::endl;
          }
          failures+=test->getFailedTests();
        });

        return failures;
      }

      runner.run();

      arg = parser.Argument("--verbose");
      if(arg){
        std::cout << runner<<std::endl;
      }

      std::cout<<runner;
      return runner.getFailedTestCount();
    }
    void toString(std::ostream & out) const;
  protected:
    bool runTaskReturnSuccess();
  };
}