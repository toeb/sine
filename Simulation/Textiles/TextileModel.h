#pragma once

#include <Simulation/ISimulationObject.h>
#include <Simulation/Force/DampedSpring.h>
#include <vector>
#include <Simulation/Dynamics/Particle.h>

namespace IBDS{

struct TextileNode{
  
  TextileNode * nodeNorth;
  TextileNode * nodeEast;
  TextileNode * nodeSouth;
  TextileNode * nodeWest;

  Particle * particle;

  DampedSpring * elongationNorth;
  DampedSpring * elongationEast;
  DampedSpring * elongationSouth;
  DampedSpring * elongationWest;

  DampedSpring * shearNorthEast;
  DampedSpring * shearSouthEast;
  DampedSpring * shearSouthWest;
  DampedSpring * shearNorthWest;

  DampedSpring * flexionNorth;
  DampedSpring * flexionEast;
  DampedSpring * flexionSouth;
  DampedSpring * flexionWest;
};

class TextileModel : public ISimulationObject{
private:
  int rows;
  int columns;
  Real spacing;
  Real particleMass;
  std::vector<DampedSpring*> _nodes;

  std::vector<DampedSpring*> _elongationSprings;
  std::vector<DampedSpring*> _shearSprings;
  std::vector<DampedSpring*> _flexionSprings;

  Real _k_d_elongation;
  Real _k_d_shear;
  Real _k_d_flexion;
  Real _k_s_elongation;
  Real _k_s_shear;
  Real _k_s_flexion;
  TextileModel();
public:
  
  TextileNode& getNode(int i, int j);


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

  static TextileModel * createTextileModel(int gridrows, int gridcolumns, const Vector3D & topleft, const Vector3D & bottomright, const Vector3D & normal);
  
  void normalize();
};
}