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

#include "Matrix2x2.h"
#include "Matrix2x3.h"
#include "Matrix3x2.h"
#include "math.h"

using namespace nspace;
/** Standard-Konstruktor: erstellt die Einheitsmatrix
*/
Matrix2x2::Matrix2x2()
{
  v[0] = Vector2D (1,0);
  v[1] = Vector2D (0,1);
}

/** Konstruktor: Erstellt die Matrix mit den Zeilenvektoren v0, v1
*/
Matrix2x2::Matrix2x2 (const Vector2D& v0, const Vector2D& v1)
{
  v[0] = v0;
  v[1] = v1;
}

/** Konstruktor: Erstellt die Matrix mit dem linken oberen Teil der 3x3 Matrix
*/
Matrix2x2::Matrix2x2 (const Matrix3x3& m)
{
  v[0].v[0] = m.v[0].v[0];
  v[0].v[1] = m.v[0].v[1];
  v[1].v[0] = m.v[1].v[0];
  v[1].v[1] = m.v[1].v[1];
}

/** Negation: -m\n
* Negiert alle Elemente der Matrix
*/
Matrix2x2 nspace::operator - (const Matrix2x2& a)
{
  return Matrix2x2(-a.v[0], -a.v[1]);
}

/** Addition: m1 + m2\n
* Elementweise Addition von m1 mit m2
*/
Matrix2x2 nspace::operator + (const Matrix2x2& a, const Matrix2x2& b)
{
  return Matrix2x2(a.v[0] + b.v[0], a.v[1] + b.v[1]);
}

/** Subtraktion: m1 - m2\n
* Elementweise Subtraktion
*/
Matrix2x2 nspace::operator - (const Matrix2x2& a, const Matrix2x2& b)
{
  return Matrix2x2(a.v[0] - b.v[0], a.v[1] - b.v[1]);
}

/** Multiplikation: m1 * m2\n
* Matrixmultiplikation von m1 mit m2
*/
Matrix2x2 nspace::operator * (const Matrix2x2& a, const Matrix2x2& b)
{
  Matrix2x2 c;
  for (int i=0; i < 2; i++)
  {
    c.v[i].v[0] = a.v[i].v[0]*b.v[0].v[0] + a.v[i].v[1]*b.v[1].v[0];
    c.v[i].v[1] = a.v[i].v[0]*b.v[0].v[1] + a.v[i].v[1]*b.v[1].v[1];
  }
  return c;
}

/** Multiplikation: m1 * m2\n
* Matrixmultiplikation von m1 mit m2
*/
Matrix2x2 nspace::operator * (const Matrix2x3& a, const Matrix3x2& b)
{
  Matrix2x2 c;
  for (int i=0; i < 2; i++)
  {
    c.v[i].v[0] = a.v[i].v[0]*b.v[0].v[0] + a.v[i].v[1]*b.v[1].v[0] + a.v[i].v[2]*b.v[2].v[0];
    c.v[i].v[1] = a.v[i].v[0]*b.v[0].v[1] + a.v[i].v[1]*b.v[1].v[1] + a.v[i].v[2]*b.v[2].v[1];
  }
  return c;
}

/** Multiplikation: d*a\n
* Elementweise Multiplikation einer Matrix mit einer Zahl
*/
Matrix2x2 nspace::operator * (const Real d, const Matrix2x2& a)
{
  return Matrix2x2 (d*a.v[0], d*a.v[1]);
}

/** Transponiert die 2x2-Matrix
*/
Matrix2x2 Matrix2x2::transpose () const
{
  return Matrix2x2 (	Vector2D(v[0].v[0], v[1].v[0]),
    Vector2D(v[0].v[1], v[1].v[1]));
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
*/
Vector2D& Matrix2x2::operator [] ( int i)
{
  return v[i];
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
*/
const Vector2D& Matrix2x2::operator [] ( int i) const
{
  return v[i];
}

/** Gibt die Inverse der Matrix zurück.
*/
Matrix2x2 Matrix2x2::inverse () const
{
  Matrix2x2 inv;

  Real a = v[0].v[0];
  Real b = v[0].v[1];
  Real c = v[1].v[0];
  Real d = v[1].v[1];
  Real Div = -b*c + a*d;
  if (fabs(Div) < 1.0e-009)
  {
    // print "Fehler in Matrixinvertierung"
    return Matrix2x2();
  }
  return Matrix2x2 ( Vector2D (d/Div, -b/Div), Vector2D (-c/Div, a/Div));
}

/** Stream-Ausgabe der Matrix
*/
std::ostream& nspace::operator << (std::ostream& s, const Matrix2x2& m)
{
  return s << m.v[0] << '\n' << m.v[1];
}

/** Zugriff per Index auf die einzelnen Komponenten der Matrix.
*/
Real& Matrix2x2::operator () (int i, int j)
{
  return v[i](j);
}

/** Zugriff per Index auf die einzelnen Komponenten der Matrix.
*/
const Real& Matrix2x2::operator () (int i, int j) const
{
  return v[i](j);
}