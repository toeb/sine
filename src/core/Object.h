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

#include <config.h>
#include <ostream>
#include <string>




#define DS_CLASS_DECLARATION(TYPE)                                  \
private:                                                            \
  typedef TYPE CurrentClassType;                                    \
public:                                                             \
  static std::string getTypeName();                                 \
  virtual inline const nspace::Type * getType() const;              \
  virtual inline bool isInstanceOf(const nspace::Type * type) const;\
private:

#define DS_CLASS_DEFINITION(TYPE)                                                                                       \
 std::string TYPE::getTypeName(){return std::string(# TYPE); }                                                          \
 const nspace::Type * TYPE::getType() const {return nspace::TypeInfo<CurrentClassType>::instance(); }                   \
 bool TYPE::isInstanceOf(const nspace::Type * type) const { return type->isSuperClassOf(this->getType()); }

namespace nspace {
  //forward declaration for Type
  class Type;
  /**
  * \brief Base class.  Contains Type information and some standard methods like the streamout operator <<.
  *
  */
  class Object {
    DS_CLASS_DECLARATION(Object)
  private:
  public:

    /**
    * \brief Default constructor.
    */
    Object();

    /**
    * \brief virtual Destructor.
    */
    virtual ~Object();

    /**
    * \brief toString method converts this object to a string representation (should be
    *        overridden by subclasses)
    *
    * \param [in,out]  out The outputstream were the string is written to.
    */
    virtual void toString(std::ostream & out) const;

    /**
    * \brief  converts object to a string
    *         usesthe toString(out) method to create a std::string which is returned
    *
    * \return  This object as a std::string.
    */
    std::string toString() const;

    /**
    * \brief Stream insertion operator.
    *
    * \param [in,out]  out The output stream.
    * \param obj           The object.
    *
    * \return  The shifted result.
    */
    friend std::ostream & operator << (std::ostream & out, const Object * obj);

    /**
    * \brief Stream insertion operator.
    *
    * \param [in,out]  out The output stream.
    * \param obj           The object.
    *
    * \return  The shifted result.
    */
    friend std::ostream & operator << (std::ostream & out, const Object & obj);

    /**
    * \brief Equality operator.
    *
    * \param a The first instance to compare.
    * \param b The second instance to compare.
    *
    * \return  true if the parameters are the same object (in memory).
    */
    friend bool operator == (const Object & a, const Object & b){
      return &a==&b;
    }
  };

}
