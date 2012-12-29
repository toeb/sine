#pragma once

#include <string>

#include <core/Node.h>
#include <simulation.model/Model.h>
#include <simulation.model/Connector.h>
#include <simulation.model/Connection.h>

#include <core/Object.h>

namespace nspace{
  class IModelBuilder : public virtual Object{
    TYPED_OBJECT(IModelBuilder);
  public:
    virtual Model* beginModel()=0;

    ModelNode * addBody(const std::string & name);
    ModelNode * addConnection(const std::string & name, const std::string  & bodyA, const std::string & bodyB);

    virtual ModelNode* addNode()=0;

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