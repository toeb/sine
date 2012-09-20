#pragma once

#include <simulation.model/builder/IModelBuilder.h>

#include <core/Set.h>

namespace nspace{

  class ModelBuilderBase : public IModelBuilder, public Set<ModelElement*> {
  private:  
    Model * _currentModel;
    ModelElement * _currentElement;
  protected:
    virtual Node * createNode(){return new Node;};
    virtual Connection * createConnection(){return new Connection;}
    virtual Connector * createConnector(){return new Connector;}
  public:    
    virtual void buildModel(Model & model)=0;
  

    ModelBuilderBase(){
      reset();
    }
    void reset(){
      _currentModel=0;
      _currentElement=0;
    }
    Model * currentModel(){
      return _currentModel;
    }
    Model * beginModel(){
      _currentModel = new Model();            
      addElement(_currentModel);
      return _currentModel;
    }
    Model * endModel(){
      buildModel(*_currentModel);
      Model * model = _currentModel;
      _currentModel =0;
      return model;
    }
    Node * addNode(){
      Node * node = createNode();
      //addElement(node);
      _currentModel->nodes().add(node);
      return node;   
    }
    Connector * addConnector(const std::string & nodeName){
      return 0;
    }
    Connection * addConnection(const std::string & nodeAm, const std::string & nodeB){
      Connection * connection = createConnection();
   //   addElement(connection);
//      _currentModel->connections().add(connection);
      return connection;
    }
    template<typename T>
    T * select(const std::string & name){
      return dynamic_cast<T*>(selectFirst([&name](T* element){element->name() == name;}));
    }

    ModelElement * element(const std::string  &name){
      return Query<ModelElement*>::selectFirst(elements(),[&name](ModelElement* element){return element->name()==name;});
    }
  private:
    
    void addElement(ModelElement * element){
      _currentElement = element;
      Set<ModelElement*>::add(element);
    }

  };
}