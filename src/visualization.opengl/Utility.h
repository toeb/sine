/*
 * Copyright (C) 2011
 * Simulation, Systems Optimization and Robotics Group (SIM)
 * Technische Universitaet Darmstadt
 * Hochschulstr. 10
 * 64289 Darmstadt, Germany
 * www.sim.tu-darmstadt.de
 *
 * This file is part of the mbslib.
 * All rights are reserved by the copyright holder.
 *
 * The mbslib is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You may use the mbslib or parts of it only with the written permission of the copyright holder.
 * You may NOT modify or redistribute any part of the mbslib without the prior written
 * permission by the copyright holder.
 *
 * Any violation of the rights and restrictions mentioned above will be prosecuted by civil and penal law.
 * Any expenses associated with the prosecution will be charged against the violator.
 */

/**
 * \file src/vis/opengl/Utility.h
 */
#include <math/definitions.h>
#include <visualization.opengl/opengl.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <visualization.opengl/GlMaterial.h>
#include <visualization/Color.h>


namespace nspace{
void convert(const Matrix3x3 & from,  double * to);
void glTriangle(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & n);
void glQuad(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & d,const Vector3D & n);
void glVertex(const Vector3D& v);
void glNormal(const Vector3D& v);
void glRotate(const Matrix3x3 & R);
void glScale(const Vector3D & s);
void glScale(Real s);
void glRotate(const Real u, const Real x, const Real y, const Real z);
void glRotate(const Quaternion & q);
void glScale(const Real x, const Real y, const Real z);
void glTranslate(const Real x, const Real y, const Real z);
void glTranslate(const Vector3D& v);
void glTransformation(const CoordinateSystem & coordinates);
void glMultMatrix(const Matrix3x3& R, const Vector3D& r);
void glLight(int light, 
  const Vector3D & position = Vector3D(1,1,0), 
  const Vector3D & ambience = Vector3D::Zero(), 
  const Vector3D & diffuse=Vector3D::Ones(), 
  const Vector3D& specular=Vector3D::Ones());

void glMaterial(
  const Vector3D & color
  ,const Real & ambient
  , const Real & diffuse
  , const Real & specular
  , const Real & shininess
  , const Real & alpha);

void glMaterial(nspace::GlMaterial & material);

void glColor(const Color & color);
void glSetClearColor(const Color & color);
}
