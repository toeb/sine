#pragma once

#include <Simulation/ISimulationObject.h>
#include <Simulation/Force/DampedSpring.h>
#include <vector>
#include <Simulation/Dynamics/Particle.h>
#include <Simulation/Dynamics/ParticleConnector.h>
#include <Math/Matrix3x3.h>
#include <Math/Vector3D.h>
#include <functional>

namespace IBDS{

struct TextileNode{
  TextileNode():
    connector(0),
      particle(0),
    north(0), south(0), east(0), west(0),
    northElongator(0),eastElongator(0),
    westElongator(0), southElongator(0),
    northEastShearer(0), southEastShearer(0), 
    southWestShearer(0), northWestShearer(0),
    northFlexor(0), southFlexor(0), westFlexor(0), eastFlexor(0){};


  TextileNode * north;
  TextileNode * east;
  TextileNode * south;
  TextileNode * west;

  ParticleConnector * connector;
  Particle * particle;

  DampedSpring * northElongator;
  DampedSpring * eastElongator;
  DampedSpring * southElongator;
  DampedSpring * westElongator;

  DampedSpring * northEastShearer;
  DampedSpring * southEastShearer;
  DampedSpring * southWestShearer;
  DampedSpring * northWestShearer;

  DampedSpring * northFlexor;
  DampedSpring * eastFlexor;
  DampedSpring * southFlexor;
  DampedSpring * westFlexor;
};

class TextileModel : public ISimulationObject{
private:
  int _rows;
  int _columns;
  Real _mass;

  Real _k_d_elongation;
  Real _k_d_shear;
  Real _k_d_flexion;
  Real _k_s_elongation;
  Real _k_s_shear;
  Real _k_s_flexion;


  TextileModel();
  void forAll(std::function<void(int, int)> f);
  void forAllNodes(std::function<void(int, int, TextileNode *)> f);
  DampedSpring *  createSpring(TextileNode * a, TextileNode * b, Real k_s, Real k_d);
  Particle * createParticle(TextileNode * node, Real mass, const Vector3D & position);


  void addSimulationObject(ISimulationObject *  object);

  void buildModel(
    const Vector3D & p, 
    const Matrix3x3 & orientation,
    Real width, Real height,
    int rows, int cols);
public:
  std::vector<ISimulationObject *> _simulationObjects;
  
  std::vector<TextileNode*> _nodes;

  TextileNode* getNode(int i, int j);


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


  
  static TextileModel * createTextileModel( const Vector3D & p,     const Matrix3x3 & orientation,    Real width, Real height,    int rows, int cols);

  void normalize();
};
}