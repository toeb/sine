#pragma once

#include <Simulation/Dynamics/Connection/Connector.h>
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
			Real _lastLength;
			Real _currentLength;
			Vector3D _f_wcs;
			Vector3D _f_s_wcs;
			Vector3D _f_d_wcs;
		public:
			//static DampedSpring * createSpring(

			~DampedSpring();
			inline void calculateSpringAndDampeningForce();

			Real getStiffnessConstant()const;
			void setStiffnessConstant(Real k_s);

			Real getDampeningConstant()const;
			void setDampeningConstant(Real k_d);

      inline const Connector & getConnectorA()const{return _cA;};
      inline const Connector& getConnectorB()const{return _cB;};

			inline Connector & getConnectorA(){return _cA;};
			inline Connector & getConnectorB(){return _cB;};

			Real getLastLength()const;
			Real getCurrentLength()const;
      inline Real getRestLength() const{return _l0;};

			const Vector3D & getForce()const;
			const Vector3D & getSpringForce()const;
			const Vector3D & getDampeningForce()const;


			/**
			* Creates a string with the specified stiffness, damping and rest length, which is attached to the specified connectors.
			*/
			DampedSpring(Connector & c1, Connector &c2, Real k_s, Real k_d, Real restLength);

			inline void act (std::vector<DynamicBody*> & target, Real time);      
		};
	}