#pragma once

#include <Simulation/Simulation.h>
#include <Simulation/SimulationObjects/Box.h>
#include <Simulation/SimulationObjects/Gravity.h>
#include <Simulation/SimulationObjects/DampedSpring.h>
#include <Simulation/SimulationObjects/BallJoint.h>
#include <Simulation/SimulationObjects/Sphere.h>
#include <Simulation/SimulationObjects/ParticleConnector.h>
#include <Simulation/SimulationObjects/RigidBodyConnector.h>

#include <string>
#include <map>

namespace IBDS{
class SimulationBuilder{
  private:
    int _connectorNumber;
    Simulation & _simulation;
    std::map<std::string,ISimulationObject *> _simulationObjects; 
  public:
    SimulationBuilder(Simulation & simulation);

    /**
     * \brief Creates a box.
     *
     * \author Tobi
     * \date 09.05.2012
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
    Box * createBox(std::string name,const Vector3D & position=Vector3D::Zero(),Real mass=1,Real width=1,Real height=1, Real depth=1);

    /**
     * \brief Sets a gravity.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param gravityVector The gravity vector.
     *
     * \return null if it fails, else.
     */
    Gravity* setGravity(const Vector3D & gravityVector);

    /**
     * \brief Sets a gravity.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param g The acceleration in negative y direction.
     *
     * \return null if it fails, else.
     */
    Gravity* setGravity(Real g=9.81);

    /**
     * \brief Creates a spring.
     *
     * \author Tobi
     * \date 09.05.2012
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
    DampedSpring * createSpring(    std::string name,     std::string bodyA,     std::string bodyB,     Real k_s,    Real k_d,    const Vector3D & r_a_wcs,     const Vector3D & r_b_wcs,    Real neutralLength = -1);

    /**
     * \brief Creates a sphere.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param name     The name.
     * \param position (optional) the position.
     * \param mass     (optional) the mass.
     * \param radius   (optional) the radius.
     *
     * \return null if it fails, else.
     */
    Sphere * createSphere(std::string name, const Vector3D & position=Vector3D::Zero(), Real mass=1,Real radius = 1){};

    /**
     * \brief Creates a particle.
     *
     * \author Tobi
     * \date 09.05.2012
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
     * \author Tobi
     * \date 09.05.2012
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
     * \author Tobi
     * \date 09.05.2012
     *
     * \param name The name.
     *
     * \return null if it fails, else the object.
     */
    ISimulationObject* getObject(std::string name);

    /**
     * \brief Queries if a given name exists.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param name The name.
     *
     * \return true if it succeeds, false if it fails.
     */
    bool nameExists(std::string name);
  private:

    /**
     * \brief Queries if a given name exists.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param name The name.
     *
     * \return true if it succeeds, false if it fails.
     */
    bool nameExists(const std::string * name);
    

    /**
     * \brief Creates a connector name.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param a a.
     * \param b The b.
     *
     * \return null if it fails, else.
     */
    std::string * createConnectorName(std::string a, std::string b);

    /**
     * \brief Creates a connector.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param bodyName   Name of the body.
     * \param position   The position.
     * \param connectsTo (optional) the connects to.
     *
     * \return null if it fails, else.
     */
    Connector* createConnector(std::string bodyName, const Vector3D & position, std::string connectsTo="Unknown");

    /**
     * \brief Creates a particle connector.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param [in,out] body If non-null, the body.
     * \param position      The position.
     *
     * \return null if it fails, else.
     */
    ParticleConnector * createParticleConnector(Body* body, const Vector3D & position);

    /**
     * \brief Creates a rigid body connector.
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param [in,out] body If non-null, the body.
     * \param position      The position.
     *
     * \return null if it fails, else.
     */
    RigidBodyConnector * createRigidBodyConnector(Body* body, const Vector3D &position);  

    /**
     * \brief Adds a simulation object. 
     *
     * \author Tobi
     * \date 09.05.2012
     *
     * \param [in,out] obj If non-null, the object.
     *
     * \return true if it succeeds, false if it fails.
     */
    bool addSimulationObject(ISimulationObject * obj);  
  };
}