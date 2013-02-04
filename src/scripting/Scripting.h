#pragma once

#include <core.logging.h>

namespace nspace{

  class ScriptObject : public Object{
    TYPED_OBJECT(ScriptObject);

  public:
    SIMPLE_PROPERTY(void*, ObjectPointer){}
    SIMPLE_PROPERTY(const Type *, ObjectType){}

  };

  class VirtualScriptMachine : public Log{
    REFLECTABLE_OBJECT(VirtualScriptMachine);
    SUBCLASSOF(Log);
    OBJECTPOINTERCOLLECTION(Object,ManagedObjects,{},{});
  public:
    virtual bool registerType(const Type * type){return false;}
    virtual bool registerObject(Object * object){return false;}
    virtual bool registerObject(ScriptObject * object){return false;}

    template<typename T>
    bool registerObject(T* object){
      auto object = new ScriptObject();
      object->setObjectPointer(object);
      object->setObjectType(typeof(object));
      return registerObject(object);
    }


    virtual bool loadStream(std::istream & stream);
    bool loadString(const std::string & script);
    bool loadFile(const std::string & filename);
  };
}

