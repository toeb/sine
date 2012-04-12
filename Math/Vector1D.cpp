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
#include "Matrix2x2.h"
#include "Matrix3x2.h"
#include "Vector1D.h"

using namespace IBDS;

/** Konstruktor: Erzeugt einen Vektor mit den �bergebenen Koordinaten. 
  */
Vector1D::Vector1D(const Real vx)
{
	v = vx;
}

/** Konstruktor: Erzeugt einen Vektor mit der ersten Koordinate des 3D Vektors. 
*/
Vector1D::Vector1D(const Vector3D vec)
{
	v = vec.v[0];
}

/** Standard-Konstruktor: Erzeugt den Vektor (0)
  */
Vector1D::Vector1D()
{
	v = 0;
}

/** Zuweisung: v1 = v2\n
  * Kopiert die Werte von Vektor v2 in Vektor v1.
  */
Vector1D& Vector1D::operator = (const Vector1D& vn)
{ 
	v = vn.v; 
	return *this; 
}

/** Zuweisung: v1 = v2\n
* Kopiert die Werte von Vektor v2 in Vektor v1.
*/
Vector1D& Vector1D::operator = (const Real& d)
{ 
	v = d; 
	return *this; 
}

/** Vektor-Subtraktion: v1 -= v2\n
  * Subtrahiert Vektor v2 von v1
  */
Vector1D& Vector1D::operator -= (const Vector1D& vn)
{ 
	v -= vn.v; 
	return *this; 
}

/** Vektor-Addition: v1 += v2\n
  * Addiert Vektor v2 zu v1
  */
Vector1D& Vector1D::operator += (const Vector1D& vn)
{ 
	v += vn.v; 
	return *this; 
}

/** Multiplikation mit Konstanter d: v1 *= d\n
  * Multipliziert den Vektor v1 mit d
  */ 
Vector1D& Vector1D::operator *= ( const Real d )
{ 
	v *= d; 
	return *this; 
}

/** Division mit Konstanter d: v1 /= d\n
  * Teilt jede Komponente des Vektors v1 durch d.\n
  * d darf nicht 0 sein!!!
  */
Vector1D& Vector1D::operator /= ( const Real d )
{ 
	Real d_inv = 1/d;
	v *= d_inv; 
	return *this; 
}


// FRIENDS

/** Gleichheit: v1 == v2 \n
  * �berpr�ft die Gleichheit der Komponenten von Vektor v1 und v2.
  */
bool IBDS::operator == (const Vector1D &a, const Vector1D &b)
{
	return (a.v == b.v);
//	return ((fabs (a.v[0]-b.v[0]) < EPSILON) && (fabs (a.v[1]-b.v[1]) < EPSILON));
}

/** Ungleichheit: v1 != v2 \n
  * �berpr�ft die Ungleichheit der Komponenten von Vektor v1 und v2.
  */
bool IBDS::operator != (const Vector1D &a, const Vector1D &b)
{
	return (a.v != b.v);
}

/** Kleiner: v1 < v2 \n
  * Kleiner wird hier folgendermassen definiert:\n
  * (x1,y1) < (x2,y2) <=> (x1 < x2) || ((x1 == x2) && (y1 < y2)) \n
  * Wird ben�tigt f�r eine Sortierung der Vektoren, um anschliessend
  * doppelte Punkte zu entfernen.
  */
bool IBDS::operator < (const Vector1D &a, const Vector1D &b)
{
	return (a.v < b.v);
}


/** Negation: -v1 \n
  * Negiert alle Komponenten des Vektor v1
  */
Vector1D IBDS::operator - (const Vector1D& a)
{  
	return Vector1D(-a.v); 
}

/** Addition: v1 + v2\n
  * Addiert v1 und v2 komponentenweise
  */
Vector1D IBDS::operator + (const Vector1D& a, const Vector1D& b)
{ 
	return Vector1D(a.v+ b.v); 
}

/** Subtraktion: v1 - v2\n
  * Subtrahiert v1 und v2 komponentenweise
  */
Vector1D IBDS::operator - (const Vector1D& a, const Vector1D& b)
{ 
	return Vector1D(a.v-b.v); 
}

/** Multiplikation mit Konstanter: v1*d\n
  * Multipliziert alle Komponenten von v1 mit d
  */
Vector1D IBDS::operator * (const Vector1D& a, const Real d)
{ 
	return Vector1D(d*a.v); 
}

/** Multiplikation mit Konstanter: d*v1\n
  * Multipliziert alle Komponenten von v1 mit d
  */
Vector1D IBDS::operator * (const Real d, const Vector1D& a)
{ 
	return a*d; 
}

/** Degenerierte Matrixmultiplikation: v1 * v2\n
  * ( x1 0  0  )   ( x2 )\n
  * ( 0  y1 0  ) * ( y2 )\n
  * ( 0  0  z1 )   ( z2 )\n
  */
Vector1D IBDS::operator | (const Vector1D& a, const Vector1D& b)
{
	return Vector1D (a.v*b.v);
}
    
/** Skalarprodukt: v1 * v2\n
  * x1*x2 + y1*y2 + z1*z2
  */
Real IBDS::operator * (const Vector1D& a, const Vector1D& b)
{ 
	return (a.v*b.v); 
}



/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  */
Real& Vector1D::operator [] ( int i)
{
	return v;
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  */
const Real& Vector1D::operator [] ( int i) const
{
    return v;
}


/** Berechnet die L�nge des Vektors.
  */
Real Vector1D::length () const
{  
	return v; 
}

/** Berechnet die L�nge des Vektors im Quadrat. 
  */ 
Real Vector1D::length2() const
{  
	return v*v; 
}

/** Normiert den Vektor (Division durch 0 bei L�nge 0 des Vektors wird nicht abgefangen!!!)
  */
void Vector1D::normalize() 
{ 
	v = 1.0; 
}

/** Berechnet die L�nge des Vektors vom aktuellen Punkt zu Punkt a.
  */
Real Vector1D::distance (Vector1D a) const
{
	return (*this - a).length();
}

/** Berechnet die quadratische L�nge des Vektors vom aktuellen Punkt zu Punkt a.
  */
Real Vector1D::distance2 (Vector1D a) const
{
	return (*this - a).length2 ();
}

/** Stream-Ausgabe des Vektors 
  */
std::ostream& IBDS::operator << (std::ostream& s, const Vector1D& v)
{ 
	return s << "( " << v.v << " )"; 
}
   
/** Gibt die Anzahl der Spalten zur�ck.
*/
int Vector1D::getCols() const
{
	return 1;
}

/** Gibt die Anzahl der Zeilen zur�ck.
*/ 
int Vector1D::getRows() const
{
	return 1;
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  * Der Index j wird beim Vektor ignoriert.
  */
Real& Vector1D::operator () (int i, int j) 
{
	return v;
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  * Der Index j wird beim Vektor ignoriert.
  */
const Real& Vector1D::operator () (int i, int j) const
{
    return v;
}
