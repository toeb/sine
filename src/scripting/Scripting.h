#pragma once

#include <core.logging.h>

namespace nspace{

  class ScriptObject : public Object{
    TYPED_OBJECT(ScriptObject);

  public:
    void toString(std::ostream & out)const{
      getObjectType()->objectToString(getObjectPointer().get(),out);
    }
    ScriptObject():_ObjectType(0){}
    SIMPLE_PROPERTY(std::shared_ptr<void>, ObjectPointer){}
    SIMPLE_PROPERTY(const Type *, ObjectType){}
    template<typename T> std::shared_ptr<T> object(){return std::static_pointer_cast<T>(getObjectPointer());}
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
      auto obj = new ScriptObject();
      obj->setObjectPointer(object);
      obj->setObjectType(typeof(T));
      return registerObject(obj);
    }


    virtual bool loadStream(std::istream & stream);
    bool loadString(const std::string & script);
    bool loadFile(const std::string & filename);
  };
}

