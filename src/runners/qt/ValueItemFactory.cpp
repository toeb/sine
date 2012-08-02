#include "ValueItemFactory.h"
#include <runners/qt/DoubleItem.h>
#include <runners/qt/NamedItem.h>
#include <runners/qt/IValueItem.h>
#include <simulation/access/MatrixValue.h>
#include <simulation/access/IValue.h>

using namespace nspace;
using namespace std;

void ValueItemFactory::create(QStandardItem& parent,  IComponent * component){
   
  if(!component)return;


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
        row << new DoubleItem(matrixItem->value(i,j));
      }
      namedItem->appendRow(row);
    }
    
    parent.appendRow(namedItem);
    return;
  }
  if(value){
    row << new NamedItem(*value);
    row << new IValueItem(*value);
    parent.appendRow(row);
    return;
  }
  auto group = dynamic_cast<Group*>(component);
  if(group){
    NamedItem * item = new NamedItem(*group);
    
   group->foreachComponent([item](IComponent * component){
     create(*item,component);
   });
   parent.appendRow(item);
  }


 


 }

