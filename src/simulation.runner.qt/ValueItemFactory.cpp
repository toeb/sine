#include "ValueItemFactory.h"
#include <simulation.runner.qt/DoubleItem.h>
#include <simulation.runner.qt/NamedItem.h>
#include <simulation.runner.qt/IValueItem.h>
#include <simulation.access/MatrixValue.h>
#include <simulation.access/IValue.h>

using namespace nspace;
using namespace std;

Set<ValueItem*> ValueItemFactory::create(QStandardItem& parent,  IComponent * component){
   Set<ValueItem*> items;
  if(!component)return items;


  QList<QStandardItem*> row;


  auto value =dynamic_cast<IValue*>(component);
  auto matrixItem = dynamic_cast<MatrixValue*>(component);
  if(matrixItem){
    auto namedItem = new NamedItem(*component);

    for(int i =0; i < matrixItem->rows();i++){
      row.clear();
      for(int j=0; j <matrixItem->cols(); j++){
        stringstream ss;
        ss << "a"<<(i+1)<<(j+1);

        row<< new QStandardItem(QString::fromStdString(ss.str()));
        auto item = new DoubleItem(matrixItem->value(i,j));
        row << item;
        items |= item;
      }
      namedItem->appendRow(row);
    }
    
    parent.appendRow(namedItem);
    return items;
  }
  if(value){
    row << new NamedItem(*value);
    auto item = new IValueItem(*value);
    row << item;
    items|=item;
    parent.appendRow(row);
    return items;
  }
  auto group = dynamic_cast<Group*>(component);
  if(group){
    NamedItem * item = new NamedItem(*group);
    
   group->foreachComponent([item,&items](IComponent * component){
     items |= create(*item,component);
   });
   parent.appendRow(item);

   return items;
  }


 


 }

