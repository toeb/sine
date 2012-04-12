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

#include "Quaternion.h"
#include "math.h"
#include "SimMath.h"

using namespace IBDS;

/** Standard-Konstruktor: erstellt ein Quaternion und setzt alle Werte auf 0.
  */
Quaternion::Quaternion()
{
	w = 0.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

/** Konstruktor: Erstellt ein Quaternion mit den übergebenen Werten.
  */
Quaternion::Quaternion(const Real pw, const Real px, const Real py, const Real pz)
{ 
	w = pw;
	x = px;
	y = py;
	z = pz;
}

/** Wandelt eine Drehung um den Winkel angle um die übergeben Achse
  * in ein Quaternion um. \n
  * Quaternion = (cos (angle/2), sin(angle/2) * axis)
  */
void Quaternion::setFromAxisAngle (const Vector3D &axis, const Real angle)
{
	Real a = 0.5 * angle;
	w = cos (a);

	Real sinus = sin (a);
	x = sinus * axis[0];
	y = sinus * axis[1];
	z = sinus * axis[2];
}

/** Gibt das Quaternion als Drehachse mit zugehörigen Drehwinkel zurück. 
  */
void Quaternion::getAxisAngle (Vector3D &axis, Real &angle)
{
  	Real l2 = x*x + y*y + z*z;
	if (l2 > SimMath::eps2)
    {
		if (w > 1.0)
			w = 1.0;
		else if (w < -1.0) 
			w = -1.0;
		angle = (Real) 2.0 * acos (w);
		Real l = sqrt (l2);
        axis[0] = x / l;
        axis[1] = y / l;
        axis[2] = z / l;
    }
    else
    {
        angle = 0.0;
        axis[0] = 1.0;
        axis[1] = 0.0;
        axis[2] = 0.0;
    }
}

/** Wandelt eine 3x3 Rotationsmatrix
  * in ein Quaternion um. \n
  * (Algorithmus: siehe Ken Shoemake (SIGGRAPH))
  */
void Quaternion::setFromMatrix3x3 (Matrix3x3 *m)
{
	Real tr = 1.0 + (*m)[0][0] + (*m)[1][1] + (*m)[2][2];
	Real s;

    if (tr > 1.0e-9)
    {
		s = sqrt (tr);
		w = 0.5*s;
		s = 0.5 /s;
        x = ((*m)[2][1] - (*m)[1][2]) * s;
        y = ((*m)[0][2] - (*m)[2][0]) * s;
		z = ((*m)[1][0] - (*m)[0][1]) * s;
    }
    else
    {
        int i = 0;
		if ((*m)[1][1] > (*m)[0][0])
			i = 1;
		if ((*m)[2][2] > (*m)[i][i])
			i = 2;
		
		switch (i)
		{
			case 0: 
					s = sqrt (((*m)[0][0] - ((*m)[1][1] + (*m)[2][2])) + 1);
					x = 0.5 * s;
					s = 0.5 / s;
					y = ((*m)[0][1] + (*m)[1][0]) * s;
					z = ((*m)[2][0] + (*m)[0][2]) * s;
					w = ((*m)[2][1] - (*m)[1][2]) * s;
					break;
			case 1:
					s = sqrt (((*m)[1][1] - ((*m)[2][2] + (*m)[0][0])) + 1);
					y = 0.5 * s;
					s = 0.5 / s;
					z = ((*m)[1][2] + (*m)[2][1]) * s;
					x = ((*m)[0][1] + (*m)[1][0]) * s;
					w = ((*m)[0][2] - (*m)[2][0]) * s;
					break;
			case 2:
					s = sqrt (((*m)[2][2] - ((*m)[0][0] + (*m)[1][1])) + 1);
					z = 0.5 * s;
					s = 0.5 / s;
					x= ((*m)[2][0] + (*m)[0][2]) * s;
					y = ((*m)[1][2] + (*m)[2][1]) * s;
					w = ((*m)[1][0] - (*m)[0][1]) * s;
					break;
		}
    }
}


/** Wandelt eine 3x3 Rotationsmatrix
  * in ein Quaternion um. Dabei wird die transponierte Matrix verwendet. \n
  * (Algorithmus: siehe Ken Shoemake (SIGGRAPH))
  */
void Quaternion::setFromMatrix3x3T (Matrix3x3 *m)
{
	Real tr = 1.0 + (*m)[0][0] + (*m)[1][1] + (*m)[2][2];
	Real s;

    if (tr > 1.0e-9)
    {
		s = sqrt (tr);
		w = 0.5*s;
		s = 0.5 /s;
        x = ((*m)[1][2] - (*m)[2][1]) * s;
        y = ((*m)[2][0] - (*m)[0][2]) * s;
		z = ((*m)[0][1] - (*m)[1][0]) * s;
    }
    else
    {
        int i = 0;
		if ((*m)[1][1] > (*m)[0][0])
			i = 1;
		if ((*m)[2][2] > (*m)[i][i])
			i = 2;
		
		switch (i)
		{
			case 0: 
					s = sqrt (((*m)[0][0] - ((*m)[1][1] + (*m)[2][2])) + 1);
					x = 0.5 * s;
					s = 0.5 / s;
					y = ((*m)[1][0] + (*m)[0][1]) * s;
					z = ((*m)[0][2] + (*m)[2][0]) * s;
					w = ((*m)[1][2] - (*m)[2][1]) * s;
					break;
			case 1:
					s = sqrt (((*m)[1][1] - ((*m)[2][2] + (*m)[0][0])) + 1);
					y = 0.5 * s;
					s = 0.5 / s;
					z = ((*m)[2][1] + (*m)[1][2]) * s;
					x = ((*m)[1][0] + (*m)[0][1]) * s;
					w = ((*m)[2][0] - (*m)[0][2]) * s;
					break;
			case 2:
					s = sqrt (((*m)[2][2] - ((*m)[0][0] + (*m)[1][1])) + 1);
					z = 0.5 * s;
					s = 0.5 / s;
					x= ((*m)[0][2] + (*m)[2][0]) * s;
					y = ((*m)[2][1] + (*m)[1][2]) * s;
					w = ((*m)[0][1] - (*m)[1][0]) * s;
					break;
		}
    }
}


/** Gibt das Quaternion als 3x3 Rotationsmatrix zurück. 
  */
void Quaternion::getMatrix3x3 (Matrix3x3 &m)
{
	Real xx = x*x;
	Real yy = y*y;
	Real zz = z*z;
	Real xy = x*y;
	Real wz = w*z;
	Real xz = x*z;
	Real wy = w*y;
	Real yz = y*z;
	Real wx = w*x;
	

	//m[0][0] = 1.0 - 2.0*(yy + zz);
	m[0][1] = 2.0*(xy-wz);
	m[0][2] = 2.0*(xz+wy);

	m[1][0] = 2.0*(xy+wz);
	//m[1][1] = 1.0 - 2.0*(xx+zz);
	m[1][2] = 2.0*(yz-wx);

	m[2][0] = 2.0*(xz-wy);
	m[2][1] = 2.0*(yz+wx);
	//m[2][2] = 1.0 - 2.0*(xx+yy);

	// [Besl, McKay 1992]
	Real ww = w*w;
	m[0][0] = ww+xx-yy-zz;
	m[1][1] = ww+yy-xx-zz;
	m[2][2] = ww+zz-xx-yy;
}

/** Gibt das Quaternion als transponierte 3x3 Rotationsmatrix zurück. 
  */
void Quaternion::getMatrix3x3T (Matrix3x3 &m)
{
	Real xx = x*x;
	Real yy = y*y;
	Real zz = z*z;
	Real xy = x*y;
	Real wz = w*z;
	Real xz = x*z;
	Real wy = w*y;
	Real yz = y*z;
	Real wx = w*x;
	

	//m[0][0] = 1.0 - 2.0*(yy + zz);
	m[1][0] = 2.0*(xy-wz);
	m[2][0] = 2.0*(xz+wy);

	m[0][1] = 2.0*(xy+wz);
	//m[1][1] = 1.0 - 2.0*(xx+zz);
	m[2][1] = 2.0*(yz-wx);

	m[0][2] = 2.0*(xz-wy);
	m[1][2] = 2.0*(yz+wx);
	//m[2][2] = 1.0 - 2.0*(xx+yy);

	// [Besl, McKay 1992]
	Real ww = w*w;
	m[0][0] = ww+xx-yy-zz;
	m[1][1] = ww+yy-xx-zz;
	m[2][2] = ww+zz-xx-yy;

}
	
/** Berechnet die Länge des Quaternions.
  */
Real Quaternion::length ()
{  
	return (Real) sqrt (x*x + y*y + z*z + w*w); 
}

/** Berechnet die Länge des Quaternions im Quadrat. 
  */ 
Real Quaternion::length2()
{  
	return x*x + y*y + z*z + w*w; 
}

/** Negation: -q\n
  * Negiert alle Elemente des Quaternions
  */
Quaternion IBDS::operator - (const Quaternion& a)
{ 
	return Quaternion(-a.w, -a.x, -a.y, -a.z); 
}

/** Addition: q1 + q2\n
  * Elementweise Addition von m1 mit m2
  */
Quaternion IBDS::operator + (const Quaternion& a, const Quaternion& b)
{ 
	return Quaternion(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z); 
}

/** Subtraktion: q1 - q2\n
  * Elementweise Subtraktion 
  */
Quaternion IBDS::operator - (const Quaternion& a, const Quaternion& b)
{ 
	return Quaternion(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z); 
}

/** Multiplikation: q1 * q2\n
  * Quaternionenmultiplikation: [w1, v1]*[w2,v2]= [w1*w2 - v1*v2, w1*v2 + w2*v1 + v1^v2] mit v={x,y,z}
  */
Quaternion IBDS::operator * (const Quaternion& a, const Quaternion& b) 
{
	Quaternion c = Quaternion ();

	c.w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z;
	c.x = b.w*a.x + a.w*b.x - b.y*a.z + a.y*b.z;
	c.y = b.w*a.y + a.w*b.y + b.x*a.z - a.x*b.z;
    c.z = -b.x*a.y + a.x*b.y + b.w*a.z + a.w*b.z;

	return c;
}

/** Multiplikation: v * q\n
  * Quaternionenmultiplikation: [0, v]*q
  */
Quaternion IBDS::operator | (const Vector3D& a, const Quaternion& b) 
{
	Quaternion c = Quaternion ();

	c.w = - a.v[0]*b.x - a.v[1]*b.y - a.v[2]*b.z;
	c.x = b.w*a.v[0] - b.y*a.v[2] + a.v[1]*b.z;
	c.y = b.w*a.v[1] + b.x*a.v[2] - a.v[0]*b.z;
    c.z = -b.x*a.v[1] + a.v[0]*b.y + b.w*a.v[2];

	return c;
}

/** Multiplikation: v * q\n
  * Quaternionenmultiplikation: [0, v]*q
  */
Quaternion IBDS::operator | (const Quaternion& a, const Vector3D& b) 
{
	Quaternion c = Quaternion ();

	c.w = - a.x*b.v[0] - a.y*b.v[1] - a.z*b.v[2];
	c.x = a.w*b.v[0] - b.v[1]*a.z + a.y*b.v[2];
	c.y = a.w*b.v[1] + b.v[0]*a.z - a.x*b.v[2];
    c.z = -b.v[0]*a.y + a.x*b.v[1] + a.w*b.v[2];

	return c;
}


/** Multiplikation: d*a\n
  * Elementweise Multiplikation eines Quaternions mit einer Zahl
  */
Quaternion IBDS::operator * (const Real d, const Quaternion& a)
{
	return Quaternion (d*a.w, d*a.x, d*a.y, d*a.z);
}

/** Zuweisung: q1 = q2\n
  * Kopiert die Werte von Quaternion q2 in Quaternion q1.
  */
Quaternion& Quaternion::operator = (const Quaternion& q)
{ 
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this; 
}


/** Stream-Ausgabe des Quaternions
  */
std::ostream& IBDS::operator << (std::ostream& s, Quaternion& q)
{ 
	return s << '(' << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ')';
}

/** Normalisiert das Quaternion. Wenn die Achse (x,y,z) eine Länge von mehr als 1 hat,
  * dann muss sie normalisiert werden und der Winkel w wird zu 0. Andernfalls wird
  * nur der Winkel neu berechnet.
  */
void Quaternion::normalize ()
{
	Real al = sqrt(x*x + y*y + z*z + w*w);
	x = x / al;
	y = y / al;
	z = z / al;
	w = w / al;
}

/** Gibt das konjugierte Quaternion zurück: (w, -x, -y, -z)
  */
Quaternion Quaternion::conjugate ()
{
	return Quaternion (w, -x, -y, -z);
}


