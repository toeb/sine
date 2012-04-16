#ifndef __RungeKuttaFehlberg45_h__
#define __RungeKuttaFehlberg45_h__
#include <Simulation/Integrators/SingleStepIntegrator.h>
namespace IBDS{

  /**
   * \brief Runge kutta fehlberg 45.
   * 				
   *    algorihm inspired by:
   *    http://math.fullerton.edu/mathews/n2003/rungekuttafehlberg/RungeKuttaFehlbergProof.pdf
   * modified stepsize calculation as seen in the script "gewoehnliche numerische
   * differentialgleichungen" by prof. Kiehl tu darmstadt.
   * 
   * programmed a similar version in mbslib (SIM.informatik.tu-darmstadt.de)
   *
   * \author Tobias Becker
   * \date 16.04.2012
   */
  class RungeKuttaFehlberg45 : public SingleStepIntegrator{
  private:
  ///< Size of the maximum step
  Real _maximumStepSize;
  ///< Size of the minimum step
  Real _minimumStepSize;
  ///< The tolerance
  Real _tolerance;
  ///< The alpha
  Real _alpha;
  ///< The beta
  Real _beta;
  ///< The gamma
  Real _gamma;
  public:

    /**
     * \brief Constructor.
     *
     * \author Tobias Becker
     * \date 16.04.2012
     *
     * \param tolerance       (optional) the tolerance.
     * \param initialStepSize (optional) size of the initial step.
     * \param alpha           (optional) alpha in (0,1] default 0.9 (reduction of new step size)
     * \param beta            (optional) beta in (0,1) default 0.5 lower bound of new step size h_new >= beta*h_old 
     * \param gamma           (optional)  gamma in (1,infinity) default 1.5 upper bound of new step size h_new <= gamma * h_old
     * \param maxStepSize     (optional) size of the maximum step.
     * \param minStepSize     (optional) size of the minimum step.
     */
    RungeKuttaFehlberg45(  
      Real tolerance = 0.001, 
      Real initialStepSize=0.01, 
      Real alpha=0.9,
      Real beta=0.5,
      Real gamma=1.5,
      Real maxStepSize = 0.1,
      Real minStepSize = 0.0001);
  protected:
    /**
   * <summary> Executes an integration step.</summary>
   *
   * <remarks> Tobias Becker, 13.04.2012.</remarks>
   */
  void doStep(const Real & h, VectorND & x_i);
  
  private:

  // coefficients used
  const Real y1,y2,y3,y4;
  const Real z1, z2, z3,z4,z5;
  const Real c21,c31,c32,c41,c42,c43,c51,c52,c53,c54,c61,c62,c63,c64,c65;
  };
}
#endif