#include <application.sample.h>
#include <visualization.opengl.renderer.geometry.h>
#include <simulation.dynamics.h>
#include <simulation.utility/DynamicsAlgorithm.h>
#include <fstream>
#include <utility.reader/Reader.h>
#include <utility.reader.trajectory.h>
#include <thread>
#include <lua/src/lua.hpp>

#include <v8.h>
using namespace nspace;
using namespace std;


class TestClass : public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(TestClass);
  SUBCLASSOF(Log);

  PROPERTY(int, IntegralValue){}
  PROPERTY(std::string, StringValue){}


};

class ScriptRunner: public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(ScriptRunner);
  SUBCLASSOF(Log);
  OBJECTPOINTERCOLLECTION(Object,Objects,{onObjectAdded(item);},{onObjectRemoved(item);});
public:
  virtual bool runScript(const std::string & script)=0;
  virtual void onObjectAdded(Object*o){}
  virtual void onObjectRemoved(Object*o){}
};
int my_function(lua_State *L)
{
  int argc = lua_gettop(L);

  std::cerr << "-- my_function() called with " << argc
    << " arguments:" << std::endl;

  for ( int n=1; n<=argc; ++n ) {
    std::cerr << "-- argument " << n << ": "
      << lua_tostring(L, n) << std::endl;
  }

  lua_pushnumber(L, 123); // return value
  return 1; // number of return values
}

class Lua : public virtual ScriptRunner{
  REFLECTABLE_OBJECT(Lua);
  SUBCLASSOF(ScriptRunner);
private:
  lua_State * _state;
public:
  Lua():_state(0){
    _state = luaL_newstate();
    luaopen_io(_state);
    luaopen_base(_state);
    luaopen_table(_state);
    luaopen_string(_state);
    luaopen_math(_state);
  }
  ~Lua(){
    lua_close(_state);
  }


  
  bool runScript(const std::string & script){
    logInfo("loading lua script.  length="<<script.length());
    debugInfo("script: "<<script);
    int error=  luaL_loadstring(_state,script.c_str());
    if(error){
      logWarning("Could not load script! (Error "<<error<<")");
      return false;
    }
    error= lua_pcall(_state,0,LUA_MULTRET,0);
    if(error){
      logWarning("Error executing script (Error "<<error<<")");
      return false;
    }
    return true;
  }



};



void report_errors(lua_State *L, int status){

}
v8::Handle<v8::Value> printlnWrap(const v8::Arguments& args);

class V8ScriptRunner : public virtual ScriptRunner{ 
  REFLECTABLE_OBJECT(V8ScriptRunner);

  v8::Handle<v8::Context> _context;



public:
  V8ScriptRunner(){
    using namespace v8;
    HandleScope scope;


    Handle<ObjectTemplate> globalTemplate = ObjectTemplate::New();
    globalTemplate->SetInternalFieldCount(1);    
    
    globalTemplate->Set(String::New("println"),FunctionTemplate::New(printlnWrap));
    


    
    _context = Context::New(0,globalTemplate);
    _context->Enter();
    Local<v8::Object> globalObject =  v8::Object::Cast(*(_context->Global()->GetPrototype()));
    Local<External> scriptRunnerWrapper=  External::New(this);
    globalObject->SetInternalField(0,scriptRunnerWrapper);

    
    Local<Value> value=    requireGlobalObject("testObject1");
  }

  v8::Local<v8::Value> requireGlobalObject(const std::string & name){
    using namespace v8;
    return static_cast<Local<v8::Value> >(_context->Global()->Get(String::New(name.c_str())));
  }
  
  void onObjectAdded(Object * object){
    if(!object)return;


    using namespace v8;
    HandleScope scope;
    Handle<ObjectTemplate> objectTemplate=ObjectTemplate::New();
    objectTemplate->SetInternalFieldCount(1);


    Local<v8::Value> value;
    requireGlobalObject("testObject123");
    
    
    Local<v8::Object> globalObject =  v8::Object::Cast(*(_context->Global()->GetPrototype()));
    





  }
  void onObjectRemoved(Object * object){

  }


  bool runScript(const std::string & source){
    using namespace v8;
    HandleScope scope;
    Context::Scope contextScope(_context);

    auto v8Source = String::New(source.c_str());
    
    logInfo("Compiling Script");
    auto script = Script::Compile(v8Source);
    logInfo("Executing Script");
    auto result = script->Run();
    

    return true;
    
  }


};


v8::Handle<v8::Value> printlnWrap(const v8::Arguments& args)
{
using namespace v8;

  Local<Value> runnerWrap = v8::Object::Cast(*(args.Holder()->GetPrototype()))->GetInternalField(0);
  if (!runnerWrap->IsExternal()) {
    return Undefined();
  }
  Local<External> wrap = Local<External>::Cast(runnerWrap);

  V8ScriptRunner* simScr = static_cast<V8ScriptRunner*>(wrap->Value());

  bool first = true;
  for (int i = 0; i < args.Length(); i++) {
    HandleScope handle_scope;
    if (first) {
      first = false;
    } else {
      std::cout << " ";
    }

    String::Utf8Value str(args[i]);

    std::cout<< *str;
  }
  std::cout << std::endl;
  return Undefined();
}



int main(int argc,  char ** argv){  
  V8ScriptRunner runner;
  
  TestClass object;
  runner.Objects()|=&object;
  runner.runScript("println('helo'); println(testObject123);");
  
  

  return 0;
  

  Lua l;
  l.Objects().add(&object);
  l.runScript("for index = 1,5 do\nprint(index)\nend");


}
