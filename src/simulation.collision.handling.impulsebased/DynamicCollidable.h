#pragma once
#include <simulation/composites/CompositeSimulationObject.h>
#include <simulation.dynamics/DynamicBody.h>
#include <simulation.collision/Collidable.h>
namespace nspace{
  
class DynamicCollidable : public Collidable, public virtual CompositeSimulationObject{
TYPED_OBJECT;
private:
  DynamicBody * _dynamicBody;

  Real _elasticityCoefficient;
  Real _staticFrictionCoefficient;
  Real _dynamicFrictionCoefficient;

  DynamicCollidable(ISimulationObject & collisionObject, DynamicBody & body, Real elasticity = 1, Real staticFriction = 1, Real dynamicFriction = 1);
 
public:


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
