#pragma once

#include <Simulation/Dynamics/Connector.h>
#include <Simulation/Force/Force.h>

namespace IBDS{
	class DampedSpring : public Force
		{
		private:
			// the connectors this spring is attached to
			Connector & _cA;
      Connector & _cB;
      // stiffness constant
			Real _k_s;			
			// damping constant
			Real _k_d;
      // initial length
			Real _l0;
		public:
			~DampedSpring();
      inline void calculateSpringAndDampeningForce(Vector3D & f_s,Vector3D & f_d)const;
      inline void calculateSpringForce(Vector3D & f)const;
      Real getStiffnessConstant()const;
      Real getDampeningConstant()const;
      const Connector & getConnectorA()const;
      const Connector& getConnectorB()const;

			/**
			 * Creates a string with the specified stiffness, damping and rest length, which is attached to the specified connectors.
			 */
			DampedSpring(Connector & c1, Connector &c2, Real k_s, Real k_d, Real restLength);
			
			// Side effect: fields a, b are set.
			void act (std::vector<DynamicBody*> & target, Real time);      
		};
	}