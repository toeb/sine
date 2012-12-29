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

#include "math.h"
#include "Vector2D.h"
#include "Matrix2x2.h"
#include "Matrix3x2.h"

using namespace nspace;

;
/** Konstruktor: Erzeugt einen Vektor mit den übergebenen Koordinaten.
*/
Vector2D::Vector2D(const Real vx, const Real vy)
{
  v[0] = vx;
  v[1] = vy;
}

/** Konstruktor: Erzeugt einen Vektor mit den ersten beiden Koordinaten des 3D Vektors.
*/
Vector2D::Vector2D(const Vector3D vec)
{
  v[0] = vec.v[0];
  v[1] = vec.v[1];
}

/** Standard-Konstruktor: Erzeugt den Vektor (0,0)
*/
Vector2D::Vector2D()
{
  v[0] = 0;
  v[1] = 0;
}

/** Zuweisung: v1 = v2\n
* Kopiert die Werte von Vektor v2 in Vektor v1.
*/
Vector2D& Vector2D::operator = (const Vector2D& vn)
{
  v[0] = vn.v[0];
  v[1] = vn.v[1];
  return *this;
}

/** Vektor-Subtraktion: v1 -= v2\n
* Subtrahiert Vektor v2 von v1
*/
Vector2D& Vector2D::operator -= (const Vector2D& vn)
{
  v[0] -= vn.v[0];
  v[1] -= vn.v[1];
  return *this;
}

/** Vektor-Addition: v1 += v2\n
* Addiert Vektor v2 zu v1
*/
Vector2D& Vector2D::operator += (const Vector2D& vn)
{
  v[0] += vn.v[0];
  v[1] += vn.v[1];
  return *this;
}

/** Multiplikation mit Konstanter d: v1 *= d\n
* Multipliziert den Vektor v1 mit d
*/
Vector2D& Vector2D::operator *= ( const Real d )
{
  v[0] *= d;
  v[1] *= d;
  return *this;
}

/** Division mit Konstanter d: v1 /= d\n
* Teilt jede Komponente des Vektors v1 durch d.\n
* d darf nicht 0 sein!!!
*/
Vector2D& Vector2D::operator /= ( const Real d )
{
  Real d_inv = 1/d;
  v[0] *= d_inv;
  v[1] *= d_inv;
  return *this;
}

// FRIENDS

/** Gleichheit: v1 == v2 \n
* Überprüft die Gleichheit der Komponenten von Vektor v1 und v2.
*/
bool nspace::operator == (const Vector2D &a, const Vector2D &b)
{
  return ((a.v[0] == b.v[0]) && (a.v[1] == b.v[1]));
  //	return ((fabs (a.v[0]-b.v[0]) < EPSILON) && (fabs (a.v[1]-b.v[1]) < EPSILON));
}

/** Ungleichheit: v1 != v2 \n
* Überprüft die Ungleichheit der Komponenten von Vektor v1 und v2.
*/
bool nspace::operator != (const Vector2D &a, const Vector2D &b)
{
  return ((a.v[0] != b.v[0]) || (a.v[1] != b.v[1]));
}

/** Kleiner: v1 < v2 \n
* Kleiner wird hier folgendermassen definiert:\n
* (x1,y1) < (x2,y2) <=> (x1 < x2) || ((x1 == x2) && (y1 < y2)) \n
* Wird benötigt für eine Sortierung der Vektoren, um anschliessend
* doppelte Punkte zu entfernen.
*/
bool nspace::operator < (const Vector2D &a, const Vector2D &b)
{
  if (a.v[0] < b.v[0])
    return true;
  else if (a.v[0] == b.v[0])
  {
    if (a.v[1] < b.v[1])
      return true;
  }
  return false;
}

/** Negation: -v1 \n
* Negiert alle Komponenten des Vektor v1
*/
Vector2D nspace::operator - (const Vector2D& a)
{
  return Vector2D(-a.v[0],-a.v[1]);
}

/** Addition: v1 + v2\n
* Addiert v1 und v2 komponentenweise
*/
Vector2D nspace::operator + (const Vector2D& a, const Vector2D& b)
{
  return Vector2D(a.v[0]+ b.v[0], a.v[1] + b.v[1]);
}

/** Subtraktion: v1 - v2\n
* Subtrahiert v1 und v2 komponentenweise
*/
Vector2D nspace::operator - (const Vector2D& a, const Vector2D& b)
{
  return Vector2D(a.v[0]-b.v[0], a.v[1]-b.v[1]);
}

/** Multiplikation mit Konstanter: v1*d\n
* Multipliziert alle Komponenten von v1 mit d
*/
Vector2D nspace::operator * (const Vector2D& a, const Real d)
{
  return Vector2D(d*a.v[0], d*a.v[1]);
}

/** Multiplikation mit Konstanter: d*v1\n
* Multipliziert alle Komponenten von v1 mit d
*/
Vector2D nspace::operator * (const Real d, const Vector2D& a)
{
  return a*d;
}

/** Degenerierte Matrixmultiplikation: v1 * v2\n
* ( x1 0  0  )   ( x2 )\n
* ( 0  y1 0  ) * ( y2 )\n
* ( 0  0  z1 )   ( z2 )\n
*/
Vector2D nspace::operator | (const Vector2D& a, const Vector2D& b)
{
  return Vector2D (a.v[0]*b.v[0],a.v[1]*b.v[1]);
}

/** Skalarprodukt: v1 * v2\n
* x1*x2 + y1*y2 + z1*z2
*/
Real nspace::operator * (const Vector2D& a, const Vector2D& b)
{
  return (a.v[0]*b.v[0] + a.v[1]*b.v[1]);
}

/** Multiplikation von Zeilenvektor v mit 2x2 Matrix m\n
* Rechtsseitige Matrixmultiplikation
*/
Vector2D nspace::operator * (const Vector2D& v, const Matrix2x2& m)
{
  return Vector2D (	v.v[0]*m.v[0].v[0] + v.v[1]*m.v[1].v[0],
    v.v[0]*m.v[0].v[1] + v.v[1]*m.v[1].v[1]);
}

/** Multiplikation von Spaltenvektor v mit 2x2 Matrix m\n
* Linksseitige Matrixmultiplikation
*/
Vector2D nspace::operator * (const Matrix2x2& m, const Vector2D& v)
{
  return Vector2D (	v.v[0]*m.v[0].v[0] + v.v[1]*m.v[0].v[1],
    v.v[0]*m.v[1].v[0] + v.v[1]*m.v[1].v[1]);
}

/** Multiplikation von Zeilenvektor v mit 3x2 Matrix m\n
* Rechtsseitige Matrixmultiplikation
*/
Vector2D nspace::operator * (const Vector3D& v, const Matrix3x2& m)
{
  return Vector2D ( 	v.v[0]*m.v[0].v[0] + v.v[1]*m.v[1].v[0] + v.v[2]*m.v[2].v[0],
    v.v[0]*m.v[0].v[1] + v.v[1]*m.v[1].v[1] + v.v[2]*m.v[2].v[1]);
}

/** Multiplikation von Zeilenvektor v mit 3x2 Matrix m\n
* Linksseitige Matrixmultiplikation
*/
Vector2D nspace::operator * (const Matrix2x3& m, const Vector3D& v)
{
  return Vector2D ( 	v.v[0]*m.v[0].v[0] + v.v[1]*m.v[0].v[1] + v.v[2]*m.v[0].v[2],
    v.v[0]*m.v[1].v[0] + v.v[1]*m.v[1].v[1] + v.v[2]*m.v[1].v[2]);
}

/** Berechnet die Länge des Vektors vom aktuellen Punkt zu Punkt a.
*/
Real Vector2D::distance (const Vector2D & a) const
{
  return (*this - a).length ();
}

/** Berechnet die quadratische Länge des Vektors vom aktuellen Punkt zu Punkt a.
*/
Real Vector2D::distance2 (const Vector2D & a) const
{
  return (*this - a).length2 ();
}

/** Stream-Ausgabe des Vektors
*/
std::ostream& nspace::operator << (std::ostream& s, const Vector2D& v)
{
  return s << "( " << v.v[0] << ", " << v.v[1]  << " )";
}