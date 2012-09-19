#include <runner/qt/ValueItem.h>
#include <QItemDelegate>
namespace nspace{

 class ValueItemDelegate : public QItemDelegate{
   Q_OBJECT;
 public:
   ValueItemDelegate(QWidget * parent=0):QItemDelegate(parent){
     
   }
   ValueItem * getValueItem(const QModelIndex & index)const{
     const QStandardItemModel * standardItemModel = dynamic_cast<const QStandardItemModel*>(index.model());
      if(!standardItemModel)return 0;
      QStandardItem * standardItem = standardItemModel->itemFromIndex(index);
      ValueItem* valueItem = dynamic_cast<ValueItem*> (standardItem);
      if(!valueItem)return 0;
      return valueItem;
   }
   virtual void setEditorData(QWidget *editor, const QModelIndex &index) const{
     auto valueItem = getValueItem(index);
     if(valueItem){
       if(!editor->isVisible()){
         valueItem->setRefresh(false);
       }
     }
     QItemDelegate::setEditorData(editor,index);
     
   }

   virtual void setModelData(QWidget *editor,
     QAbstractItemModel *model,
     const QModelIndex &index) const{
       auto valueItem = getValueItem(index);
       if(valueItem){
         valueItem->setRefresh(true);
         
       }
       QItemDelegate::setModelData(editor,model,index);
   }

 };


}