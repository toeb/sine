#pragma once

#include <Simulation/ISimulationObject.h>
#include <Simulation/Force/DampedSpring.h>
#include <vector>
namespace IBDS{
class TextileModel : public ISimulationObject{
private:
  std::vector<DampedSpring> _elongationSprings;
  std::vector<DampedSpring> _shearSprings;
  std::vector<DampedSpring> _flexionSprings;

  Real _k_d_elongation;
  Real _k_d_shear;
  Real _k_d_flexion;
  Real _k_s_elongation;
  Real _k_s_shear;
  Real _k_s_flexion;

public:
  void setElongationSpringConstant(Real k_d_e);
  void setShearSpringConstant(Real k_d_s);
  void setFlexionSpringConstant(Real k_d_f);
  void setElongationDampeningConstant(Real k_d_e);
  void setShearDampeningConstant(Real k_d_s);
  void setFlexionDampeningConstant(Real k_d_f);

  Real getElongationSpringConstant(Real k_d_e)const;
  Real getShearSpringConstant(Real k_d_s)const;
  Real getFlexionSpringConstant(Real k_d_f)const;
  Real getElongationDampeningConstant(Real k_d_e)const;
  Real getShearDampeningConstant(Real k_d_s)const;
  Real getFlexionDampeningConstant(Real k_d_f)const;

  static TextileModel * createTextileModel(int gridwidth, int gridheight);
  
  void normalize();
};
}