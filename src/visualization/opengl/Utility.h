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
#include "opengl.h"
#include <math/definitions.h>



namespace nspace{
void convert(const Matrix3x3 & from,  double * to);

class GlMaterial{
public:
  static GlMaterial * jade;
  static GlMaterial * rubber;
  static GlMaterial * plastic;
  static GlMaterial * sinn;
  static GlMaterial * bronze;
 

 static void setup(){
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void set();
  GlMaterial(){};
  GlMaterial(
    Real r,
    Real g,
    Real b, 
    Real ambient,
    Real diffuse, 
    Real specular, 
    Real alpha, 
    Real shininess)
  : shininess(shininess), alpha(alpha){
    this->ambient.x()=r*alpha;
    this->ambient.y()=g*alpha;
    this->ambient.z()=b*alpha; 

    this->diffuse.x()=r*alpha;
    this->diffuse.y()=g*alpha;
    this->diffuse.z()=b*alpha; 

    this->specular.x()=r*alpha;
    this->specular.y()=g*alpha;
    this->specular.z()=b*alpha; 
  };
  GlMaterial(
    Real Ra,
    Real Ga,
    Real Ba,
    Real Rd,
    Real Gd,
    Real Bd,
    Real Rs,
    Real Gs,
    Real Bs,
    Real alpha,
    Real shininess
    ){
    ambient.x()=Ra;
    ambient.y()=Ga;
    ambient.z()=Ba; 

    diffuse.x()=Rd;
    diffuse.y()=Gd;
    diffuse.z()=Bd; 

    specular.x()=Rs;
    specular.y()=Gs;
    specular.z()=Bs; 
    this->alpha = alpha;
    this->shininess = shininess;
  };
  Vector3D ambient;
  Vector3D diffuse;
  Vector3D specular;
  Real shininess;
  Real alpha;
};

void glVertex(const Vector3D& v);

void glNormal(const Vector3D& v);

void glRotate(const Real u, const Real x, const Real y, const Real z);

void glScale(const Real x, const Real y, const Real z);

void glTranslate(const Real x, const Real y, const Real z);
void glTranslate(const Vector3D& v);

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

void renderCube();

};
//convenience functions for working with opengl 

