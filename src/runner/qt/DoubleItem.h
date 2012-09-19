#include <runner/qt/ValueItem.h>
namespace nspace{

 class DoubleItem: public ValueItem{
   double & _value;
 public:
   DoubleItem(double & value):_value(value){

   }
   virtual void set( std::istream & is ){is >> _value;}
   virtual void get( std::ostream & os ) const{os << _value;}

 protected:
 };

}