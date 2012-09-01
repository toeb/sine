#pragma once

#include <simulation/dynamics/connection/Connector.h>
#include <simulation/force/Force.h>

namespace nspace{
	class DampedSpring : public Force
		{
		private:
			// the connectors this spring is attached to
			DynamicConnector & _cA;
			DynamicConnector & _cB;
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

      inline const DynamicConnector & getConnectorA()const{return _cA;};
      inline const DynamicConnector & getConnectorB()const{return _cB;};

			inline DynamicConnector & getConnectorA(){return _cA;};
			inline DynamicConnector & getConnectorB(){return _cB;};

			Real getLastLength()const;
			Real getCurrentLength()const;
      inline Real getRestLength() const{return _l0;};

			const Vector3D & getForce()const;
			const Vector3D & getSpringForce()const;
			const Vector3D & getDampeningForce()const;


			/**
			* Creates a string with the specified stiffness, damping and rest length, which is attached to the specified connectors.
			*/
			DampedSpring(DynamicConnector & c1, DynamicConnector &c2, Real k_s, Real k_d, Real restLength);

			inline void act (std::vector<DynamicBody*> & target, Real time);      
		};
	}