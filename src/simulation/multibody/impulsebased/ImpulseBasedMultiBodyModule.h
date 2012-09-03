#pragma once
#include <simulation/multibody/impulsebased/Joint.h>
#include <simulation/core/SimulationModuleBase.h>
#include <simulation/timing/Timeable.h>

#include <vector>

namespace nspace{
  
class ImpulseBasedMultiBodyModule : public SimulationModuleBase<Joint>,public virtual Timeable{
private:
  Real _normalisation;
  ///< The position tolerance
  Real _eps_p;
  ///< The the velocity tolerance
  Real _eps_v;
  ///< The maximum number of iterations
  int _maxIterations;
  ///< The iterations used in last step
  int _iterations;
  std::vector<Joint *> _temporaryJoints;
public:

  /**
   * \brief Correct positions loop is executed on all joints.
   *
   * 
   *
   * \param h The stepsize used.
   */
  void correctPositions(Real h);

  /**
   * \brief Corrects  velocities.
   *
   * 
   */
  void correctVelocities();


  int getLastNumberOfIterations()const;
  ImpulseBasedMultiBodyModule(int maxIterations=20, Real normalisation=100, Real positionTolerance=10e-3, Real velocityTolerance=10e-4);
  
  void foreachJoint(std::function<void(Joint *)> f){
    this->foreachObject(f);
    std::for_each(_temporaryJoints.begin(), _temporaryJoints.end(),f);
  }

  void clearTemporaryJoints(){
    _temporaryJoints.clear();
  }

  void addTemporaryJoint(Joint & j){
    _temporaryJoints.push_back(&j);
  }
  

};

}