#pragma once

#include <config.h>
#include <ostream>
#include <string>
#include <memory>

#include <core/Set.h>
#include <core/Comparator.h>

// helper macros needed for MODIFIER(x)
#define _MODIFIER_public public:
#define _MODIFIER_private private:
#define _MODIFIER_protected protected:
#define _MODIFIER_ 

// returns the modifier specfied by x and appending a : if x is not empty
// MODIFIER(public) --> public:
// MODIFIER(private) --> private:
// MODIFIER() --> 
#define MODIFIER(x) _MODIFIER_##x  

// macro for defining the fieldname (SomeName --> _SomeName
#define FIELDNAME(NAME) _##NAME
// macro for get method (SomeName --> getSomeName)
#define GETMETHOD(NAME) get##NAME
// macro for set method (SomeName --> setSomeName)
#define SETMETHOD(NAME) set##NAME


// defines a field named <NAME> of type <TYPE> in a class/struct which is private by default
// FIELD(int, number) --> private: int number;
// FIELD(int, number, public) --> public: int number; //remark:  actually the expansion will result in: private: public: int number;
#define FIELD(TYPE,NAME,_MODIFIER) private: MODIFIER(_MODIFIER) TYPE NAME;


// defines a getter method for a property name <NAME> of type <TYPE> which is public by default
// GET(int, Number) --> public: inline int getNumber()const
// GET(int, Number, protected) --> protected: inline int getNumber()const
#define GET(TYPE,NAME,_MODIFIER) public: MODIFIER(_MODIFIER) inline TYPE GETMETHOD(NAME)()const

// defines a setter method for a property name <NAME> of type <TYPE> which is public by default
// SET(int, Number) --> public: inline void setNumber(int value)
// SET(int, Number, protected) --> protected: inline void setNumber(int value)
#define SET(TYPE,NAME,_MODIFIER) public: MODIFIER(_MODIFIER) inline void SETMETHOD(NAME)(TYPE value)

//#define FIELD(MODIFIER, TYPE,NAME) MODIFIER: TYPE FIELDNAME(NAME);

// declares the default setter method (default: public) allows insertion of code before the fields value is returned
#define GETTER(TYPE,NAME,_MODIFIER,BEFOREGET) GET(TYPE,NAME,_MODIFIER){BEFOREGET; return FIELDNAME(NAME);}

// declares the default getter method allows insertion of code before and after th value of the field is set
#define SETTER(TYPE,NAME,_MODIFIER,BEFORESET,AFTERSET) SET(TYPE,NAME,_MODIFIER){BEFORESET; FIELDNAME(NAME) = value; AFTERSET;} 


// BASIC_PROPERTY - defines a property which consists of a private field named _<NAME> and a getter and setter method which are public by default
// it is also possible to inject code in get method as well as before and after the private field was changed
// BASIC_PROPERTY(std::string, LastName) -->  private: std::string _LastName;
//                                  public: inline std::string getLastName()const{ return _LastName; }
//                                  public: inline void setLastName(std::string value){ _LastName=value; }
//
// BASIC_PROPERTY(int, Num,protected,std::cout<<"getting Num"<<std::endl, std::cout << "setting Num" << std::endl, std::cout << "Num was set to " << value << std::endl) -->
//            private: int _Num;
//            public: inline int getNum()const{ 
//              std::cout << "getting Num" << std::endl;
//              return _Num;
//            }
//            public: inline void setNum(int value){
//              std::cout << "setting Num" << std::endl;
//              _Num = value;
//              std::cout << "Num was set to " << value << std::endl;
//            }
// which can then be called
// given: _Num =0;
// object.setNum(3);
// object.getNum();
// --> output   setting Num
//              Num was set to 3
//              getting Num
#define BASIC_PROPERTY(TYPE,NAME,_MODIFIER, BEFOREGET, BEFORESET, AFTERSET) \
  FIELD(TYPE,FIELDNAME(NAME),private)\
  GETTER(TYPE,NAME,_MODIFIER,BEFOREGET)\
  SETTER(TYPE,NAME,_MODIFIER,BEFORESET,AFTERSET)




// defines a reference accessor of type <TYPE> & which is non const and public by default
// REF(std::string, FirstName) --> public: inline std::string  & FirstName()
// REF(std::string, FirstName, const, protected) --> protected: inline const std::string & FirstName()const
#define REF(TYPE,NAME,CONST,_MODIFIER) public: MODIFIER(_MODIFIER) inline CONST TYPE & NAME() CONST

#define READONLY_REFERENCE(MODIFIER, TYPE,NAME) MODIFIER:inline  const TYPE & NAME()const{return FIELDNAME(NAME);}
#define REFERENCE(MODIFIER,TYPE,NAME) MODIFIER:inline TYPE & NAME(){return FIELDNAME(NAME);}
#define FIELD_REFERENCE(MODIFIER,TYPE,NAME) FIELD(TYPE,FIELDNAME(NAME),private) READONLY_REFERENCE(MODIFIER,TYPE,NAME); REFERENCE(MODIFIER, TYPE,NAME);
#define PUBLIC_FIELD_REFERENCE(TYPE,NAME) FIELD_REFERENCE(public,TYPE,NAME)


#define READONLY_SIMPLE_PROPERTY(TYPE,NAME)\
  FIELD(TYPE,FIELDNAME(NAME),private);\
  GETTER(TYPE,NAME,public);


#define READONLY_PROPERTY(TYPE,NAME) \
  READONLY_REFERENCE(public,TYPE,NAME)\
  READONLY_SIMPLE_PROPERTY(TYPE,NAME)


//#define POINTER_PROPERTY_DELETER(TYPE,NAME)\
//  void delete##NAME(){TYPE temp = GETMETHOD(NAME)(); SETMETHOD(NAME)(0); delete temp;}


#define ITEMADDMETHODNAME(NAME) onItemAddedTo##NAME
#define ITEMREMOVEMETHODNAME(NAME) onItemRemovedFrom##NAME
#define itemAdded(TYPE,NAME) ITEMADDMETHODNAME(NAME)(TYPE  item)
#define itemRemoved(TYPE,NAME) ITEMREMOVEMETHODNAME(NAME)(TYPE  item)




// creates a set of type TYPE in the current class allows public reference acces to the field. adds an observer
// to the set which causses the code blocks in ONADD and ONREMOVE to be called whenever an element is added or removed
// e.g.
//  class TestClass{
//    PROPERTYSET(int,Numbers,{cout << item << " added"<<endl;}, {cout << item << " removed" <<endl;});
//  };
// int main(){
//  TestClass c;
//  c.Numbers().add(2);
//  c.Numbers().add(3);
//  c.Numbers().add(2);
//  c.Numbers().remove(3);
//  c.Numbers().remove(3);
//  c.Numbers().remove(2);
// }
// this code would result in following output
// 2 added
// 3 added
// 3 removed
// 2 removed
#define PROPERTYSET(TYPE,NAME, ONADD, ONREMOVE)\
        FIELD(nspace::Set<TYPE >,FIELDNAME(NAME),private);\
    private:\
        std::unique_ptr<nspace::ObservableCollection<TYPE >::Observer> _##NAME##Observer;\
        void init##NAME##Observer(){\
            if(!_##NAME##Observer.get()){\
                _##NAME##Observer.reset(new nspace::ObservableCollection<TYPE >::DelegateObserver(\
                            [this](nspace::ObservableCollection<TYPE > * sender, TYPE  object){ ITEMADDMETHODNAME(NAME)(object);},\
                            [this](nspace::ObservableCollection<TYPE > * sender, TYPE  object){ ITEMREMOVEMETHODNAME(NAME)(object);}\
                            ));\
                FIELDNAME(NAME).addObserver(_##NAME##Observer.get());\
            }\
        }\
        void itemAdded(TYPE ,NAME)ONADD;\
        void itemRemoved(TYPE ,NAME)ONREMOVE;\
    public:\
        const nspace::Set<TYPE > & NAME()const{ return FIELDNAME(NAME);}\
        nspace::Set<TYPE > & NAME(){init##NAME##Observer(); return FIELDNAME(NAME);}\
    private:

#define INITIALIZERNAME(NAME) __##NAME##initializer
#define INITIALIZERCLASSNAME(NAME) __##NAME##initializer##Class


// use inside a class definition.  INITIALIZATIONCODE will be executed every time an object the class is instanciated
#define INITIALIZER(NAME,INITIALIZATIONCODE)\
  private:\
class INITIALIZERCLASSNAME(NAME){\
public:\
  INITIALIZERCLASSNAME(NAME)(){INITIALIZATIONCODE}\
};\
  INITIALIZERCLASSNAME(NAME) INITIALIZERNAME(NAME);

//use inside a class definition INITIALIZATIONCODE will be executed for this type.  It will be called when the first object of that type is constructed
#define STATIC_INITIALIZER(NAME,INITIALIZATIONCODE)\
  INITIALIZER(NAME##Static, static bool __isInitialized=false; if(__isInitialized)return; __isInitialized=true; INITIALIZATIONCODE)



/*
#define READONLY_REFERENCE(TYPE,NAME,FIELDNAME)\
  const TYPE & NAME()const{return FIELDNAME;}

#define REFERENCE(TYPE,NAME,FIELDNAME) 

#define EXTENDED_REFERENCE(TYPE,NAME,EXTENSION)\
  

#define REFERENCE(TYPE,NAME, FIELD) 
  */
#define ON_PROPERTY_CHANGING_METHOD_NAME(NAME)on##NAME##Changing
// the signature of the on changing method (w/o returntype, which is void)
#define ON_PROPERTY_CHANGING(TYPE,NAME) ON_PROPERTY_CHANGING_METHOD_NAME(NAME)(TYPE oldvalue, TYPE & newvalue, bool & cancel)
// a nicer to read alias of ON_PROPERTY_CHANGING
#define propertyChanging(TYPE,NAME) ON_PROPERTY_CHANGING(TYPE,NAME)

#define EXTENDED_PROPERTY(TYPE, NAME,_MODIFIER,BEFOREGET,BEFORESET, AFTERSET) \
  BASIC_PROPERTY(TYPE,NAME,_MODIFIER,BEFOREGET,\
    BEFORESET; \
    bool cancel=false;\
    if(FIELDNAME(NAME)==value)return; \
    this->ON_PROPERTY_CHANGING_METHOD_NAME(NAME)(FIELDNAME(NAME),value,cancel); \
    if(cancel)return;\
    , AFTERSET);\
  private:\
  void ON_PROPERTY_CHANGING(TYPE,NAME)

#define EXTENDED_REFERENCE_PROPERTY(MODIFIER,TYPE, NAME)\
MODIFIER:\
  const TYPE & NAME()const{return FIELDNAME(NAME);} \
  TYPE & NAME(){return FIELDNAME(NAME);} \
  private:

#define REFERENCE_PROPERTY(TYPE, NAME) EXTENDED_REFERENCE_PROPERTY(public,TYPE, NAME)


// This macro defines a Property in a class generating getter and setter methods
// as well as a field of the specified TYPE called _<Name> .  It also checks the value for equality 
// before changing it (if the oldvalue and new value are equal the set method just returns)
// The last statement generated is a method called on<NAME>Changing(<TYPE> oldvalue,<TYPE> newvalue, bool & cancel)
// which the client needs to implement (minimally by adding empty braces)
// IMPORTANT :  you can initialize the fields normally in the constructor by writing :_<Name>(...)
//  Example 1: 
//  PROPERTY(int, NumberOfOrders){}  will create:
//  - a private int field called _NumberOfOrders
//  - the getter and setter method int getNumberOfOrders()const, void setNumberOfOrders(int value)
//  - the onNumberOfOrdersChanging(...) method
//  Example 2: 
//  PROPERTY(int, NumberOfOrders){
//    if(newvalue < 3){ 
//      cancel = true;
//      return;
//    }
//    std::cout << "Number of Orders changed from " << oldvalue << " to " << newvalue <<std::endl;
//  }
//  this will create the same field and methods as example 1 however it will cancel the change if
//  the new value is smaller than 3.  if the value is higher than three a string will be printed
//  e.g: setNumberOfOrders(4) --> "Number of Orders changed from 0 to 4"
#define SIMPLE_PROPERTY(TYPE, NAME) EXTENDED_PROPERTY(TYPE,NAME,public,,,)


namespace nspace{
class Property;
typedef const uint TypeId;
typedef const uint ObjectId;
// struct representing a type. 
struct TypeData{
  static const TypeData & UnknownType;
  // the id of this type
  TypeId id;  
  // name of this type
  std::string name;
  // operator for converting this TypeData to its type id
  inline operator const TypeId & ()const{return id;}

  // default constructor
  TypeData();  
  // constructor accepting name
  TypeData(const std::string & name);
  // number of typedata structs created
  static unsigned int typeCount();
  //void * createInstance();
  Set<const Property*> * properties;

  int getPropertyCount()const;
  const Property * getProperty(const std::string & name)const;
  const Property* getProperty(int index)const;

private:
  static unsigned int _typeCounter;
};


template<typename T>
class TypeDataProvider{
public:
static inline const TypeData & getTypeData(){
  return TypeData::UnknownType;
}
};





#define TYPEDATAPROVIDER(TYPE) \
  template<>\
  class TypeDataProvider<TYPE>{\
  public:\
    static inline const TypeData & getTypeData(){\
      return TYPE::ClassType();\
    }\
  };\
  template<>\
  class TypeDataProvider<TYPE*>{\
  public:\
    static inline const TypeData & getTypeData(){\
      return TYPE::ClassType();\
    }\
  };


#define typeof(TYPE) (TypeDataProvider<TYPE>::getTypeData())



// Macro for making an object a typed object.  
// defines a static meta information structure (TypeData) and virtual access methods
#define TYPED_OBJECT(type) public:\
  static inline const TypeData & ClassType(){static TypeData typeData(#type); return typeData; };\
  virtual inline const TypeId & getType()const {return ClassType().id;}\
  virtual inline const TypeData & getTypeData()const {return ClassType();}
 
// base class including types
class Object{
TYPED_OBJECT(Object);
private:
  static uint _idCounter;
  ObjectId _id;  
public:  
  Object();
  ~Object();
  inline const ObjectId & objectId()const{return _id;}
  // tostring method which converts this object to a string representation (should be overridden by subclasses)
  virtual void toString(std::ostream & out)const;
  
  // to string operator
  //std::ostream & operator<<(std::ostream & out)const;
  // tostring method which returns the string
  std::string toString()const;

  friend std::ostream & operator << (std::ostream & out, const Object * obj);  
  friend std::ostream & operator << (std::ostream & out, const Object & obj);

  friend bool operator == (const Object & a, const Object & b){
    return &a==&b;
  }
};
TYPEDATAPROVIDER(Object)






}
