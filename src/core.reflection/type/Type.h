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
*/
#pragma once
#include <config.h>
#include <core.graph/Node.h>

#include <core.collection/containers/Set.h>

#include <core.property.h>
#include <memory>
namespace nspace
{
  // forward declarations
  class MemberInfo;
  class MethodInfo;
  class PropertyInfo;
  class Type;
  class Object;

  typedef const Type * ConstTypePtr;

  /**
  * \brief Defines an alias representing identifier for a type.
  */
  typedef uint TypeId;


  /**
  * \brief Type.
  *        this class represents a Type. it Inherits from Node<Type> so that a the typehierarcy may be accessed.
  *        Alot of Macros are defined to help specify types / members for classes
  *        This class contains methods for reflecting over Objects
  */
  class Type : public Node<Type>
  {
  private:
    static TypeId _typeCounter;
  protected:
    Type();
  public:
    friend bool operator==(const Type & a, const Type & b);
    friend bool operator!=(const Type & a, const Type & b);
    friend std::ostream & operator <<(std::ostream & out, const Type & type);
    friend std::ostream & operator <<(std::ostream & out, const Type * type);
    
    
    std::shared_ptr<void>   createInstance() const;
    std::shared_ptr<Object> createObjectInstance()const;
    template<typename T> std::shared_ptr<T> createTypedInstance()const;

    bool isConstructible()const;
    bool isStringifyable()const;

    void objectToString(const void * object, std::ostream & stream)const;
    std::string objectToString(const void * object)const;



    std::shared_ptr<Object> toSmartObjectPointer(std::shared_ptr<void> object)const;
    Object * toRawObjectPointer(void * object)const;

    std::shared_ptr<void> toSmartDerivedPointer(std::shared_ptr<Object> object)const;
    void * toRawDerivedPointer(Object * object)const;

    typedef TypeId basic_property(Id);
    typedef std::string                                                   basic_property(Name);
    typedef std::function<std::shared_ptr<Object>(std::shared_ptr<void>)> basic_property(SmartObjectPointerConverter);    
    typedef std::function<std::shared_ptr<void>(std::shared_ptr<Object>)> basic_property(SmartDerivedPointerConverter);
    typedef std::function<Object *(void * )>                              basic_property(RawObjectPointerConverter);
    typedef std::function<void *(Object * )>                              basic_property(RawDerivedPointerConverter);
    typedef std::function<std::shared_ptr<void>()>                        basic_property(CreateInstanceFunction);
    typedef std::function<void(const void *, std::ostream &)>             basic_property(ObjectToStringFunction);

    template<typename DerivedType> static Object * rawCastToObject(void * pointer);
    template<typename DerivedType> static std::function<Object *(void * )> rawToObjectCaster();
    template<typename DerivedType> static std::shared_ptr<Object> smartCastToObject(std::shared_ptr<void> pointer);
    template<typename DerivedType> static std::function<std::shared_ptr<Object> (std::shared_ptr<void>  )> smartToObjectCaster();
    template<typename DerivedType> static std::shared_ptr<void> smartCastToDerived(std::shared_ptr<Object> pointer);
    template<typename DerivedType> static std::function<std::shared_ptr<void>(std::shared_ptr<Object>)> smartToDerivedCaster();
    template<typename DerivedType> static void * rawCastToDerived(Object * pointer);
    template<typename DerivedType> static std::function<void*(Object *)> rawToDerivedCaster();
    template<typename DerivedType> static void derivedToString(const void * ptr, std::ostream & stream);
    template<typename DerivedType> static std::function<void (const void * , std::ostream &)> derivedStringifier();


    bool isConvertibleToSmartObjectPointer()const;
    bool isConvertibleToRawObjectPointer()const;


    


    PROPERTYSET(const MemberInfo *, Members,,);
  public:
    Set<const PropertyInfo*> Properties() const;
    const MemberInfo * getMember(const std::string & name) const;
    const MethodInfo * getMethodInfo(const std::string & name) const;
    const PropertyInfo * getProperty(const std::string & name) const;
    bool isSuperClassOf(const Type * other) const;

  protected:
    void onPredecessorAdded(Type* type);
    void onPredecessorRemoved(Type* type);
  };
}