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
#include <core.serialization/Serialization.h>
#include <core.reflection/member/MemberInfo.h>
#include <core.reflection/member/method/MethodInfo.h>
namespace nspace {
  class PropertyInfo : public MemberInfo{
    typedef const MethodInfo * basic_property(GetMethod);
    typedef const MethodInfo * basic_property(SetMethod);
    typedef const Type * basic_property(PropertyType);
  protected:
    PropertyInfo(const std::string & name, const MethodInfo * getter, const MethodInfo * setter):MemberInfo(name),_SetMethod(setter),_GetMethod(getter){
      const Type *  propertyType=0;
      if(getter){
        if(getter->getArgumentTypes().size()!=0){
          std::cerr << "getter is not a parameterless method. ignoring"<<std::endl;
          _GetMethod=0;
        }else{
          auto type = getter->getReturnType()->removeConst()->removeReference();
          propertyType = type->removeConst()->removeReference();
        }
      }
      if(setter){
        if(setter->getArgumentTypes().size()!=1){
          std::cerr<<"setter method is not a single parameter method"<<std::endl;          
        }else{
          auto type = setter->getArgumentTypes().at(0)->removeReference()->removeConst();
          if(propertyType){
            if(propertyType!=type){
              std::cerr<<"getter and setter raw types do not match"<<std::endl;

            }else{
              // find closest relation 
              
            }
          }else{
            propertyType = type;
          }
          
        }
      }
    }
  public:
    
    bool isGettable()const{return getGetMethod()!=0;}
    bool isSettable()const{return getSetMethod()!=0;}

    Argument get(const void * ptr)const{
      if(!isGettable())return Argument();
      auto getter = getGetMethod();
      return getter->call(ptr);
    }
    Argument get(void * ptr)const{
      if(!isGettable())return Argument();
      auto getter = getGetMethod();
      return getter->call(ptr);
    }
    void set(void * ptr, Argument argument)const{
      if(!isSettable())return;
      auto setter = getSetMethod();
      Argument args[1]={argument};
      setter->call(ptr,args);

    }
    void set(const void * ptr , Argument argument)const{ 
      if(!isSettable())return;
      auto setter = getSetMethod();
      Argument args[1]={argument};
      setter->call(ptr,args);
    }
  };
}
