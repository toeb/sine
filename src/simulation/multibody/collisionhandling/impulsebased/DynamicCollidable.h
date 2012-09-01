#pragma once
#include <Simulation/Collision/Collidable.h>
#include <Simulation/Dynamics/DynamicBody.h>
#include <Simulation/Core/CompositeSimulationObject.h>
namespace IBDS{
  
class DynamicCollidable : public Collidable, public virtual CompositeSimulationObject{
private:
  DynamicBody * _dynamicBody;

  Real _elasticityCoefficient;
  Real _staticFrictionCoefficient;
  Real _dynamicFrictionCoefficient;

  DynamicCollidable(ISimulationObject & collisionObject, DynamicBody & body, Real elasticity = 1, Real staticFriction = 1, Real dynamicFriction = 1);
 
public:
  static const TypeId type;
  const TypeId getType()const{return DynamicCollidable::type;}

  static DynamicCollidable * create(ISimulationObject * simulationObject,Real elasticity = 1, Real staticFriction = 1, Real dynamicFriction = 1);
  static DynamicCollidable * create(ISimulationObject & collisionObject, DynamicBody & body,Real elasticity = 1, Real staticFriction = 1, Real dynamicFriction = 1);
  
  /**
  * Returns the underlying body
  */
  inline DynamicBody  & dynamicBody(){return *_dynamicBody;};


  Real getElasticityCoefficient()const;
  Real getStaticFrictionCoefficient()const;
  Real getDynamicFrictionCoefficient()const;

  void setElasticityCoefficient(Real e);
  void setStaticFrictionCoefficient(Real s);
  void setDynamicFrictionCoefficient(Real d) ;
};
}
