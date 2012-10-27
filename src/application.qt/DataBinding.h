#pragma once

#include <memory>

#include <core/Reflection.h>
#include <core.logging.h>


#include <QObject>
#include <QLineEdit>
namespace nspace{
  class LineEditDataBinding : 
    public QObject, 
    public virtual PropertyChangingObject, 
    public virtual PropertyChangedListener, 
    public virtual Log
  {
    Q_OBJECT;
    REFLECTABLE_OBJECT(LineEditDataBinding);
  public:
    enum BindingType{
      OneWay,
      TwoWay,
      OneWayToSource
    };

    PROPERTY(QLineEdit * , Target){      
      if(oldvalue)disconnect();
      if(newvalue)connect(newvalue,SIGNAL(editingFinished()),this,SLOT(targetChanged()));
      if(newvalue)connect(newvalue,SIGNAL(textEdited(const QString& )),this,SLOT(targetChanged()));
    }
    PROPERTY(std::string, PropertyName){}
    PROPERTY(PropertyChangingObject*, Source){
      if(oldvalue)oldvalue->listeners()/=this;
      if(newvalue)newvalue->listeners()|= this;
    }
    PROPERTY(BindingType, BindingType){}
    PROPERTY(const Property*, Property){}
    
    bool _propertyChanging;//don't know if i realy need this 
  public:
    LineEditDataBinding():_propertyChanging(false),_Source(0),_Target(0),_BindingType(TwoWay),_Property(0)
    {}
    ~LineEditDataBinding(){
      setSource(0);
      setTarget(0);
    }
    

    void onPropertyChanged(Object * sender, const std::string & propertyName){
      if(propertyName!=_PropertyName)return;
      auto source = getSource();
      if(!source)return;
      auto prop= source->getTypeData().getProperty(propertyName);
      if(!prop)return;
      std::stringstream ss;
      prop->serialize(sender,ss);
      auto target = getTarget();
      if(!target)return;      
      _propertyChanging = true;
      target->setText(tr(ss.str().c_str()));
      _propertyChanging=false;
    }

    public slots:
      void targetChanged(){
        logInfo("TextChanged");
        if(_propertyChanging)return;
        auto target =getTarget();
        if(!target)return; //this should never happen
        auto source = getSource();
        if(!source)return;
        auto prop =source->getTypeData().getProperty(_PropertyName);
        if(!prop)return ;
        std::string text = target->text().toUtf8().data();
        std::stringstream ss(text);
        prop->deserialize((void*)(Object*)source,ss);
      }


  };
}