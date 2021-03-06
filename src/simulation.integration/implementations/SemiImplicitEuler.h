// /*
//  * Copyright (C) 2011
//  * Simulation, Systems Optimization and Robotics Group (SIM)
//  * Technische Universitaet Darmstadt
//  * Hochschulstr. 10
//  * 64289 Darmstadt, Germany
//  * www.sim.tu-darmstadt.de
//  *
//  * This file is part of the mbslib.
//  * All rights are reserved by the copyright holder.
//  *
//  * The mbslib is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//  *
//  * You may use the mbslib or parts of it only with the written permission of the copyright holder.
//  * You may NOT modify or redistribute any part of the mbslib without the prior written
//  * permission by the copyright holder.
//  *
//  * Any violation of the rights and restrictions mentioned above will be prosecuted by civil and penal law.
//  * Any expenses associated with the prosecution will be charged against the violator.
//  */
//
// /**
//  * \file src/mbs/integrators/implementations/SemiImplicitEuler.h
//  * Declaration of mbslib::ExplicitEuler
//  */
// #pragma once
// #include <simulation/integration/StepIntegrator.h>
// namespace nspace{
//
// /**
//  * \brief The semi implicit Euler integrator
//  */
// class SemiImplicitEuler : public StepIntegrator{
// public:
//
//   /**
//    * \brief Constructor.
//    *
//    * \param [in]  system   The system.
//    * \param stepSize          (optional) size of the step (default is 0.01).
//    */
//   SemiImplicitEuler(Real stepSize = 0.01);
//
//   /**
//    * \brief does a semi implicit Euler step.
//    *
//    * \param t_i The current time t_i.
//    * \param h   The timestep length h.
//    *
//    * \return  .
//    */
//  void doStep(Real t_i, Real h);
//
//   int getErrorOrder()const;
// };//class ExplicitEulerIntegrator
// }//namespace mbslib;
