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
#include <core/Object.h>
#include <core/Serialization.h>
#include <core/reflection/MemberInfo.h>
namespace nspace {

  /**
   * \brief Information about a property.
   */
  class PropertyInfo : public virtual MemberInfo {
    TYPED_OBJECT(PropertyInfo);
    SUBCLASSOF(MemberInfo);
    SIMPLE_PROPERTY(bool, HasGetter){}
    SIMPLE_PROPERTY(bool, HasSetter){}
    // the typedata of the property
    SIMPLE_PROPERTY(const Type *, PropertyType){}
    // access to the default value
    SIMPLE_PROPERTY(const void *, DefaultValue){}
    // custom serializer
    SIMPLE_PROPERTY(CustomSerializer*, CustomSerializer){}
    // custom deserializer
    SIMPLE_PROPERTY(CustomDeserializer*, CustomDeserializer){}
    BASIC_PROPERTY(std::function<Object* (void *)>, ObjectConverter,public,,,);
    SIMPLE_PROPERTY(bool, IsNavigatable){}
    SIMPLE_PROPERTY(bool, IsPointer){}
    SIMPLE_PROPERTY(bool, IsVisible){}
public:

    /**
     * \brief Default constructor.
     */
    PropertyInfo() :
      _HasGetter(false),
      _HasSetter(false),
      _PropertyType(0),
      _DefaultValue(0),
      _CustomSerializer(0),
      _CustomDeserializer(0),
      _ObjectConverter([] (void * ptr){return static_cast<Object*>(0); }),
      _IsNavigatable(false),
      _IsPointer(false),
      _IsVisible(true)
    {}

    /**
     * \brief sets this property to the default value.
     *
     * \param [in,out]  object  If non-null, the object.
     */
    void setToDefaultValue(Object * object) const {
      if(getDefaultValue()) setValue(object,getDefaultValue());
    }

    /**
     * \brief sets the value of the property.
     *
     * \param [in,out]  object  If non-null, the object.
     * \param value             The value.
     */
    virtual void setValue(Object * object, const void * value) const=0;

    /**
     * \brief gets the value of the property.
     *
     * \param object          The object.
     * \param [in,out]  value If non-null, the value.
     */
    virtual void getValue(const Object * object, void * value) const=0;

    /**
     * \brief if the value is a pointer and a subtype of object this method returns the pointer as an
     *        Object.
     *
     * \param object  The object.
     *
     * \return  null if it fails, else.
     */
    Object * asObjectPointer(const Object * object) const {
      if(!getIsPointer()) return 0;
      void * value;
      getValue(object,&value);
      return getObjectConverter() (value);
    }

    /**
     * \brief Gets mutable pointer.
     *
     * \param [in,out]  object  If non-null, the object.
     *
     * \return  null if it fails, else the mutable pointer.
     */
    virtual void * getMutablePointer(Object * object) const {
      return 0;
    }

    /**
     * \brief Gets constant pointer.
     *
     * \param object  The object.
     *
     * \return  null if it fails, else the constant pointer.
     */
    virtual const void * getConstPointer(const Object * object) const {
      return 0;
    }

    /**
     * \brief Deserializes.
     *
     * \param [in,out]  object  If non-null, the object.
     * \param [in,out]  in      The in.
     *
     * \return  true if it succeeds, false if it fails.
     */
    virtual bool deserialize(Object * object, std::istream & in) const=0;

    /**
     * \brief Serializes.
     *
     * \param [in,out]  object  If non-null, the object.
     * \param [in,out]  out     The out.
     *
     * \return  true if it succeeds, false if it fails.
     */
    virtual bool serialize(Object * object, std::ostream & out) const=0;

    /**
     * \brief Adds an observer to 'observer'.
     *
     * \param [in,out]  object    If non-null, the object.
     * \param [in,out]  observer  If non-null, the observer.
     *
     * \return  true if it succeeds, false if it fails.
     */
    virtual bool addObserver(Object * object,ObjectObserver* observer) const;

    /**
     * \brief Removes the observer.
     *
     * \param [in,out]  object    If non-null, the object.
     * \param [in,out]  observer  If non-null, the observer.
     *
     * \return  true if it succeeds, false if it fails.
     */
    virtual bool removeObserver(Object * object,ObjectObserver* observer) const;


    /**
     * \brief Gets.
     *
     * \param [in,out]  value The value.
     * \param object          The object.
     */
    template<typename ObjectType, typename T>
    void get(T& value, const ObjectType & object) const {
      getValue(&object,&value);
    }

    /**
     * \brief Sets.
     *
     * \param value             The value.
     * \param [in,out]  object  The object.
     */
    template<typename ObjectType, typename T>
    void set(const T& value, ObjectType & object) const {
      setValue(&object,&value);
    }
  };

  /**
   * \brief sets all properties of the specified object to default.
   *
   * \tparam  typename T  Type of the typename t.
   * \param [in,out]  object  The object.
   */
  template <typename T> void setToDefault(T & object){
    typeof(T)->Properties().foreachElement([&object](const PropertyInfo * prop){
                                             prop->setToDefaultValue(&object);
                                             //cout << "setting "<<prop->getName()<<" to default"<<endl;
                                           });
  }
}
