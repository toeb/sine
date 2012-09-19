#include <QStandardItem>
#include <simulation.access/IComponent.h>
namespace nspace{
 class ValueItemFactory{
 public:
   static void create(QStandardItem& parent,  IComponent * component);
 };
}