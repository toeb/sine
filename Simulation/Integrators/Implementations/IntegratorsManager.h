#pragma once

#include "Simulation/Simulation.h"
#include "Simulation/Integrators/Integrator.h"
#include <string>

namespace IBDS{
	class IntegratorsManager
		{
		private:
			// pointer to the simulation this manager belongs to
			Simulation * const _simulation;
			
			// pointer to the available integrators array
			(Integrator* const)* const _integrators;
			
			// the number of the available integrators
			int _integratorsCount;
			
			// pointer to the array of names of the available integrators
			std::string * _integratorNames;
			
			IntegratorsManager();
			
		public:
			/**
			 * \param simulation the simulation to associate this manager with
			 * \param integrators array of pointers to the available integrator objects
			 * \param integratorsCount length of the array
			 */
			IntegratorsManager(Simulation* const simulation, Integrator * const * const integrators, int integratorsCount);
			
			~IntegratorsManager();
			
			/**
			 * \return names pointer to the names array
			 */
			std::string const * getIntegratorNames();

			/**
			 * \return count number of the available integrators
			 */
			int getIntegratorsCount();
			
			/**
			 * Sets the integrator in the simulation.
			 * \param integratorName pointer to the name of the integrator to set
			 */
			void setIntegrator (std::string const & integratorName);
		
			/**
			 * \return the name of the current integrator in the simulation
			 */
			std::string const & getIntegrator();
		};
	}