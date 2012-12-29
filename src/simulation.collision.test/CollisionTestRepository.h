#pragma once
#include <simulation.collision.test/CollisionTest.h>
#include <simulation.collision/Collidable.h>
#include <map>
namespace nspace{
  class CollisionTestRepository{
  private:
    std::vector<const CollisionTest*> _tests;
    CollisionTestRepository();
  public:

    /**
    * \brief Singleton Access to the CollisionTestRepository
    *
    * \return .
    */
    static CollisionTestRepository & instance();

    /**
    * \brief Adds a Collisiontest to the repository.
    *
    *
    * \param test The test.
    */
    void addTest(const CollisionTest* test);

    /**
    * \brief gets the Collisiontest.
    *
    *
    * \param a type of collidable a.
    * \param b type of collidable b.
    *
    * \return null if it fails, else the test.
    */
    const inline CollisionTest* getTest(const TypeId a,const TypeId b)const{
      const CollisionTest * current=0;
      for(int i=0; i < _tests.size(); i++){
        current = _tests.at(i);
        if(current->getTypeA()==a && current->getTypeB()==b){
          return current;
        }
      }
      return 0;
    }

    const CollisionTest* getTest(const ISimulationObject & a,const ISimulationObject & b)const;

    const inline CollisionTest * operator()(const TypeId a,const TypeId b)const{return getTest(a,b);}
    const inline CollisionTest * operator()(const ISimulationObject & a,const ISimulationObject & b)const{return getTest(a,b);}

    bool hasTest(const ISimulationObject & a,const ISimulationObject & b);
    bool hasTestFor(const ISimulationObject & a)const;
    bool hasTestFor(const TypeId a)const;
  };
}
