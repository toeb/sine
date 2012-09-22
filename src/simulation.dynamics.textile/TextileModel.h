#pragma once

#include <vector>
#include <functional>

#include <math/core.h>

#include <simulation/ISimulationObject.h>
#include <simulation.dynamics.force/DampedSpring.h>
#include <simulation.dynamics/Particle.h>
#include <simulation.dynamics/connection/ParticleConnector.h>

namespace nspace{

/**
 * \brief a Textile node has links to the north south east and west node as well as to the 12 connected springs. 
 *
 * 
 */
struct TextileNode{
  TextileNode():
    connector(0),
      particle(0),
    north(0), south(0), east(0), west(0),
    northElongator(0),eastElongator(0),
    westElongator(0), southElongator(0),
    northEastShearer(0), southEastShearer(0), 
    southWestShearer(0), northWestShearer(0),
    northFlexor(0), southFlexor(0), westFlexor(0), eastFlexor(0),i(0),j(0){}

  ParticleConnector * connector;
  Particle * particle;
  int i,j;

  TextileNode * north;
  TextileNode * east;
  TextileNode * south;
  TextileNode * west;

 
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

/**
 * \brief Textile model. 
 *
 * 
 */
class TextileModel : public ISimulationObject{
private:
  int _rows;
  int _columns;
  
  Real _width;
  Real _height;
  Real _mass;
  
  std::vector<ISimulationObject *> _simulationObjects;
  std::vector<TextileNode*> _nodes;
  

  Real _k_d_elongation;
  Real _k_d_shear;
  Real _k_d_flexion;
  Real _k_s_elongation;
  Real _k_s_shear;
  Real _k_s_flexion;

  Real _maximumElongation;
  bool _normalize;

public:
  static TextileModel * createTextileModel( const Vector3D & p,     const Matrix3x3 & orientation, Real mass,   Real width, Real height,    int rows, int cols);
  void normalize();

  bool isNormalizing()const;
  void setNormalizing(bool flag);
  
  Real getSuggestedStepSize()const;
  
  void setMaximumElongation(Real valueInPercent);
  Real getMaximumElongation()const;

  void setMass(Real mass);
  Real getMass()const;
  
  std::vector<ISimulationObject*> & getSimulationObjects();
  
  TextileNode* getNode(int i, int j);

  void foreachNode(std::function<void (TextileNode* node)> f);

  void setElongationSpringConstant(Real k_d_e);
  Real getElongationSpringConstant()const;

  void setElongationDampeningConstant(Real k_d_e);
  Real getElongationDampeningConstant()const;


  void setShearDampeningConstant(Real k_d_s);
  Real getShearDampeningConstant()const;

  void setShearSpringConstant(Real k_d_s);
  Real getShearSpringConstant()const;


  void setFlexionDampeningConstant(Real k_d_f);
  Real getFlexionDampeningConstant()const;

  void setFlexionSpringConstant(Real k_d_f);
  Real getFlexionSpringConstant()const;



private:
  void normalizeEachSpring(Real maxElongationRate);

  void for_each_spring(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f);
  void for_each_elongator(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f);
  void for_each_flexor(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f);
  void for_each_shearer(std::function<void (TextileNode * , TextileNode * , DampedSpring * )> f);

  TextileModel();

  DampedSpring *  createSpring(TextileNode * a, TextileNode * b, Real k_s, Real k_d);
  Particle * createParticle(TextileNode * node, const Vector3D & position);
  DampedSpring * createFlexor(TextileNode * nodeA, TextileNode* nodeB);
  DampedSpring * createShearer(TextileNode * nodeA, TextileNode* nodeB);
  DampedSpring * createElongator(TextileNode * nodeA, TextileNode* nodeB);
  
  void createFlexors(TextileNode *node);
  void createShearers(TextileNode *node);
  void createElongators(TextileNode *node);

  void createNodeMesh(const Vector3D & p,const Matrix3x3 & orientation);
  void createSprings();
  void setupNodeConnectivity();
  

  void addSimulationObject(ISimulationObject *  object);

  void buildModel(
    const Vector3D & p, 
    const Matrix3x3 & orientation,
    Real mass,
    Real width, Real height,
    int rows, int cols);

    void normalizeShearers(Real maxElongationRate);
    void normalizeElongators(Real maxElongationRate);
	};
}
