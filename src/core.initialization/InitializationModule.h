#pragma once

#include <core.hub/ModuleBase.h>
#include <core.initialization/Initializable.h>

namespace nspace{
  class InitializationModule : public virtual ModuleBase, public virtual Initializable{
    TYPED_OBJECT(InitializationModule);
  private:
    Set<Initializable*> _initializeables;
  public:
    virtual bool accept(Object * object){
      if(object==this)return false;
      return dynamic_cast<Initializable*>(object)!=0;
    }

    virtual void onAcception(Object * object){
      auto initializeable = dynamic_cast<Initializable*>(object);
      if(isInitialized() && !initializeable->initialize()){
        renounce(initializeable);
        return;
      }

      _initializeables |= initializeable;

    }
    virtual void onRenounce(Object * object){
      _initializeables /= dynamic_cast<Initializable*>(object);
    }

    
   void cleanupObject(){
     _initializeables.foreachElement([](Initializable * initializeable){initializeable->cleanup();});
   };
   bool initializeObject(){
     bool success = true;
     _initializeables.foreachElement([&success](Initializable * initializeable){
       auto named = dynamic_cast<NamedObject*>(initializeable);
       
       std::cout<< "Initializing ";
       if(named)std::cout << named->name() << " ";
       else std::cout << " unknown ";
       std::cout << ". . . . . . . . . . ";
       bool s = initializeable->initialize() ;
       if(s)std::cout << "successful" ;
       else std::cout<< "failed";
       std::cout << std::endl;
       success &=s;
       
     });
     return success;
   }
  };
}