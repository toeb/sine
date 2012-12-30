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
#include <visualization/Color.h>
#include <visualization/Light.h>
#include <visualization/Material.h>

namespace nspace {

  /**
   * \brief Gl vertex. calls glVertex3d for any type that is accessible by operator()(int index)
   *
   * \tparam  typename VectorType Type of the typename vector type.
   * \param v The const VectorType&amp; to process.
   */
  template<typename VectorType> void glVertex(const VectorType& v){
    glVertex3d(v(0), v(1), v(2));
  }

  /**
   * \brief Gl normal. calls glNormal3d for any type that is accessible by operator()(index)
   *
   * \tparam  typename VectorType Type of the typename vector type.
   * \param v The const VectorType&amp; to process.
   */
  template<typename VectorType> void glNormal(const VectorType& v){
    glNormal3d(v(0), v(1), v(2));
  }

  /**
   * \brief Gl rotate. calls glMultMatrix for any type that is accessible by operator()(i,j)
   *
   * \tparam  typename Matrix3x3Type  Type of the typename matrix 3x 3 type.
   * \param R The const Matrix3x3Type &amp; to process.
   */
  template<typename Matrix3x3Type> void glRotate(const Matrix3x3Type & R){
    glMultMatrix(R,Vector3D::Zero());
  }

  /**
   * \brief Gl translate. calls glTranslated for any type that is accessible by operator()(i)
   *
   * \tparam  typename VectorType Type of the typename vector type.
   * \param v The const VectorType&amp; to process.
   */
  template<typename VectorType> void glTranslate(const VectorType& v){
    glTranslated(v(0), v(1), v(2));
  }

  /**
   * \brief Gl multiply matrix. calls glMultMatrixd for R a type which must possess the operator()(i,j) and r reference to a type with the operator()(i)
   *
   * \tparam  typename MatrixType Type of the typename matrix type.
   * \tparam  typename VectorType Type of the typename vector type.
   * \param R The const MatrixType&amp; to process.
   * \param r The const VectorType&amp; to process.
   */
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

  /**
   * \brief Converts. a Matrix3x3 to a double * (16 element opengl 4x4 matrix - columnmajor order)
   *
   * \param from          Source for the.
   * \param [in,out]  to  If non-null, to.
   */
  void convert(const Matrix3x3 & from,  double * to);

  /**
   * \brief Gl triangle. Draws a triangle between the points a,b,c with the normal n
   *
   * \param a The const Vector3D &amp; to process.
   * \param b The const Vector3D &amp; to process.
   * \param c The const Vector3D &amp; to process.
   * \param n The const Vector3D &amp; to process.
   */
  void glTriangle(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & n);

  /**
   * \brief Gl quad. Draws a Quad 2D surface defined by its four cornerpoints and normal vector n
   *
   * \param a The const Vector3D &amp; to process.
   * \param b The const Vector3D &amp; to process.
   * \param c The const Vector3D &amp; to process.
   * \param d The const Vector3D &amp; to process.
   * \param n The const Vector3D &amp; to process.
   */
  void glQuad(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & d,const Vector3D & n);

  /**
   * \brief Gl scale. scales the 3 dimensions by Vector
   *
   * \param s The const Vector3D &amp; to process.
   */
  void glScale(const Vector3D & s);

  /**
   * \brief Gl scale. scales the three dimensions by x,y and z
   *
   * \param x  scaling factor
   * \param y  scaling factor
   * \param z  scaling factor
   */
  void glScale(const Real x, const Real y, const Real z);

  /**
   * \brief Gl scale. scales all dimensions equaly by s
   *
   * \param s The Real to process.
   */
  void glScale(Real s);

  /**
   * \brief Gl rotate. rotates by alpha around the axis specified by x,y and z
   *
   * \param alpha The angle by which to rotate
   * \param x     The x component of the rotations axis
   * \param y     The y component of the rotations axis
   * \param z     The z component of the rotations axis
   */
  void glRotate(const Real alpha, const Real x, const Real y, const Real z);

  /**
   * \brief Gl rotate quaternion. rotates by quaternion
   *
   * \param q The const Quaternion &amp; to rotate by
   */
  void glRotateQuaternion(const Quaternion & q);

  /**
   * \brief Gl translate. Translates to x, y, z
   *
   * \param x
   * \param y
   * \param z
   */
  void glTranslate(const Real x, const Real y, const Real z);

  /**
   * \brief Gl transformation. Transforms the current Worldview matrix by the specified coordinates
   *        (first transposed rotation then translation)
   *
   * \param coordinates The coordinates.
   */
  void glTransformation(const CoordinateSystem & coordinates);

  /**
   * \brief Gl light. sets a light in gl
   *
   * \param light     The light.
   * \param position  (optional) the position.
   * \param ambience  (optional) the ambience color.
   * \param diffuse   (optional) the diffuse color.
   * \param specular  (optional) the specular color.
   */
  void glLight(int light,
               const Vector3D & position = Vector3D(1,1,0),
               const Vector3D & ambience = Vector3D::Zero(),
               const Vector3D & diffuse=Vector3D::Ones(),
               const Vector3D& specular=Vector3D::Ones());

  /**
   * \brief Gl disables all lights.
   */
  void glDisableLights();

  /**
   * \brief Sets the light with lightNumber to the parameters declared in Light class
   *
   * \param lightNumber The light number.
   * \param light       The light.
   */
  void glLight(uint lightNumber, const Light & light);

  /**
   * \brief Gl material. Sets gl the material
   *
   * \param color     The color.
   * \param ambient   The ambient.
   * \param diffuse   The diffuse.
   * \param specular  The specular.
   * \param shininess The shininess.
   * \param alpha     The alpha.
   */
  void glMaterial(
    const Vector3D & color
    , Real ambient
    ,  Real diffuse
    ,  Real specular
    ,  Real shininess
    ,  Real alpha);

  /**
   * \brief Gl material. Sets the current material
   *
   * \param material  The material.
   */
  void glMaterial(const Material & material);

  /**
   * \brief Gl color. Sets the current color
   *
   * \param color The color.
   */
  void glColor(const Color & color);

  /**
   * \brief Gl sets the clear color.
   *
   * \param color The color.
   */
  void glSetClearColor(const Color & color);

  /**
   * \brief Gl sphere. draws a sphere
   *
   * \param r     The double to process.
   * \param lats  The lats.
   * \param longs The longs.
   */
  void glSphere(double r, int lats, int longs);

  /**
   * \brief Gl quad.
   *
   * \param a       The const Vector3D &amp; to process.
   * \param b       The const Vector3D &amp; to process.
   * \param c       The const Vector3D &amp; to process.
   * \param d       The const Vector3D &amp; to process.
   * \param normal  (optional) the normal.
   */
  void glQuad(const Vector3D & a,const Vector3D & b,const Vector3D & c,const Vector3D & d, const Vector3D * normal=0);

  /**
   * \brief Gl quad. alternative formulation.  a position, orientation and side length specifies a square quad
   *
   * \param position    The position.
   * \param orientation The orientation.
   * \param sidelength  (optional) the sidelength.
   */
  void glQuad(const Vector3D & position, const Quaternion & orientation, Real sidelength=1);

  /**
   * \brief Gl line. draws a line
   *
   * \param a The const Vector3D &amp; to process.
   * \param b The const Vector3D &amp; to process.
   */
  void glLine(const Vector3D & a, const Vector3D & b);

  /**
   * \brief Gl vector. draws a Line from start to start + direction
   *
   * \param start     The start.
   * \param direction The direction.
   */
  void glVector(const Vector3D & start, const Vector3D & direction);
}
