#pragma once
#include <common/Set.h>

namespace nspace{

  struct Entry{
    Entry():value(0),name(""){}
    std::string name;
    void * value;
  };


  class ValueLookup{
  private:    
    Set<Entry*> _entries;
  public:
    const Set<Entry*> & entries()const{
      return _entries;
    }

    template<typename T>
    T operator()(const std::string & parametername){
      return this->get<T>(parametername);
    }
    
    //returns true if parameter hasValue
    template<typename T>
    bool get(T & result, const std::string & parametername){
      if(!hasValue(parametername))return false;
      result = get<T>(parametername);
      return true;
    }

    template<typename T>
    T get(const std::string & parametername){
      T* result = getPointer<T>(parametername);
      //return default value
      if(!result)return T();
      return *result;
    }
    template<typename T>
    T * getPointer(const std::string & parametername){
      if(!hasValue(parametername))return 0;
      Entry * currentEntry = entry(parametername);
      T*result=0;
      result = static_cast<T*>(currentEntry->value);
      return result;
    }

    template<typename T>
    void set(const std::string & parametername,T value){
      Entry * entry = _entries.selectFirst([parametername](Entry* entry){return entry->name == parametername;});
      if(!entry){
        entry = new Entry;
        entry->name = parametername;
        _entries.add(entry);
      }
      if(!entry->value)entry->value = new T();
      *static_cast<T*>(entry->value) = value;      
    }

    bool has(const std::string & parametername)const{
      return entry(parametername)!=0;
    }
    bool hasValue(const std::string & parametername)const{
      const Entry * currentEntry = entry(parametername);
      if(!currentEntry)return false;
      if(!currentEntry->value)return false;
      return true;
    }
  private:
    Entry * entry(const std::string & name){
      Entry * entry = _entries.selectFirst([name](Entry* entry){return entry->name == name;});
      return entry;
    }
    const Entry * entry(const std::string & name)const{
      Entry * entry = _entries.selectFirst([name](Entry* entry){return entry->name == name;});
      return entry;
    }

    Entry * require(const std::string & name){
      Entry * currentEntry = entry(name);
      if(!currentEntry){
        currentEntry = new Entry;
        currentEntry->name = name;
        _entries.add(currentEntry);
      }
      return currentEntry;
    }

  };
}