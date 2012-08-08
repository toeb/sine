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
#include <math.h>


using namespace nspace;

;
nspace::
/** Standard-Konstruktor: erstellt ein Quaternion und setzt alle Werte auf 0.
  */
Quaternion::Quaternion()
{
	_w = 0.0;
	_x = 0.0;
	_y = 0.0;
	_z = 0.0;
}

/** Konstruktor: Erstellt ein Quaternion mit den übergebenen Werten.
  */
Quaternion::Quaternion(const Real pw, const Real px, const Real py, const Real pz)
{ 
	_w = pw;
  _x = px;
  _y = py;
  _z = pz;
}

/** Wandelt eine Drehung um den Winkel angle um die übergeben Achse
  * in ein Quaternion um. \n
  * Quaternion = (cos (angle/2), sin(angle/2) * axis)
  */
void Quaternion::setFromAxisAngle (const Vector3D &axis, const Real angle)
{
	Real a = 0.5 * angle;
	_w = cos (a);

	Real sinus = sin (a);
  _x = sinus * axis(0);
  _y = sinus * axis(1);
  _z = sinus * axis(2);
}

/** Gibt das Quaternion als Drehachse mit zugehörigen Drehwinkel zurück. 
  */
void Quaternion::getAxisAngle (Vector3D &axis, Real &angle)
{
  	Real l2 = _x*_x + _y*_y + _z*_z;
	if (l2 > EPSILON)
    {
		if (_w > 1.0)
			_w = 1.0;
		else if (_w < -1.0) 
			_w = -1.0;
		angle = (Real) 2.0 * acos (_w);
		Real l = sqrt (l2);
    axis(0) = _x / l;
    axis(1) = _y / l;
    axis(2) = _z / l;
    }
    else
    {
        angle = 0.0;
        axis(0) = 1.0;
        axis(1) = 0.0;
        axis(2) = 0.0;
    }
}

/** Wandelt eine 3x3 Rotationsmatrix
  * in ein Quaternion um. \n
  * (Algorithmus: siehe Ken Shoemake (SIGGRAPH))
  */
void Quaternion::setFromMatrix3x3 (const Matrix3x3  &m)
{
	Real tr = 1.0 + m(0,0) +m(1,1) + m(2,2);
	Real s;

    if (tr > 1.0e-9)
    {
		s = sqrt (tr);
		_w = 0.5*s;
		s = 0.5 /s;
        _x = (m(2,1) - m(1,2)) * s;
        _y = (m(0,2) -m(2,0)) * s;
		_z = (m(1,0) - m(0,1)) * s;
    }
    else
    {
        int i = 0;
		if (m(1,1) > m(0,0))
			i = 1;
		if (m(2,2) >m(i,i))
			i = 2;
		
		switch (i)
		{
			case 0: 
					s = sqrt (m(0,0)- (m(1,1) + m(2,2)) + 1);
					_x = 0.5 * s;
					s = 0.5 / s;
					_y = (m(0,1) + m(1,0)) * s;
					_z = (m(2,0) + m(0,2)) * s;
					_w = (m(2,1) - m(1,2)) * s;
					break;
			case 1:
					s = sqrt (m(1,1) - (m(2,2) + m(0,0)) + 1);
					_y = 0.5 * s;
					s = 0.5 / s;
          _z = (m(1,2) + m(2,1)) * s;
          _x = (m(0,1) + m(1,0)) * s;
          _w = (m(0,2) - m(2,0)) * s;
					break;
			case 2:
					s = sqrt (m(2,2) - (m(0,0) + m(1,1)) + 1);
					_z = 0.5 * s;
					s = 0.5 / s;
          _x =(m(2,0) + m(0,2)) * s;
          _y =(m(1,2) + m(2,1)) * s;
          _w =(m(1,0) - m(0,1)) * s;
					break;
		}
    }
}


/** Wandelt eine 3x3 Rotationsmatrix
  * in ein Quaternion um. Dabei wird die transponierte Matrix verwendet. \n
  * (Algorithmus: siehe Ken Shoemake (SIGGRAPH))
  */
void Quaternion::setFromMatrix3x3T (const Matrix3x3  &m)
{
  setFromMatrix3x3(m.transpose());
}
Quaternion zeroRot(1,0,0,0);
const Quaternion & Quaternion::ZeroRotation(){
  return *&zeroRot;
}
/** Gibt das Quaternion als 3x3 Rotationsmatrix zurück. 
  */
void Quaternion::getMatrix3x3 (Matrix3x3 &m)const
{
	Real xx = _x*_x;
	Real yy = _y*_y;
	Real zz = _z*_z;
	Real xy = _x*_y;
	Real wz = _w*_z;
	Real xz = _x*_z;
	Real wy = _w*_y;
	Real yz = _y*_z;
	Real wx = _w*_x;
	

	//m(0,0) = 1.0 - 2.0*(yy + zz);
	m(0,1) = 2.0*(xy-wz);
	m(0,2) = 2.0*(xz+wy);

	m(1,0) = 2.0*(xy+wz);
	//m(1,1) = 1.0 - 2.0*(xx+zz);
	m(1,2) = 2.0*(yz-wx);

	m(2,0) = 2.0*(xz-wy);
	m(2,1) = 2.0*(yz+wx);
	//m(2,2) = 1.0 - 2.0*(xx+yy);

	// (Besl, McKay 1992)
	Real ww = _w*_w;
	m(0,0) = ww+xx-yy-zz;
	m(1,1) = ww+yy-xx-zz;
	m(2,2) = ww+zz-xx-yy;
}
 Matrix3x3 Quaternion::getMatrix3x3T()const{
  Matrix3x3 RT;
  getMatrix3x3T(RT);
  return RT;
}
/** Gibt das Quaternion als transponierte 3x3 Rotationsmatrix zurück. 
  */
void Quaternion::getMatrix3x3T (Matrix3x3 &m)const
{
  getMatrix3x3(m);
  m.transposeInPlace();


}
	
/** Berechnet die Länge des Quaternions.
  */
Real Quaternion::length ()
{  
	return (Real) sqrt (_x*_x + _y*_y + _z*_z + _w*_w); 
}

/** Berechnet die Länge des Quaternions im Quadrat. 
  */ 
Real Quaternion::length2()
{  
	return _x*_x + _y*_y + _z*_z + _w*_w; 
}

/** Negation: -q\n
  * Negiert alle Elemente des Quaternions
  */
Quaternion nspace::operator - (const Quaternion& a)
{ 
	return Quaternion(-a._w, -a._x, -a._y, -a._z); 
}

/** Addition: q1 + q2\n
  * Elementweise Addition von m1 mit m2
  */
Quaternion nspace::operator + (const Quaternion& a, const Quaternion& b)
{ 
	return Quaternion(a._w + b._w, a._x + b._x, a._y + b._y, a._z + b._z); 
}

/** Subtraktion: q1 - q2\n
  * Elementweise Subtraktion 
  */
Quaternion nspace::operator - (const Quaternion& a, const Quaternion& b)
{ 
	return Quaternion(a._w - b._w, a._x - b._x, a._y - b._y, a._z - b._z); 
}

/** Multiplikation: q1 * q2\n
  * Quaternionenmultiplikation: [w1, v1]*[w2,v2]= [w1*w2 - v1*v2, w1*v2 + w2*v1 + v1^v2] mit v={x,y,z}
  */
Quaternion nspace::operator * (const Quaternion& a, const Quaternion& b) 
{
	Quaternion c = Quaternion ();

	c._w = a._w*b._w - a._x*b._x - a._y*b._y - a._z*b._z;
	c._x = b._w*a._x + a._w*b._x - b._y*a._z + a._y*b._z;
	c._y = b._w*a._y + a._w*b._y + b._x*a._z - a._x*b._z;
  c._z = -b._x*a._y + a._x*b._y + b._w*a._z + a._w*b._z;

	return c;
}

/** Multiplikation: v * q\n
  * Quaternionenmultiplikation: [0, v]*q
  */
Quaternion nspace::operator | (const Vector3D& a, const Quaternion& b) 
{
	Quaternion c = Quaternion ();

	c._w = - a.v[0]*b._x - a.v[1]*b._y - a.v[2]*b._z;
	c._x = b._w*a.v[0] - b._y*a.v[2] + a.v[1]*b._z;
	c._y = b._w*a.v[1] + b._x*a.v[2] - a.v[0]*b._z;
    c._z = -b._x*a.v[1] + a.v[0]*b._y + b._w*a.v[2];

	return c;
}

/** Multiplikation: v * q\n
  * Quaternionenmultiplikation: [0, v]*q
  */
Quaternion nspace::operator | (const Quaternion& a, const Vector3D& b) 
{
	Quaternion c = Quaternion ();

	c._w = - a._x*b.v[0] - a._y*b.v[1] - a._z*b.v[2];
	c._x = a._w*b.v[0] - b.v[1]*a._z + a._y*b.v[2];
	c._y = a._w*b.v[1] + b.v[0]*a._z - a._x*b.v[2];
    c._z = -b.v[0]*a._y + a._x*b.v[1] + a._w*b.v[2];

	return c;
}


/** Multiplikation: d*a\n
  * Elementweise Multiplikation eines Quaternions mit einer Zahl
  */
Quaternion nspace::operator * (const Real d, const Quaternion& a)
{
	return Quaternion (d*a._w, d*a._x, d*a._y, d*a._z);
}

/** Zuweisung: q1 = q2\n
  * Kopiert die Werte von Quaternion q2 in Quaternion q1.
  */
Quaternion& Quaternion::operator = (const Quaternion& q)
{ 
  _w = q._w;
  _x = q._x;
  _y = q._y;
  _z = q._z;
	return *this; 
}


/** Stream-Ausgabe des Quaternions
  */
std::ostream& nspace::operator << (std::ostream& s, Quaternion& q)
{ 
	return s << '(' << q._w << ", " << q._x << ", " << q._y << ", " << q._z << ')';
}

/** Normalisiert das Quaternion. Wenn die Achse (x,y,z) eine Länge von mehr als 1 hat,
  * dann muss sie normalisiert werden und der Winkel w wird zu 0. Andernfalls wird
  * nur der _winkel neu berechnet.
  */
void Quaternion::normalize ()
{
	Real al = sqrt(_x*_x + _y*_y + _z*_z + _w*_w);
	_x = _x / al;
	_y = _y / al;
	_z = _z / al;
	_w = _w / al;
}

/** Gibt das konjugierte Quaternion zurück: (w, -x, -y, -z)
  */
Quaternion Quaternion::conjugate ()const
{
	return Quaternion (_w, -_x, -_y, -_z);
}


