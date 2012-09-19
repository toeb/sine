#pragma once

#include <string>

#include <common/Node.h>
#include <simulation.model/Model.h>
#include <simulation.model/Connector.h>
#include <simulation.model/Connection.h>


namespace nspace{
  class IModelBuilder{
  public:
    virtual Model* beginModel()=0;

    Node * addBody(const std::string & name);
    Node * addConnection(const std::string & name, const std::string  & bodyA, const std::string & bodyB);
    

    virtual Node* addNode()=0;   


    virtual Connector* addConnector(const std::string &nodeName)=0;
    virtual Connection* addConnection(const std::string & nodeNameA, const std::string & nodeNameB)=0;
    virtual Model * endModel()=0;

    virtual Model * currentModel()=0;

    template<typename T>
    T * element(const std::string & name){
      ModelElement * me = element(name);
      T * res = dynamic_cast<T*>(me);
      return res;
    }
  
    virtual ModelElement * element(const std::string & name)=0;

  };




}