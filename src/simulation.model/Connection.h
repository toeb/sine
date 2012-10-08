#pragma once

#include <core/Set.h>
#include <math/core.h>

#include <simulation.model/ModelElement.h>
#include <simulation.model/Connector.h>
namespace nspace{

  class Connection :public NamedObject{
    TYPED_OBJECT(Connection)
  public:
    std::string type;
    Vector3D axis;
  };

  class JointLimit : public NamedObject {
    TYPED_OBJECT(JointLimit)
  private:
    Real _lowerPosition;
    Real _upperPosition;
    Real _velocity;
    Real _effort;
  public:
    Real & lowerPosition(){return _lowerPosition;}
    Real & upperPosition(){return _upperPosition;}
    Real & velocity(){return _velocity;}
    Real & effort(){return _effort;}
  };

  namespace model{
    class Spring : public Connection{
        TYPED_OBJECT(Spring);
    private:
      Real _dampeningCoefficient;
      Real _springCoefficient;
      Real _neutralLength;
    public:
    };

    namespace joint{
      enum JointType{
        Prismatic, Rotational, Fixed,
      };
    }

    class Joint : public Connection{
      TYPED_OBJECT(Joint)
    private:
      joint::JointType _type;
    public:
    };
  }
}
