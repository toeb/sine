/*
* IBDS - Impulse-Based Dynamic Simulation Library
* Copyright (c) 2003-2008 Jan Bender http://www.impulse-based.de
*
* This software is provided 'as-is', without any express or implied
* warranty. In no event will the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*
* Jan Bender - Jan.Bender@impulse-based.de
*/

#include "Matrix4x4.h"
#include "math.h"
#include "Matrix3x3.h"

using namespace nspace;

;
/** Standard-Konstruktor: erstellt die Einheitsmatrix
*/
Matrix4x4::Matrix4x4()
{
  for (int i=0; i < 4; i++)
  {
    for (int j=0; j < 4; j++)
    {
      if (i == j)
        m[i][j] = 1.0;
      else
        m[i][j] = 0.0;
    }
  }
}

/** Konstruktor: Erstellt die Matrix mit den übergebenen Werten
*/
Matrix4x4::Matrix4x4 (Real matrix[4][4])
{
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      m[i][j] = matrix[i][j];
}

/** Fills the matrix with the given values.
*/
void Matrix4x4::set(const Real matrix[16])
{
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      m[i][j] = matrix[i*4+j];
}

/** Get the matrix.
*/
void Matrix4x4::get(Real *matrix)
{
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      matrix[i*4+j] = m[i][j];
}

/** Sets the translation, rotation and scale of this tranformation matrix
*/
void Matrix4x4::setTransformation (const Vector3D &translation, const Matrix3x3 &rotation, const Vector3D &scale)
{
  operator()(0,0) = scale(0) * rotation(0,0);
  operator()(0,1) = rotation(0,1);
  operator()(0,2) = rotation(0,2);
  operator()(1,0) = rotation(1,0);
  operator()(1,1) = scale(1) * rotation(1,1);
  operator()(1,2) = rotation(1,2);
  operator()(2,0) = rotation(2,0);
  operator()(2,1) = rotation(2,1);
  operator()(2,2) = scale(2) * rotation(2,2);
  operator()(3,0) = translation(0);
  operator()(3,1) = translation(1);
  operator()(3,2) = translation(2);
  operator()(3,3) = (Real) 1.0;
}

/** Negation: -m\n
* Negiert alle Elemente der Matrix
*/
Matrix4x4 nspace::operator - (const Matrix4x4& a)
{
  Matrix4x4 m;
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      m.m[i][j] = -a.m[i][j];
  return m;
}

/** Addition: m1 + m2\n
* Elementweise Addition von m1 mit m2
*/
Matrix4x4 nspace::operator + (const Matrix4x4& a, const Matrix4x4& b)
{
  Matrix4x4 m;
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      m.m[i][j] = a.m[i][j]+b.m[i][j];
  return m;
}

/** Subtraktion: m1 - m2\n
* Elementweise Subtraktion
*/
Matrix4x4 nspace::operator - (const Matrix4x4& a, const Matrix4x4& b)
{
  Matrix4x4 m;
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      m.m[i][j] = a.m[i][j] - b.m[i][j];
  return m;
}

/** Multiplikation: m1 * m2\n
* Matrixmultiplikation von m1 mit m2
*/
Matrix4x4 nspace::operator * (const Matrix4x4& a, const Matrix4x4& b)
{
  Matrix4x4 c;
  for (int i=0; i < 4; i++)
  {
    c.m[i][0] = a.m[i][0]*b.m[0][0] + a.m[i][1]*b.m[1][0] + a.m[i][2]*b.m[2][0] + a.m[i][3]*b.m[3][0];
    c.m[i][1] = a.m[i][0]*b.m[0][1] + a.m[i][1]*b.m[1][1] + a.m[i][2]*b.m[2][1] + a.m[i][3]*b.m[3][1];
    c.m[i][2] = a.m[i][0]*b.m[0][2] + a.m[i][1]*b.m[1][2] + a.m[i][2]*b.m[2][2] + a.m[i][3]*b.m[3][2];
    c.m[i][3] = a.m[i][0]*b.m[0][3] + a.m[i][1]*b.m[1][3] + a.m[i][2]*b.m[2][3] + a.m[i][3]*b.m[3][3];
  }
  return c;
}

/** Multiplikation: m1 ^ m2\n
* Matrixmultiplikation von m1 mit m2
* Diese Funktion arbeitet schneller als die allgemeine 4x4 Matrixmultiplikation,
* aber sie arbeitet nur korrekt, wenn a und b SE(3) Transformationsmatrizen sind.
*/
Matrix4x4 nspace::operator ^ (const Matrix4x4& a, const Matrix4x4& b)
{
  Matrix4x4 c;

  /* Rc = Ra Rb */
  c.m[0][0] = a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0] + a.m[0][2]*b.m[2][0];
  c.m[0][1] = a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1] + a.m[0][2]*b.m[2][1];
  c.m[0][2] = a.m[0][0]*b.m[0][2] + a.m[0][1]*b.m[1][2] + a.m[0][2]*b.m[2][2];
  c.m[1][0] = a.m[1][0]*b.m[0][0] + a.m[1][1]*b.m[1][0] + a.m[1][2]*b.m[2][0];
  c.m[1][1] = a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1] + a.m[1][2]*b.m[2][1];
  c.m[1][2] = a.m[1][0]*b.m[0][2] + a.m[1][1]*b.m[1][2] + a.m[1][2]*b.m[2][2];
  c.m[2][0] = a.m[2][0]*b.m[0][0] + a.m[2][1]*b.m[1][0] + a.m[2][2]*b.m[2][0];
  c.m[2][1] = a.m[2][0]*b.m[0][1] + a.m[2][1]*b.m[1][1] + a.m[2][2]*b.m[2][1];
  c.m[2][2] = a.m[2][0]*b.m[0][2] + a.m[2][1]*b.m[1][2] + a.m[2][2]*b.m[2][2];

  /* Vc.m = Ra.m Vb.m + Va.m */
  c.m[0][3] = a.m[0][0]*b.m[0][3] + a.m[0][1]*b.m[1][3] + a.m[0][2]*b.m[2][3] + a.m[0][3];
  c.m[1][3] = a.m[1][0]*b.m[0][3] + a.m[1][1]*b.m[1][3] + a.m[1][2]*b.m[2][3] + a.m[1][3];
  c.m[2][3] = a.m[2][0]*b.m[0][3] + a.m[2][1]*b.m[1][3] + a.m[2][2]*b.m[2][3] + a.m[2][3];

  /* Rest */
  c.m[3][0] = c.m[3][1] = c.m[3][2] = 0.0;
  c.m[3][3] = 1.0;
  return c;
}

/** Multiplikation: m * v\n
* Matrixmultiplikation von m mit v
*/
Vector3D nspace::operator * (const Matrix4x4& m, const Vector3D& v)
{
  return Vector3D (v.v[0]*m.m[0][0] + v.v[1]*m.m[0][1] + v.v[2]*m.m[0][2],
    v.v[0]*m.m[1][0] + v.v[1]*m.m[1][1] + v.v[2]*m.m[1][2],
    v.v[0]*m.m[2][0] + v.v[1]*m.m[2][1] + v.v[2]*m.m[2][2]);
}

/** Multiplikation: m ^ p\n
* Matrixmultiplikation von m mit p
*/
Vector3D nspace::operator ^ (const Matrix4x4& m, const Vector3D& p)
{
  return Vector3D (p.v[0]*m.m[0][0] + p.v[1]*m.m[0][1] + p.v[2]*m.m[0][2] + m.m[0][3],
    p.v[0]*m.m[1][0] + p.v[1]*m.m[1][1] + p.v[2]*m.m[1][2] + m.m[1][3],
    p.v[0]*m.m[2][0] + p.v[1]*m.m[2][1] + p.v[2]*m.m[2][2] + m.m[2][3]);
}

/** Multiplikation: d*a\n
* Elementweise Multiplikation einer Matrix mit einer Zahl
*/
Matrix4x4 nspace::operator * (const Real d, const Matrix4x4& a)
{
  Matrix4x4 m;
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      m.m[i][j] = d*a.m[i][j];
  return m;
}

/** Transponiert die 4x4-Matrix
*/
Matrix4x4 Matrix4x4::transpose () const
{
  Matrix4x4 t;
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      t.m[i][j] = m[j][i];
  return t;
}

/** Stream-Ausgabe der Matrix
*/
std::ostream& nspace::operator << (std::ostream& s, const Matrix4x4& m)
{
  return s << m.m[0][0] << " " << m.m[0][1] << " " << m.m[0][2] << " " << m.m[0][3] << '\n' <<
    m.m[1][0] << " " << m.m[1][1] << " " << m.m[1][2] << " " << m.m[1][3] << '\n' <<
    m.m[2][0] << " " << m.m[2][1] << " " << m.m[2][2] << " " << m.m[2][3] << '\n' <<
    m.m[3][0] << " " << m.m[3][1] << " " << m.m[3][2] << " " << m.m[3][3] << '\n';
}

/** Zuweisung: \n
* Kopiert die Werte von Matrix m.
*/
Matrix4x4& Matrix4x4::operator = (const Matrix4x4& mat)
{
  for (int i=0; i < 4; i++)
    for (int j=0; j < 4; j++)
      m[i][j] = mat.m[i][j];
  return *this;
}

/** Gibt die Inverse der Matrix zurück.
*/
Matrix4x4 Matrix4x4::inverse () const
{
  Matrix4x4 inv;

  /* Invertieren des Rotationsteils durch Transponieren */
  inv.m[0][0] = m[0][0];
  inv.m[0][1] = m[1][0];
  inv.m[0][2] = m[2][0];
  inv.m[1][0] = m[0][1];
  inv.m[1][1] = m[1][1];
  inv.m[1][2] = m[2][1];
  inv.m[2][0] = m[0][2];
  inv.m[2][1] = m[1][2];
  inv.m[2][2] = m[2][2];

  /* Verschiebungsvektor:  d' = -(R^-1) * d */
  inv.m[0][3] = - inv.m[0][0]*m[0][3] - inv.m[0][1]*m[1][3] - inv.m[0][2]*m[2][3];
  inv.m[1][3] = - inv.m[1][0]*m[0][3] - inv.m[1][1]*m[1][3] - inv.m[1][2]*m[2][3];
  inv.m[2][3] = - inv.m[2][0]*m[0][3] - inv.m[2][1]*m[1][3] - inv.m[2][2]*m[2][3];

  /* Der Rest bleibt gleich */
  inv.m[3][0] = inv.m[3][1] = inv.m[3][2] = 0.0;
  inv.m[3][3] = 1.0;

  return inv;
}

/** Zugriff per Index auf die einzelnen Komponenten der Matrix.
*/
Real& Matrix4x4::operator () (int i, int j)
{
  return m[i][j];
}

/** Zugriff per Index auf die einzelnen Komponenten der Matrix.
*/
const Real& Matrix4x4::operator () (int i, int j) const
{
  return m[i][j];
}

/** Gibt die Transformation als Verschiebung, Rotationsmatrix und Skalierungsvektor zurück.
*/
void Matrix4x4::getTransformation (Vector3D &translation, Matrix3x3 &rotation, Vector3D &scale) const
{
  // Rotationsmatrix berechnen
  rotation = Matrix3x3 (	Vector3D (m[0][0], m[0][1], m[0][2]),
    Vector3D (m[1][0], m[1][1], m[1][2]),
    Vector3D (m[2][0], m[2][1], m[2][2]));
  scale(0) = rotation[0].length ();
  scale(1) = rotation[1].length ();
  scale(2) = rotation[2].length ();

  // Skalierung aus Rotationsmatrix entfernen
  rotation[0] = 1.0/scale(0) * rotation[0];
  rotation[1] = 1.0/scale(1) * rotation[1];
  rotation[2] = 1.0/scale(2) * rotation[2];

  translation = Vector3D (m[3][0], m[3][1], m[3][2]);
}