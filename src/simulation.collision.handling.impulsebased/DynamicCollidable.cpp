#include "DynamicCollidable.h"
using namespace nspace;
using namespace std;


DynamicCollidable::DynamicCollidable(
        ISimulationObject & collisionObject,
        DynamicBody & body,
        Real elasticity,
        Real staticFriction,
        Real dynamicFriction
        ):Collidable(collisionObject),
    _dynamicBody(&body),
    _elasticityCoefficient(elasticity),
    _staticFrictionCoefficient(staticFriction),
    _dynamicFrictionCoefficient(dynamicFriction){
    addComponent(&collisionObject);
    addComponent(&body);
}




DynamicCollidable *DynamicCollidable::create(
        ISimulationObject & collisionObject,
        DynamicBody & body,
        Real elasticity,
        Real staticFriction,
        Real dynamicFriction){
    return new DynamicCollidable(collisionObject,body,elasticity,staticFriction,dynamicFriction);
}

DynamicCollidable * DynamicCollidable::create(ISimulationObject * obj,
                                              Real elasticity,
                                              Real staticFriction,
                                              Real dynamicFriction){
    if(!obj)return 0;
    Geometry * geometry = dynamic_cast<Geometry*>(obj);
    DynamicBody * body = dynamic_cast<DynamicBody*>(obj);

    if(!(geometry&&body)){
        return 0;
    }
    return create(*geometry,*body,elasticity,staticFriction,dynamicFriction);
}



Real DynamicCollidable::getElasticityCoefficient() const {
    return _elasticityCoefficient;
}

Real DynamicCollidable::getStaticFrictionCoefficient() const {
    return _staticFrictionCoefficient;
}

Real DynamicCollidable::getDynamicFrictionCoefficient() const {
    return _dynamicFrictionCoefficient;
}


void DynamicCollidable::setElasticityCoefficient(Real e) {
    _elasticityCoefficient = e;
}

void DynamicCollidable::setStaticFrictionCoefficient(Real s) {
    _staticFrictionCoefficient = s;
}

void DynamicCollidable::setDynamicFrictionCoefficient(Real d) {
    _dynamicFrictionCoefficient = d;
}
