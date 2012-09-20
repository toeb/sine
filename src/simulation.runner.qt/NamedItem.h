#include <QStandardItem>
#include <core/Object.h>
namespace nspace{

 class NamedItem : public QStandardItem{
 private:
    NamedObject & _object;
 public:
   NamedItem(NamedObject & object):_object(object){
     setText(QString::fromStdString(object.name()));
     setEditable(false);
   }
 };
 

}