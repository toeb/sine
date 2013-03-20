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
#include <sstream>
namespace nspace
{
  // forward declarations
  class MemberInfo;
  class MethodInfo;
  class PropertyInfo;
  struct ConstructorInfo;
  struct NamespaceInfo;
  class Type;
  
 typedef const Type * ConstTypePtr;


  /**
  * \brief Type.
  *        this class represents a Type. it Inherits from Node<Type> so that a the typehierarcy may be accessed.
  *        Alot of Macros are defined to help specify types / members for classes
  *        This class contains methods for reflecting over Objects
  */
  class Type : public Node<Type>
  {
  public: 
    /**
    * \brief Defines an alias representing identifier for a type.
    */
  typedef uint TypeId;
  private:
    static TypeId _typeCounter;
  protected:
    Type(const std::string & name, const Type * underlyingType);
  public:
    virtual ~Type();
    // type traits
    typedef const NamespaceInfo * basic_property(Namespace);


    // comparison
    friend bool operator==(const Type & a, const Type & b);
    friend bool operator!=(const Type & a, const Type & b);

    // to string
    friend std::ostream & operator <<(std::ostream & out, const Type & type);
    friend std::ostream & operator <<(std::ostream & out, const Type * type);
        
    // type fields
    typedef TypeId             basic_property(Id);
    typedef std::string        basic_property(Name);    
    std::string getFullyQualifiedName()const;

    // member access
    PROPERTYSET(const MemberInfo *, Members,,);
  public:
    Set<const PropertyInfo*>          Properties() const;
    Set<const MethodInfo*>            Methods()const;
    Set<const ConstructorInfo*>       Constructors()const;


    const MemberInfo *        getMember(const std::string & name) const;
    const MethodInfo *        getMethod(const std::string & name) const;
    const PropertyInfo *      getProperty(const std::string & name) const;
    bool isDefaultConstructible()const;
    const ConstructorInfo *   getConstructor(const std::vector<const Type*>& types)const;    
    template<typename Container> const ConstructorInfo * getConstructor(const Container & container)const;
    
    //type hierarchy
    bool isSuperClassOf(const Type * other) const;
    bool isSubClassOf(const Type * other)const;
    typedef Set<const Type*> basic_property(SuperClasses);
    typedef Set<const Type*> basic_property(RootClasses);

    // modifiers
    
    typedef const Type *  basic_property(UnderlyingType);
    typedef const Type *  basic_property(UnqualifiedType);
    typedef bool          basic_property(IsPointer);
    typedef bool          basic_property(IsReference);
    typedef bool          basic_property(IsVolatile);
    typedef bool          basic_property(IsConst);
    bool isUnqualifiedType()const;
    const Type * removeConst()const;
    const Type * removeReference()const;
    const Type * removePointer()const;

  protected:
    void onSuccessorAdded(Type * type);
    void onSuccessorRemoved(Type* type);

    void onPredecessorAdded(Type* type);
    void onPredecessorRemoved(Type* type);
  };
}