#pragma once

#include <simulation.model/builder/IModelBuilder.h>

#include <core/Set.h>

namespace nspace{

  class ModelBuilderBase : public IModelBuilder, public Set<ModelElement*> {
    TYPED_OBJECT(ModelBuilderBase);
  private:  
    Set<Model*> _models;
    Model * _currentModel;
    ModelElement * _currentElement;
  protected:
    virtual ModelNode * createNode();
    virtual Connection * createConnection();
    virtual Connector * createConnector();
  public:    
    virtual void buildModel(Model & model)=0;

    ModelBuilderBase();
    void reset();
    const Set<Model*> models()const;
    Model * currentModel();
    Model * beginModel();
    Model * endModel();
    ModelNode * addNode();
    Connector * addConnector(const std::string & nodeName);
    Connection * addConnection(const std::string & nodeAm, const std::string & nodeB);
    template<typename T>
    T * select(const std::string & name);

    ModelElement * element(const std::string  &name);
  private:

    void addElement(ModelElement * element);
  };

  //template implementation
  template<typename T>
  T * ModelBuilderBase::select(const std::string & name){
    return dynamic_cast<T*>(selectFirst([&name](T* element){element->name() == name;}));
  }


}