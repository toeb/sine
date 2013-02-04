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
#include "Object.h"
#include <sstream>
#include <string>
#include <core/reflection/PropertyInfo.h>
#include <core/NamedObject.h>
using namespace nspace;
using namespace std;

std::string Object::toString() const {
  stringstream ss;
  toString(ss);
  return ss.str();
}

void Object::toString(std::ostream & out) const {
  if(nspace::hasObjectName(this)) {
    out << name(this);
    return;
  }
  out << "<object typeid=\""<<getType()<<"\" typename=\""<< getType().getName() << "\"/>";
}
Object::Object(){}
namespace nspace {
  std::ostream & operator << (std::ostream & out, const Object & obj){
    obj.toString(out);
    return out;
  }
  std::ostream & operator << (std::ostream & out, const Object * obj){
    if(!obj) return out << "Null";
    out << *obj;
    return out;
  }
}

Object::~virtual ~Object(){}