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
#include "Matrix3x3.h"
#include "Matrix2x3.h"
#include "Matrix3x2.h"
#include "Vector2D.h"
#include "Vector1D.h"
#include <iostream>
using namespace std;
using namespace IBDS;

#define VEC_INC //incVec();
#define VEC_DEC //decVec();

int vecCount=0;
long vecChanges=0;

Vector3D _e1(1,0,0);
Vector3D _e2(0,1,0);
Vector3D _e3(0,0,1);

const Vector3D & Vector3D::e1(){
  return _e1;
}
const Vector3D & Vector3D::e2(){
  return _e2;
}
const Vector3D & Vector3D::e3(){
  return _e3;
}

void incVec(){
  vecCount++;
  vecChanges++;
  if(vecChanges % 1000 ==0)cout << "Vector3D Count:"<<vecCount<<endl;
}
void decVec(){
  vecCount--;
  vecChanges++;
  if(vecChanges % 1000 ==0)cout << "Vector3D Count:"<<vecCount<<endl; 
}
void Vector3D::setZero(){
  v[0] = 0;
  v[1] = 0;
  v[2] = 0;
}
void Vector3D::assign(const Vector3D & vector){  
	v[0] = vector.v[0];
	v[1] = vector.v[1];
	v[2] = vector.v[2];
}

/** Konstruktor: Erzeugt einen Vektor mit den übergebenen Koordinaten. 
  */
Vector3D::Vector3D(const Real vx, const Real vy, const Real vz)
{
	v[0] = vx;
	v[1] = vy;
	v[2] = vz;
  VEC_INC
}


/** Standard-Konstruktor: Erzeugt den Vektor (0,0,0)
  */
Vector3D::Vector3D()
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
  VEC_INC
}

/** Copy constructor
  */
Vector3D::Vector3D(const Vector3D &vector)
{
  assign(vector);
  VEC_INC
}

Vector3D::~Vector3D(){
  VEC_DEC
}

/** Zuweisung: v1 = v2\n
  * Kopiert die Werte von Vektor v2 in Vektor v1.
  */
Vector3D& Vector3D::operator = (const Vector3D& vn)
{ 
	memcpy (v, vn.v, sizeof(Real)*3);
	return *this; 
}

/** Vektor-Subtraktion: v1 -= v2\n
  * Subtrahiert Vektor v2 von v1
  */
Vector3D& Vector3D::operator -= (const Vector3D& vn)
{ 
	v[0] -= vn.v[0]; 
	v[1] -= vn.v[1]; 
	v[2] -= vn.v[2]; 
	return *this; 
}

/** Vektor-Addition: v1 += v2\n
  * Addiert Vektor v2 zu v1
  */
Vector3D& Vector3D::operator += (const Vector3D& vn)
{ 
	v[0] += vn.v[0]; 
	v[1] += vn.v[1]; 
	v[2] += vn.v[2]; 
	return *this; 
}

/** Multiplikation mit Konstanter d: v1 *= d\n
  * Multipliziert den Vektor v1 mit d
  */ 
Vector3D& Vector3D::operator *= ( const Real d )
{ 
	v[0] *= d; 
	v[1] *= d; 
	v[2] *= d; 
	return *this; 
}

/** Division mit Konstanter d: v1 /= d\n
  * Teilt jede Komponente des Vektors v1 durch d.\n
  * d darf nicht 0 sein!!!
  */
Vector3D& Vector3D::operator /= ( const Real d )
{ 
	Real d_inv = 1/d;
	v[0] *= d_inv; 
	v[1] *= d_inv; 
	v[2] *= d_inv;
	return *this; 
}

Vector3D zeroVector;
const Vector3D & Vector3D::Zero(){
  return zeroVector;
}
// FRIENDS

/** Gleichheit: v1 == v2 \n
  * Überprüft die Gleichheit der Komponenten von Vektor v1 und v2.
  */
bool IBDS::operator == (const Vector3D &a, const Vector3D &b)
{
	return ((a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]));
//	return ((fabs (a.v[0]-b.v[0]) < EPSILON) && (fabs (a.v[1]-b.v[1]) < EPSILON) && (fabs(a.v[2]-b.v[2]) < EPSILON));
}

/** Ungleichheit: v1 != v2 \n
  * Überprüft die Ungleichheit der Komponenten von Vektor v1 und v2.
  */
bool IBDS::operator != (const Vector3D &a, const Vector3D &b)
{
	return ((a.v[0] != b.v[0]) || (a.v[1] != b.v[1]) || (a.v[2] != b.v[2]));
}

/** Kleiner: v1 < v2 \n
  * Kleiner wird hier folgendermassen definiert:\n
  * (x1,y1,z1) < (x2,y2,z2) <=> (x1 < x2) || ((x1 == x2) && (y1 < y2)) || ((x1 == x2) && (y1 == y2) && (z1 < z2))\n
  * Wird benötigt für eine Sortierung der Vektoren, um anschliessend
  * doppelte Punkte zu entfernen.
  */
bool IBDS::operator < (const Vector3D &a, const Vector3D &b)
{
	if (a.v[0] < b.v[0])
		return true;
	else if (a.v[0] == b.v[0])
	{
		if (a.v[1] < b.v[1])
			return true;
		else if ((a.v[1] == b.v[1]) && (a.v[2] < b.v[2]))
			return true;
		else 
			return false;
	}
	else 
		return false;
}


/** Negation: -v1 \n
  * Negiert alle Komponenten des Vektor v1
  */
Vector3D IBDS::operator - (const Vector3D& a)
{  
	return Vector3D(-a.v[0],-a.v[1],-a.v[2]); 
}

/** Addition: v1 + v2\n
  * Addiert v1 und v2 komponentenweise
  */
Vector3D IBDS::operator + (const Vector3D& a, const Vector3D& b)
{ 
	return Vector3D(a.v[0]+ b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); 
}

/** Subtraktion: v1 - v2\n
  * Subtrahiert v1 und v2 komponentenweise
  */
Vector3D IBDS::operator - (const Vector3D& a, const Vector3D& b)
{ 
	return Vector3D(a.v[0]-b.v[0], a.v[1]-b.v[1], a.v[2]-b.v[2]); 
}

/** Multiplikation mit Konstanter: v1*d\n
  * Multipliziert alle Komponenten von v1 mit d
  */
Vector3D IBDS::operator * (const Vector3D& a, const Real d)
{ 
	return Vector3D(d*a.v[0], d*a.v[1], d*a.v[2]); 
}

/** Multiplikation mit Konstanter: d*v1\n
  * Multipliziert alle Komponenten von v1 mit d
  */
Vector3D IBDS::operator * (const Real d, const Vector3D& a)
{ 
	return a*d; 
}

/** Degenerierte Matrixmultiplikation: v1 * v2\n
  * ( x1 0  0  )   ( x2 )\n
  * ( 0  y1 0  ) * ( y2 )\n
  * ( 0  0  z1 )   ( z2 )\n
  */
Vector3D IBDS::operator | (const Vector3D& a, const Vector3D& b)
{
	return Vector3D (a.v[0]*b.v[0],a.v[1]*b.v[1],a.v[2]*b.v[2]);
}
    

/** Skalarprodukt: v1 * v2\n
  * x1*x2 + y1*y2 + z1*z2
  */
Real IBDS::operator * (const Vector3D& a, const Vector3D& b)
{ 
	return (a.v[0]*b.v[0] + a.v[1]*b.v[1] + a.v[2]*b.v[2]); 
}

/** Kreuzprodukt: v1 ^ v2\n
  * Berechnet das Kreuzprodukt der Vektoren v1 und v2
  */
Vector3D IBDS::operator ^ (const Vector3D& a, const Vector3D& b) 
{
	return Vector3D ( 	a.v[1]*b.v[2] - a.v[2]*b.v[1],
				a.v[2]*b.v[0] - a.v[0]*b.v[2],
				a.v[0]*b.v[1] - a.v[1]*b.v[0]);
}

/** Multiplikation von Zeilenvektor v mit 3x3 Matrix m\n
  * Rechtsseitige Matrixmultiplikation
  */
Vector3D IBDS::operator * (const Vector3D& v, const Matrix3x3& m) 
{
	return Vector3D ( 	v.v[0]*m.v[0].v[0] + v.v[1]*m.v[1].v[0] + v.v[2]*m.v[2].v[0],
				v.v[0]*m.v[0].v[1] + v.v[1]*m.v[1].v[1] + v.v[2]*m.v[2].v[1],
				v.v[0]*m.v[0].v[2] + v.v[1]*m.v[1].v[2] + v.v[2]*m.v[2].v[2]);
}

/** Multiplikation von Spaltenvektor v mit 3x3 Matrix m\n
  * Linksseitige Matrixmultiplikation
  */
Vector3D IBDS::operator * (const Matrix3x3& m, const Vector3D& v) 
{
	return Vector3D (v.v[0]*m.v[0].v[0] + v.v[1]*m.v[0].v[1] + v.v[2]*m.v[0].v[2],
				v.v[0]*m.v[1].v[0] + v.v[1]*m.v[1].v[1] + v.v[2]*m.v[1].v[2],
				v.v[0]*m.v[2].v[0] + v.v[1]*m.v[2].v[1] + v.v[2]*m.v[2].v[2]);
}

/** Multiplikation von Zeilenvektor v mit 3x3 Matrix m\n
* Rechtsseitige Matrixmultiplikation
*/
Vector3D IBDS::operator * (const Vector3D& v, const Vector1D& m) 
{
	return Vector3D (v.v[0]*m.v, v.v[1]*m.v, v.v[2]*m.v);
}

/** Multiplikation von Spaltenvektor v mit 3x3 Matrix m\n
* Linksseitige Matrixmultiplikation
*/
Vector3D IBDS::operator * (const Vector1D& m, const Vector3D& v) 
{
	return Vector3D (v.v[0]*m.v, v.v[1]*m.v, v.v[2]*m.v);
}

/** Multiplikation von Spaltenvektor v mit 3x2 Matrix m\n
* Linksseitige Matrixmultiplikation
*/
Vector3D IBDS::operator * (const Matrix3x2& m, const Vector2D& v) 
{
	return Vector3D (	v.v[0]*m.v[0].v[0] + v.v[1]*m.v[0].v[1],
						v.v[0]*m.v[1].v[0] + v.v[1]*m.v[1].v[1],
						v.v[0]*m.v[2].v[0] + v.v[1]*m.v[2].v[1]);
}

/** Multiplikation von Zeilenvektor v mit 2x3 Matrix m\n
* Rechtsseitige Matrixmultiplikation
*/
Vector3D IBDS::operator * (const Vector2D& v, const Matrix2x3& m) 
{
	return Vector3D ( 	v.v[0]*m.v[0].v[0] + v.v[1]*m.v[1].v[0],
						v.v[0]*m.v[0].v[1] + v.v[1]*m.v[1].v[1],
						v.v[0]*m.v[0].v[2] + v.v[1]*m.v[1].v[2]);
}

/** Multiplikation der Kreuproduktmatrix von v mit der 3x3 Matrix m.
  */
Matrix3x3 IBDS::operator , (const Matrix3x3& m, const Vector3D& v) 
{
	Matrix3x3 V = Matrix3x3 (Vector3D (0, -v.v[2], v.v[1]), 
							Vector3D (v.v[2], 0, -v.v[0]), 
							Vector3D (-v.v[1], v.v[0], 0));
	return m*V;
}

/** Multiplikation der 3x3 Matrix m mit der Kreuproduktmatrix von v.
  */
Matrix3x3 IBDS::operator , (const Vector3D& v, const Matrix3x3& m) 
{
	Matrix3x3 V = Matrix3x3 (Vector3D (0, -v.v[2], v.v[1]), 
							Vector3D (v.v[2], 0, -v.v[0]), 
							Vector3D (-v.v[1], v.v[0], 0));
	return V*m;
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  */
Real& Vector3D::operator [] ( int i)
{
	return v[i];
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  */
const Real& Vector3D::operator [] ( int i) const
{
	return v[i];
}


/** Berechnet die Länge des Vektors.
  */
Real Vector3D::length () const
{  
	return (Real) sqrt (v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); 
}

/** Berechnet die Länge des Vektors im Quadrat. 
  */ 
Real Vector3D::length2() const
{  
	return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; 
}

/** Normiert den Vektor (Division durch 0 bei Länge 0 des Vektors wird nicht abgefangen!!!)
  */
void Vector3D::normalize() 
{ 
	*this /= length(); 
}

/** Berechnet die Länge des Vektors vom aktuellen Punkt zu Punkt a.
  */
Real Vector3D::distance (const Vector3D &a) const
{
	return (*this - a).length ();
}

/** Berechnet die quadratische Länge des Vektors vom aktuellen Punkt zu Punkt a.
  */
Real Vector3D::distance2 (const Vector3D &a) const
{
	return (*this - a).length2 ();
}

/** Stream-Ausgabe des Vektors 
  */
std::ostream& IBDS::operator << (std::ostream& s, const Vector3D& v)
{ 
	return s << "( " << v.v[0] << ", " << v.v[1] << ", " << v.v[2] << " )"; 
}
   
/** Gibt die Anzahl der Spalten zurück.
*/
int Vector3D::getCols() const
{
	return 1;
}

/** Gibt die Anzahl der Zeilen zurück.
*/
int Vector3D::getRows() const
{
	return 3;
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  * Der Index j wird beim Vektor ignoriert.
  */
Real& Vector3D::operator () (int i, int j) 
{
	return v[i];
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  * Der Index j wird beim Vektor ignoriert.
  */
const Real& Vector3D::operator () (int i, int j) const
{
	return v[i];
}
