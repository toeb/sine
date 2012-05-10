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

#include "Matrix3x3.h"
#include "math.h"
#include "Vector3D.h"
#include <iostream>

using namespace std;
using namespace IBDS;
#define INC //inc();
#define DEC //dec();
int counter = 0;
long totalchanges = 0;
void inc(){
  counter++;
  totalchanges++;
  if(totalchanges % 1000==0)cout << "Matrix3x3 Count "<<counter<<endl;
}
void dec(){
  counter--;
  totalchanges++;
  if(totalchanges % 1000==0)cout << "Matrix3x3 Count "<<counter<<endl;
}
/** Standard-Konstruktor: erstellt die Einheitsmatrix
  */
Matrix3x3::Matrix3x3()
{
	v[0] = Vector3D (1,0,0);
	v[1] = Vector3D (0,1,0);
	v[2] = Vector3D (0,0,1);  
  INC
}
/** Konstruktor: Erstellt die Matrix mit den Zeilenvektoren v0, v1, v2
  */
Matrix3x3::Matrix3x3 (const Vector3D& v0, const Vector3D& v1, const Vector3D& v2)
{
	v[0] = v0; 
	v[1] = v1; 
	v[2] = v2; 
  INC
}
Matrix3x3::Matrix3x3(const Matrix3x3 & rhs){
  assign(rhs);
  INC
}

void Matrix3x3::assign(const Matrix3x3 & value){
  v[0].v[0] = value.v[0].v[0]; v[0].v[1] = value.v[0].v[1]; v[0].v[2] = value.v[0].v[2];
  v[1].v[0] = value.v[1].v[0]; v[1].v[1] = value.v[1].v[1]; v[1].v[2] = value.v[1].v[2];
  v[2].v[0] = value.v[2].v[0]; v[2].v[1] = value.v[2].v[1]; v[2].v[2] = value.v[2].v[2];
}

Matrix3x3::~Matrix3x3(){
 // delete v;
  DEC
}
Matrix3x3 * zero = new Matrix3x3(Vector3D(),Vector3D(),Vector3D());
Matrix3x3 * identityMatrix= new Matrix3x3();

const Matrix3x3 & Matrix3x3::Zero(){  
  return *zero;
}

const Matrix3x3 & Matrix3x3::Identity(){
  return *identityMatrix;
}

bool Matrix3x3::isZero(){
  return Zero()==*this;
}



bool IBDS::operator== (const Matrix3x3& a,const Matrix3x3& b){
  return a(0,0) == b(0,0) && a(0,1) == b(0,1) && a(0,2) == b(0,0) 
      && a(1,0) == b(1,0) && a(1,1) == b(1,1) && a(1,2) == b(1,2) 
      && a(2,0) == b(2,0) && a(2,1) == b(2,1) && a(2,2) == b(2,2);
}
bool IBDS::operator!= (const Matrix3x3& a,const Matrix3x3& b){
  return !(a==b);
}
/** Negation: -m\n
  * Negiert alle Elemente der Matrix
  */
Matrix3x3 IBDS::operator - (const Matrix3x3& a)
{ 
	return Matrix3x3(-a.v[0], -a.v[1], -a.v[2]); 
}

/** Addition: m1 + m2\n
  * Elementweise Addition von m1 mit m2
  */
Matrix3x3 IBDS::operator + (const Matrix3x3& a, const Matrix3x3& b)
{ 
	return Matrix3x3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); 
}

/** Subtraktion: m1 - m2\n
  * Elementweise Subtraktion 
  */
Matrix3x3 IBDS::operator - (const Matrix3x3& a, const Matrix3x3& b)
{ 
	return Matrix3x3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]); 
}

/** Multiplikation: m1 * m2\n
  * Matrixmultiplikation von m1 mit m2
  */
Matrix3x3 IBDS::operator * (const Matrix3x3& a, const Matrix3x3& b) 
{
	Matrix3x3 c;

	c.v[0].v[0] = a.v[0].v[0]*b.v[0].v[0] + a.v[0].v[1]*b.v[1].v[0] + a.v[0].v[2]*b.v[2].v[0];
	c.v[0].v[1] = a.v[0].v[0]*b.v[0].v[1] + a.v[0].v[1]*b.v[1].v[1] + a.v[0].v[2]*b.v[2].v[1];
	c.v[0].v[2] = a.v[0].v[0]*b.v[0].v[2] + a.v[0].v[1]*b.v[1].v[2] + a.v[0].v[2]*b.v[2].v[2];

	c.v[1].v[0] = a.v[1].v[0]*b.v[0].v[0] + a.v[1].v[1]*b.v[1].v[0] + a.v[1].v[2]*b.v[2].v[0];
	c.v[1].v[1] = a.v[1].v[0]*b.v[0].v[1] + a.v[1].v[1]*b.v[1].v[1] + a.v[1].v[2]*b.v[2].v[1];
	c.v[1].v[2] = a.v[1].v[0]*b.v[0].v[2] + a.v[1].v[1]*b.v[1].v[2] + a.v[1].v[2]*b.v[2].v[2];

	c.v[2].v[0] = a.v[2].v[0]*b.v[0].v[0] + a.v[2].v[1]*b.v[1].v[0] + a.v[2].v[2]*b.v[2].v[0];
	c.v[2].v[1] = a.v[2].v[0]*b.v[0].v[1] + a.v[2].v[1]*b.v[1].v[1] + a.v[2].v[2]*b.v[2].v[1];
	c.v[2].v[2] = a.v[2].v[0]*b.v[0].v[2] + a.v[2].v[1]*b.v[1].v[2] + a.v[2].v[2]*b.v[2].v[2];

	return c;
}

/** Multiplikation: d*a\n
  * Elementweise Multiplikation einer Matrix mit einer Zahl
  */
Matrix3x3 IBDS::operator * (const Real d, const Matrix3x3& a)
{
	return Matrix3x3 (d*a.v[0], d*a.v[1], d*a.v[2]);
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  */
Vector3D& Matrix3x3::operator [] ( int i) 
{
    return v[i];
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  */
const Vector3D& Matrix3x3::operator [] ( int i) const
{
    return v[i];
}


/** Zugriff per Index auf die einzelnen Komponenten der Matrix.
  */
Real& Matrix3x3::operator () (int i, int j) 
{
	return v[i][j];
}

/** Zugriff per Index auf die einzelnen Komponenten der Matrix.
  */
const Real& Matrix3x3::operator () (int i, int j) const
{
	return v[i][j];
}

/** Transponiert die 3x3-Matrix 
  */
Matrix3x3 Matrix3x3::transpose () const
{
	return Matrix3x3 (	Vector3D(v[0].v[0], v[1].v[0], v[2].v[0]),
				Vector3D(v[0].v[1], v[1].v[1], v[2].v[1]),
				Vector3D(v[0].v[2], v[1].v[2], v[2].v[2]));
}


/** Gibt die Inverse der Matrix zurück.
  */
Matrix3x3 Matrix3x3::inverse () const
{
	Real a = v[0].v[0];
	Real b = v[0].v[1];
	Real c = v[0].v[2];
	Real d = v[1].v[0];
	Real e = v[1].v[1];
	Real f = v[1].v[2];
	Real g = v[2].v[0];
	Real h = v[2].v[1];
	Real i = v[2].v[2];
	Real Div = -c*e*g+b*f*g+c*d*h-a*f*h-b*d*i+a*e*i;
	if (fabs(Div) < EPSILON)
	{
		std::cout << "matrix inversion failed\n";
		return Matrix3x3 (Vector3D (), Vector3D (), Vector3D ());
	}
	Div = (1.0/Div);
	return Matrix3x3 (	(Vector3D(-f*h+e*i,c*h-b*i,-c*e+b*f)*Div),
				(Vector3D(f*g-d*i,-c*g+a*i,c*d-a*f)*Div),
				(Vector3D(-e*g+d*h,b*g-a*h,-b*d+a*e)*Div));
				// hat Mathematica so ermittelt
}

/** Gibt die Inverse einer symmetrischen, nicht singulären Matrix zurück.
  */
Matrix3x3 Matrix3x3::symmInverse () const
{
	Real e2_df = v[1].v[2]*v[1].v[2] - v[1].v[1]*v[2].v[2];  // e^2 - d*f
	Real bf = v[0].v[1]*v[2].v[2];
	Real ce = v[0].v[2]*v[1].v[2];
	Real c2 = v[0].v[2]*v[0].v[2];
	Real cd = v[0].v[2]*v[1].v[1];
	Real be = v[0].v[1]*v[1].v[2];
	Real af = v[0].v[0]*v[2].v[2];
	Real ae = v[0].v[0]*v[1].v[2];
	Real bc = v[0].v[1]*v[0].v[2];
	Real b2 = v[0].v[1]*v[0].v[1];
	Real ad = v[0].v[0]*v[1].v[1];

	Real Div = 1.0 / (c2*v[1].v[1] + v[0].v[1] * (bf - 2 * ce) + v[0].v[0]* e2_df  );

	Real a = e2_df * Div;
	Real b = (bf - ce) * Div;
	Real c = (cd - be) * Div;
	Real d = (c2 - af) * Div;
	Real e = (ae - bc) * Div;
	Real f = (b2 - ad) * Div;

	return Matrix3x3 (Vector3D(a,b,c),
				Vector3D(b,d,e),
				Vector3D(c,e,f));
}



/** Stream-Ausgabe der Matrix
  */
std::ostream& IBDS::operator << (std::ostream& s, const Matrix3x3& m)
{ 
	return s << m.v[0] << '\n' << m.v[1] << '\n' << m.v[2];
}

/** Gibt die Anzahl der Spalten zurück.
*/
int Matrix3x3::getCols() const
{
	return 3;
}

/** Gibt die Anzahl der Zeilen zurück.
*/
int Matrix3x3::getRows() const
{
	return 3;
}
