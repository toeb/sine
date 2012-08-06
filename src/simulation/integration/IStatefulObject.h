#pragma once

#include <simulation/core/ISimulationObject.h>
#include <simulation/integration/State.h>
#include <common/patterns/Composite.h>

namespace nspace{

/**
 * \brief Super class of integrable objects. Allows access to the state and its derivative.
 *
 */
class IStatefulObject : public virtual ISimulationObject{
public:
  
  void operator>>(IState & x)const{
    exportState(x);
    
  }
  void operator<<(const IState & state){
    importState(state);
  }

   /**
    * \brief Gets the dimension of the state of this IIntegrable
    * 			 
    * \return The state dimension.
    */
   virtual unsigned int stateDimension()const=0;

   /**
    * \brief Gets the available number of derivatives.
    *
    * \return The available derivatives.
    */
   virtual unsigned int availableDerivatives()const=0;
 /**
   * \brief Sets the state this integratable.
   * 				
   * \param x The state.
   */
  virtual void importState(const IState & x)=0;

  /**
   * \brief Gets the state of this integrable.
   * \param [out] x the state.
   */
  virtual void exportState(IState & x)const=0;

  /**
   * \brief Gets the last derived state.
   * 				
   * 				xDot is the derivative of the state
   */
  virtual void exportDerivedState(IState & xDot)const=0;

	void resizeState(IState & x)const{
    uint dim = stateDimension();
    uint derivs =availableDerivatives();
		if(x.dimension() == dim && x.derivatives() >= derivs)return;
		x.resize(dim,derivs);
	}
private:
protected:
	
  


};


}