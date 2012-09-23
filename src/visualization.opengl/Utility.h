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
#include <math/core.h>
#include <visualization.opengl/opengl.h>
#include <simulation.kinematics/CoordinateSystem.h>
#include <visualization.opengl/GlMaterial.h>
#include <visualization/Color.h>


namespace nspace{
  
template<typename VectorType> void glVertex(const VectorType& v){  glVertex3d(v(0), v(1), v(2)); }
template<typename VectorType> void glNormal(const VectorType& v){  glNormal3d(v(0), v(1), v(2)); }
template<typename Matrix3x3Type> void glRotate(const Matrix3x3Type & R){   glMultMatrix(R,Vector3D::Zero()); }
template<typename VectorType> void glTranslate(const VectorType& v){  glTranslated(v.x(), v.y(), v.z()); }
template<typename MatrixType, typename VectorType> void glMultMatrix(const MatrixType& R, const VectorType& r){
  // transform matrix and vector into a double array which is a opegnl 4x4 matrix
  double m[16];
  m[0] = R(0, 0);
  m[4] = R(0, 1);
  m[8] = R(0, 2);
  m[12] = r(0);
  m[1] = R(1, 0);
  m[5] = R(1, 1);
  m[9] = R(1, 2);
  m[13] = r(1);
  m[2] = R(2, 0);
  m[6] = R(2, 1);
  m[10] = R(2, 2);
  m[14] = r(2);
  m[3] = 0;
  m[7] = 0;
  m[11] = 0;
  m[15] = 1;
  glMultMatrixd(m);
}



void convert(const Matrix3x3 & from,  double * to);
void glTriangle(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & n);
void glQuad(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & d,const Vector3D & n);

void glScale(const Vector3D & s);
void glScale(Real s);
void glRotate(const Real u, const Real x, const Real y, const Real z);
void glRotateQuaternion(const Quaternion & q);
void glScale(const Real x, const Real y, const Real z);
void glTranslate(const Real x, const Real y, const Real z);



void glTransformation(const CoordinateSystem & coordinates);

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
