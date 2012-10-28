#include <application.sample.h>
#include <visualization.opengl.renderer.geometry.h>

using namespace nspace;
using namespace std;
class IEnumerable{
public:
  virtual void * elementPointerAt(uint i)const;
  virtual uint size()const;
};
template<typename T>
class ITypedEnumerable : public IEnumerable{
public:
  virtual T elementAt(uint i)const;
};
class ICollection : public IEnumerable{
public:
  virtual bool addElement(void * item);
  virtual bool removeElement(void * item);
};
template<typename T>
class ITypedCollection : public ITypedEnumerable<T>, public ICollection{
public:
  bool addElement(void * item){
    if(!item)return false;
    auto typedItem = reinterpret_cast<T*>(item);
    return addElement(*typedItem);
  }
  bool removeElement(void * item){
    if(!item)return false;
    auto typedItem = reinterpret_cast<T*>(item);
    return addElement(*typedItem);
  }
  virtual bool addElement(T item);
  virtual bool removeElement(T item);
};

class PropertySetInfo : public virtual Object{  
  TYPED_OBJECT(PropertySetInfo);

  SIMPLE_PROPERTY(const TypeData*, ElementType){}

  // custom serializer
  SIMPLE_PROPERTY(CustomSerializer*, CustomElementSerializer){}
  // custom deserializer
  SIMPLE_PROPERTY(CustomDeserializer*, CustomElementDeserializer){}
public:
  PropertySetInfo():_ElementType(0),_CustomElementDeserializer(0),_CustomElementSerializer(0){}
  // sets the value of the property set at i
  virtual bool setElement(void * object, uint i, const void * value)const=0;
  // gets the value of the property set at i
  virtual bool getElement(const void * object, uint i, void * value)const=0;  

  virtual bool addElement(void * object, void*value)const=0;
  virtual bool removeElement(void * object, const void*value)const=0;

  virtual bool deserializeElement(void * object, uint i,std::istream & in)const=0;
  virtual bool serializeElement(void * object, uint i,std::ostream & out)const=0;

  virtual uint getElementCount(void * object)const=0;

  template<typename ObjectType, typename T> bool get(T& value, uint i, const ObjectType & object)const{ getValue(&object,i,&value); }
  template<typename ObjectType, typename T> bool set(const T& value, uint i, ObjectType & object)const{ setValue(&object,i,&value); }   

};



template<typename OwningClass, typename ValueType>
class TypedPropertySetInfo:public virtual TypedProperty<OwningClass, Set<ValueType> >, public virtual PropertySetInfo{
  TYPED_OBJECT(TypedPropertySetInfo);
public:
  TypedPropertySetInfo(){
    setElementType(&typeof(ValueType));
  }

  virtual Set<ValueType> & getMutableSetReference( OwningClass * object )const=0;
  virtual const Set<ValueType> & getConstSetReference(const OwningClass * object )const=0;

  // TypedProperty Implementation
  void setTypedValue(OwningClass * object, Set<ValueType>  value)const{
    getMutableSetReference(object)=value;
  }
  Set<ValueType> getTypedValue(const OwningClass * object)const{
    return getConstSetReference(object);
  }


  const Set<ValueType> * getConstTypedPointer(const OwningClass * object)const{
    return &getConstSetReference(object);
  }
  Set<ValueType> * getMutableTypedPointer(OwningClass * object)const{
    return &getMutableSetReference(object);
  }

  virtual uint getElementCount(void * object)const{
    auto typedObject = reinterpret_cast<OwningClass*>(object);
    return getConstSetReference(typedObject).size();
  }

  bool addTypedElement(OwningClass & object, ValueType & value)const{
    return getMutableSetReference(&object).add(value);
  }
  bool removeTypedElement(OwningClass & object, const ValueType & value)const{
    return getMutableSetReference(&object).remove(value);
  }

  bool addElement(void * object, void*value)const{
    auto typedObject = reinterpret_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<ValueType*>(value);
    return addTypedElement(*typedObject,*typedValue);
  }
  bool removeElement(void * object, const void*value)const{
    auto typedObject = reinterpret_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<const ValueType*>(value);
    return removeTypedElement(*typedObject,*typedValue);
  }
  bool setTypedElement(OwningClass * object, uint i, const ValueType * value )const{
    Set<ValueType> & propertyset = getMutableSetReference(object);
    if(i>=propertyset.size())return false;
    return propertyset.set(i,*value);
  }
  bool getTypedElement(const OwningClass * object, uint i, ValueType * value )const{
    const Set<ValueType> & propertyset = getConstSetReference(object);
    if(i>=propertyset.size())return false;
    return propertyset.get(i,*value);
  }
  // sets the value of the property set at i
  bool setElement(void * object, uint i, const void * value)const{
    auto typedObject = reinterpret_cast<OwningClass*>(object);
    auto typedValue = reinterpret_cast<const ValueType*>(value);
    if(!typedObject)return false;
    return setTypedElement(typedObject,i,typedValue);
  }
  // gets the value of the property set at i
  bool getElement(const void * object, uint i, void * value)const{
    auto typedObject = reinterpret_cast<const OwningClass*>(object);
    auto typedValue = reinterpret_cast<ValueType*>(value);
    if(!typedObject)return false;
    return getTypedElement(typedObject,i,typedValue);
  }
  bool deserializeElement(void * ptr, uint i, std::istream & in)const{
    // get Object* from ptr
    Object *object = reinterpret_cast<Object*>(ptr);
    OwningClass * owningClass = dynamic_cast<OwningClass*>(object);
    if(!owningClass)return false;
    ValueType value;
    if(getCustomDeserializer()){
      if(!(getCustomDeserializer()->deserialize(&value,in)))return false;
    }else{
      if(!Deserializer<ValueType>::deserialize(&value,in))return false;
    }

    setTypedElement(owningClass,i,&value);
    return true;
  }
  bool serializeElement(void * ptr,uint i,  std::ostream & out)const{
    Object *object = reinterpret_cast<Object*>(ptr);
    OwningClass * owningClass = dynamic_cast<OwningClass*>(object);
    if(!owningClass)return false;
    ValueType value;
    getTypedElement(owningClass,i,&value);
    if(getCustomSerializer()){
      if(!(getCustomSerializer()->serialize(out,&value)))return false;
    }else{
      if(!Serializer<ValueType>::serialize(out,&value))return false;
    }
    return true;
  }


};




#define PROPERTYCOLLECTION(TYPE,NAME,ONADD,ONREMOVE)\
private:\
class PROPERTYCLASS(NAME) : public virtual TypedPropertySetInfo<ReflectableType,TYPE>{\
public:\
  SINGLETON( PROPERTYCLASS(NAME) ){setName("Numbers");}\
  Set<TYPE> & getMutableSetReference( ReflectableType * object )const{\
  return object->NAME();\
}\
  const Set<TYPE> & getConstSetReference(const ReflectableType * object )const{\
  return object->NAME();\
}\
};\
  STATIC_INITIALIZER(PROPERTYCLASS(NAME), { ReflectableType::propertiesSet() |= PROPERTYCLASSINSTANCE(NAME);});\
  PROPERTYSET(TYPE,NAME,ONADD,ONREMOVE);


template <typename T>
class Serializer<Set<T> >{
public:
  static bool serialize(std::ostream & stream, const Set<T> * value){  
    const Set<T> & val = *value;
    for(int i=0; i< val; i++){    
      T v = val.at(i);
      if(!Serializer<T>::serialize(stream,&v)){
        stream << "{"<<i<<"}";
      }
      if(i<val.size()-1)stream<<" ";
    }
    return true;
  };
};

template <typename T>
class Deserializer<Set<T> >{
public:
  static bool deserialize(Set<T> * value, std::istream & stream){
    Set<T> tmp;
    while(stream){
      T i;
      if(!Deserializer<T>::deserialize(&i,stream)){
        // break if any element could not be serialized
        return false;
      }
      tmp|=i;
    }
    *value = tmp;
    return true;
  }
};

/*
SERIALIZERS(Set<int>, { 
const Set<int> & val = *value;
for(int i=0; i< val; i++){    
stream<< val.at(i);
if(i<val.size()-1)stream<<" ";
}
},{
Set<int> & val = *value;
while(stream){
int i;
stream >> i;
val|=i;
}
});
*/
class Test : public virtual PropertyChangingObject, public virtual Log{
  REFLECTABLE_OBJECT(Test);
  SUBCLASSOF(Log);

public:
  Test(){
    Numbers()|= 1,3,4,6,7,98;
    Colors()|= Color("red");

  }
  PROPERTYCOLLECTION(int, Numbers,{logInfo("item added "<<item);  },{logInfo("item removed: "<<item);});  
  PROPERTYCOLLECTION(double, Doubles,{logInfo("item added "<<item);  },{logInfo("item removed: "<<item);});
  PROPERTYCOLLECTION(Color, Colors,{logInfo("item added "<<item);  },{logInfo("item removed: "<<item);});


};

class MySample : public Sample{

public:


  void setup(){

    Components()|=new Test();

    // create a sphere renderer
    auto sphereRenderer = new SphereRenderer();
    // add renderer to component set
    Components() |= sphereRenderer;

    // create a sphere with radius 0.5
    auto sphere = new Sphere(0.5);

    // add sphere to renderer
    *sphereRenderer |= sphere;

    // print setup of sample app
    application().printSetup();
    application().printHierarchy();
  }  
};

int main(int argc,  char ** argv){
  // instanciate sample
  MySample sample;

  // create sample application
  SampleApplication app(argc,argv, sample);

  // run sample application
  return app.run();
}