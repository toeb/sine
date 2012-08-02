#include <QStandardItem>
#include <simulation/core/ISimulationObject.h>
namespace nspace{

 class NamedItem : public QStandardItem{
 private:
    ISimulationObject & _object;
 public:
   NamedItem(ISimulationObject & object):_object(object){
     setText(QString::fromStdString(object.getName()));
     setEditable(false);
   }
 };
 

}