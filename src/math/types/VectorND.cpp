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

#include <math.h>
#include "VectorND.h"
#include <math/types/MatrixNxM.h>
#include <iostream>
using namespace std;
using namespace nspace;

/** Konstruktor: Erzeugt einen Vektor mit der Dimension 0. 
  */
VectorND::VectorND():n(0),v(0)
{
}

/** Konstruktor: Erzeugt einen Vektor mit der �bergebenen Dimension. 
  */
VectorND::VectorND(const int dim):n(dim),v(new Real[dim])
{
}

void VectorND::resize(int dim){
  if(dim==n)return;
  if(v)delete[] v;
  n=dim;
  v = new Real[dim];

}

/** Destruktor
  */
VectorND::~VectorND()
{
  n = 0;
  delete []v;
  v =0;
}

/** Zuweisung: v1 = v2\n
  * Kopiert die Werte von Vektor v2 in Vektor v1.
  */
VectorND& VectorND::operator = (const VectorND& vn)
{ 
  if(n !=vn.n){
    resize(vn.n);
  }
  #pragma omp parallel for
  for (int i=0; i < n; i++)
    v[i] = vn.v[i]; 
  return *this; 
}



/** Vektor-Subtraktion: v1 -= v2\n
  * Subtrahiert Vektor v2 von v1
  */
VectorND& VectorND::operator -= (const VectorND& vn)
{ 
  #pragma omp parallel for
  for (int i=0; i < n; i++)
    v[i] -= vn.v[i]; 
  return *this; 
}

/** Vektor-Addition: v1 += v2\n
  * Addiert Vektor v2 zu v1
  */
VectorND& VectorND::operator += (const VectorND& vn)
{ 
  #pragma omp parallel for
  for (int i=0; i < n; i++)
    v[i] += vn.v[i]; 
  return *this; 
}

/** Multiplikation mit Konstanter d: v1 *= d\n
  * Multipliziert den Vektor v1 mit d
  */ 
VectorND& VectorND::operator *= ( const Real d )
{ 
#pragma omp parallel for
  for (int i=0; i < n; i++)
    v[i] *= d; 
  return *this; 
}

/** Division mit Konstanter d: v1 /= d\n
  * Teilt jede Komponente des Vektors v1 durch d.\n
  * d darf nicht 0 sein!!!
  */
VectorND& VectorND::operator /= ( const Real d )
{ 
  Real d_inv = 1/d;
  #pragma omp parallel for
  for (int i=0; i < n; i++)
    v[i] *= d_inv; 
  return *this; 
}


// FRIENDS

/** Gleichheit: v1 == v2 \n
  * �berpr�ft die Gleichheit der Komponenten von Vektor v1 und v2.
  */
bool nspace::operator == (const VectorND &a, const VectorND &b)
{
  bool bl = true;
  #pragma omp parallel for
  for (int i=0; i < a.n; i++)
    bl = bl && (a.v[i] == b.v[i]);
  return bl;
}

/** Ungleichheit: v1 != v2 \n
  * �berpr�ft die Ungleichheit der Komponenten von Vektor v1 und v2.
  */
bool nspace::operator != (const VectorND &a, const VectorND &b)
{
  bool bl = false;
  for (int i=0; i < a.n; i++)
    bl = bl || (a.v[i] != b.v[i]);
  return bl;
}



/** Negation: -v1 \n
  * Negiert alle Komponenten des Vektor v1
  */
VectorND nspace::operator - (const VectorND& a)
{  
  VectorND vn(a.n);
  for (int i=0; i < a.n; i++)
    vn.v[i] = -a.v[i];
  return vn; 
}

/** Addition: v1 + v2\n
  * Addiert v1 und v2 komponentenweise
  */
VectorND nspace::operator + (const VectorND& a, const VectorND& b)
{ 
  VectorND  vn(a.n);

  for (int i=0; i < a.n; i++)
    vn.v[i] = a.v[i] + b.v[i];
  return vn; 
}

/** Subtraktion: v1 - v2\n
  * Subtrahiert v1 und v2 komponentenweise
  */
VectorND nspace::operator - (const VectorND& a, const VectorND& b)
{ 
  VectorND vn(a.n);
  for (int i=0; i < a.n; i++)
    vn.v[i] = a.v[i] - b.v[i];
  return vn; 
}

/** Multiplikation mit Konstanter: v1*d\n
  * Multipliziert alle Komponenten von v1 mit d
  */
VectorND  nspace::operator * (const VectorND& a, const Real d)
{ 
  VectorND vn(a.n);
  for (int i=0; i < a.n; i++){
    vn.v[i] = d*a.v[i];
  }
  return vn; 
}

/** Multiplikation mit Konstanter: d*v1\n
  * Multipliziert alle Komponenten von v1 mit d
  */
VectorND nspace::operator * (const Real d, const VectorND& a)
{ 
  VectorND ret = a*d;
  return ret; 
}

    

/** Skalarprodukt: v1 * v2\n
  * x1*x2 + y1*y2 + z1*z2
  */
Real nspace::operator * (const VectorND& a, const VectorND& b)
{ 
  Real s = 0.0;
  for (int i=0; i < a.n; i++)
    s += a.v[i]*b.v[i];
  return s; 
}


/** Multiplikation von Zeilenvektor v mit 2x2 Matrix m\n
  * Rechtsseitige Matrixmultiplikation
  */
VectorND nspace::operator * (const VectorND& v, const MatrixNxM& m) 
{
  int dim = m.cols();
  VectorND vn = VectorND (dim);
 
  for (int i=0; i < vn.n; i++)
  {
    vn.v[i] = 0.0;
    for (int j=0; j < v.n; j++)
      vn.v[i] += v.v[j]*m.v[j].v[i];
  }
  return vn;
}

/** Multiplikation von Spaltenvektor v mit 2x2 Matrix m\n
  * Linksseitige Matrixmultiplikation
  */
VectorND nspace::operator * (const MatrixNxM& m, const VectorND& v) 
{
  int dim = m.rows();
  VectorND vn = VectorND (dim);
  for (int i=0; i < m.rows(); i++)
  {
    vn.v[i] = 0.0;
    for (int j=0; j < m.cols(); j++)
      vn.v[i] += m.v[i].v[j]*v.v[j];
  }
  return vn;
}

/** Stream-Ausgabe des Vektors 
  */
std::ostream& nspace::operator << (std::ostream& s, const VectorND& v)
{ 
  s << "( ";
  for (int i=0; i < v.n-1; i++)
    s << v.v[i] << ", ";
  s << v.v[v.n-1] << " )"; 
  return s; 
}



/** Berechnet die L�nge des Vektors.
  */
Real VectorND::length () const
{  
  return (Real) sqrt (*this * *this); 
}

/** Berechnet die L�nge des Vektors im Quadrat. 
  */ 
Real VectorND::length2() const
{  
  return *this * *this; 
}

/** Normiert den Vektor (Division durch 0 bei L�nge 0 des Vektors wird nicht abgefangen!!!)
  */
void VectorND::normalize() 
{ 
  *this /= length(); 
}

/** Berechnet die L�nge des Vektors vom aktuellen Punkt zu Punkt a.
  */
Real VectorND::distance (VectorND a) const
{
  return (*this - a).length ();
}

/** Berechnet die quadratische L�nge des Vektors vom aktuellen Punkt zu Punkt a.
  */
Real VectorND::distance2 (VectorND a) const
{
  return (*this - a).length2 ();
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  * Der Index j wird beim Vektor ignoriert.
  */
Real& VectorND::operator () (int i, int j) 
{
  return v[i];
}

/** Zugriff per Index auf die einzelnen Komponenten des Vektors.
  * Der Index j wird beim Vektor ignoriert.
  */
const Real& VectorND::operator () (int i, int j) const
{
  return v[i];
}
