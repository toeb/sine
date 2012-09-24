#pragma once
#include <QStandardItem>
#include <QTimer>
#include <QItemDelegate>

#include <sstream>

#include <simulation.access/IValue.h>
namespace nspace{

 class IValueItem : public ValueItem{
 private:
   IValue & _value;
 public:
   IValue & value(){
     return _value;
   }
   const IValue& value()const{
     return _value;
   }
   IValueItem(IValue & value):_value(value){

   }
 protected:
   virtual void set( std::istream & is ){
     value().fromString(is);
   }
   virtual void get( std::ostream & os ) const{
     value().toString(os);
   }
 };




}