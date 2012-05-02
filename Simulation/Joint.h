#pragma once

namespace IBDS {

	class Joint
	{
	private:
		
	public:

		/**
		 * \param h simulation step size (for position prediction)
		 */
		virtual bool correctPosition(Real h) = 0;

		virtual void correctVelocity() = 0;
	};
}