#pragma once


#include <core/Object.h>
#include <core/Reflection.h>
#include <QAbstractItemModel>
#include <simulation.logging/Log.h>
#include <sstream>
namespace nspace{
  class ObjectPropertyViewModel : public QAbstractItemModel, public virtual PropertyChangingObject, public virtual Log{
    Q_OBJECT;
    REFLECTABLE_OBJECT(ObjectPropertyViewModel);
    SUBCLASSOF(Log);
    PROPERTY(Object *, CurrentObject){}


  public:
    void onPropertyChanged(const std::string  & name){
      if(name=="CurrentObject") reset();      
    }

    ObjectPropertyViewModel():_CurrentObject(0){}

    QModelIndex parent( const QModelIndex& index ) const {
      
      if(!index.isValid())return QModelIndex();
      return QModelIndex();
    }
    bool hasChildren(const QModelIndex& parent)const{      
      bool res = QAbstractItemModel::hasChildren(parent);      


      //logInfo(""<<parent.row()<<"."<<parent.column()<<" "<<res<<" ");
      return res;
    }
    const Property*  getProperty(const QModelIndex & index)const{
      if(!index.isValid())return 0;
      auto object = getCurrentObject();
      if(!object)return 0;
      int row = index.row();
      auto prop = object->getTypeData().Properties().at(row);      
      return prop;
    }

    bool setData(const QModelIndex & index, const QVariant & value, int role=Qt::EditRole){
      auto prop = getProperty(index);
      if(!prop)return false;
      std::string stdstring = value.toString().toUtf8().constData();
      auto object = getCurrentObject();
      std::stringstream ss(stdstring);
      bool result = prop->deserialize(object,ss);
      if(!result)logWarning("could not deserialize "<<prop->getPropertyName()<<" from string '"<<stdstring<<"'");
      return result;

    }
    
    Qt::ItemFlags flags(const QModelIndex & index)const{
      if(index.column()==1){
        Qt::ItemFlags result = QAbstractItemModel::flags(index)|Qt::ItemIsEditable;
        return result;
      }
      return QAbstractItemModel::flags(index);
    }
    QModelIndex index(int row, int column, const QModelIndex & parent=QModelIndex())const{    
      if(!hasIndex(row,column,parent))return QModelIndex();

      Object * currentObject = 0;
      if(parent.isValid()){
        currentObject = reinterpret_cast<Object*>(parent.internalPointer());
      }else{
        currentObject = getCurrentObject();
      }

      if(!currentObject)return QModelIndex();

      auto prop = currentObject->getTypeData().Properties().at(row);
      if(!prop)return QModelIndex();
      return createIndex(row,column,(void*)(Object*)prop);      
    }

    int rowCount(const QModelIndex &parent=QModelIndex())const{
      if(getCurrentObject()==0)return 0;

      return getCurrentObject()->getTypeData().Properties().size();

    }
    int columnCount(const QModelIndex &parent=QModelIndex())const{
      if(getCurrentObject()==0)return 0;
      return 2;
    }
    /*bool hasIndex(int row, int col)const{
      if(row >= rowCount())return false;
      if(col >= columnCount())return false;
      return true;

    }
    bool hasIndex(const QModelIndex & index)const{
      return hasIndex(index.row(),index.column());
    }*/
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole)const{      
      auto object = getCurrentObject();
      auto prop = getProperty(index);
      if(!prop)return QVariant();
    
      if(role==Qt::WhatsThisRole || role == Qt::ToolTipRole){
        return QVariant::fromValue(tr(prop->getPropertyDescription().c_str()));
      }

      //logInfo("getting data @"<<index.row()<<"."<<index.column()<<" role:"<<role); 
      if(role!=Qt::DisplayRole)return QVariant();
        
      if(index.column()==0) return QVariant::fromValue(tr(prop->getPropertyDisplayName().c_str()));      

      else if(index.column()==1) {
        std::stringstream ss;
        prop->serialize(object,ss);
        auto str =tr(ss.str().c_str());
        return QVariant::fromValue(str);     
      }
    }

  };
}
