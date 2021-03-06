#pragma once

#include <Simulation/Core/Simulation.h>
#include <Simulation/Dynamics/BodyPrimitives/DynamicBox.h>
#include <Simulation/Dynamics/BodyPrimitives/DynamicSphere.h>
#include <Simulation/Force/Gravity.h>
#include <Simulation/Force/DampedSpring.h>
#include <Simulation/MultiBodyDynamics/ImpulseBased/BallJoint.h>
#include <Simulation/Dynamics/Connection/ParticleConnector.h>
#include <Simulation/Dynamics/Connection/RigidBodyConnector.h>
#include <Simulation/Geometry/Primitives/Rectangle.h>
#include <Simulation/Geometry/Primitives/Pyramid.h>
#include <Simulation/Geometry/Primitives/Triangle.h>

#include <string>
#include <map>

namespace IBDS{
class SimulationBuilder{
private:
    int _unknownCounter;
    int _connectorNumber;
    Simulation & _simulation;
    std::map<std::string,ISimulationObject *> _simulationObjects; 
    Vector3D _currentOffset;    
public:

  void setOffset(const Vector3D & offset){
    _currentOffset.assign(offset);
  }

  SimulationBuilder(Simulation & simulation);

  std::map<std::string,ISimulationObject *> & getSimulationObjects();

  Rectangle * createFixedRectangle(std::string name="",const Vector3D& position=Vector3D::Zero(),const Quaternion & orientation=Quaternion::zeroRotation(),Real width=1,Real height =1);

  /**
    * \brief Creates a box.
    *
    * \param name     The name.
    * \param position (optional) the position.
    * \param mass     (optional) the mass.
    * \param width    (optional) the width.
    * \param height   (optional) the height.
    * \param depth    (optional) the depth.
    *
    * \return null if it fails, else.
    */
  DynamicBox * createBox(std::string name="",const Vector3D & position=Vector3D::Zero(),Real mass=1,Real width=1,Real height=1, Real depth=1);
    
  /**
    * \brief Sets a gravity.
    *
    * \param gravityVector The gravity vector.
    *
    * \return null if it fails, else.
    */
  Gravity* setGravity(const Vector3D & gravityVector);

  /**
    * \brief Sets a gravity.
    *
    * \param g The acceleration in negative y direction.
    *
    * \return null if it fails, else.
    */
  Gravity* setGravity(Real g=9.81);

  /**
    * \brief Creates a spring.
    *
    * \param name          The name.
    * \param bodyA         The body a.
    * \param bodyB         The body b.
    * \param k_s           The s.
    * \param k_d           The d.
    * \param r_a_wcs       a wcs.
    * \param r_b_wcs       The b wcs.
    * \param neutralLength (optional) length of the neutral.
    *
    * \return null if it fails, else.
    */
  DampedSpring * createSpring(std::string name, std::string bodyA, std::string bodyB, Real k_s, Real k_d, const Vector3D & r_a_wcs, const Vector3D & r_b_wcs, Real neutralLength = -1);

  /**
    * \brief Creates a sphere.
    *
    * \param name     The name.
    * \param position (optional) the position.
    * \param mass     (optional) the mass.
    * \param radius   (optional) the radius.
    *
    * \return null if it fails, else.
    */
  DynamicSphere * createSphere(std::string name="", const Vector3D & position=Vector3D::Zero(), Real mass=1,Real radius = 1);
    
  /**
    * \brief Creates a particle.
    *
    * \param name     The name.
    * \param position (optional) the position.
    * \param mass     (optional) the mass.
    *
    * \return null if it fails, else.
    */
  Particle * createParticle(std::string name, const Vector3D & position=Vector3D::Zero(), Real mass=1);

  /**
    * \brief Creates a ball joint.
    *
    * \param jointName Name of the joint.
    * \param bodyA     The body a.
    * \param bodyB     The body b.
    * \param position  The position.
    *
    * \return null if it fails, else.
    */
  BallJoint * createBallJoint(std::string jointName, std::string bodyA, std::string bodyB, const Vector3D & position);

  /**
    * \brief Gets an object.
    *
    * \param name The name.
    *
    * \return null if it fails, else the object.
    */
  ISimulationObject* getObject(std::string name);

  /**
    * \brief Queries if a given name exists.
    *
    * \param name The name.
    *
    * \return true if it succeeds, false if it fails.
    */
  bool nameExists(std::string name);
private:

  std::string createUnknownName();
  /**
    * \brief Queries if a given name exists.
    *
    * \param name The name.
    *
    * \return true if it succeeds, false if it fails.
    */
  bool nameExists(const std::string * name);
    

  /**
    * \brief Creates a connector name.
    *
    * \param a a.
    * \param b The b.
    *
    * \return null if it fails, else.
    */
  std::string createConnectorName(std::string a, std::string b);

  /**
    * \brief Creates a connector.
    *
    * \param bodyName   Name of the body.
    * \param position   The position.
    * \param connectsTo (optional) the connects to.
    *
    * \return null if it fails, else.
    */
  Connector* createConnector(std::string bodyName, const Vector3D & position, std::string connectsTo="Unknown");

  /**
    * \brief Adds a simulation object. 
    *
    * \param [in,out] obj If non-null, the object.
    *
    * \return true if it succeeds, false if it fails.
    */
  bool addSimulationObject(ISimulationObject * obj);  
};
}