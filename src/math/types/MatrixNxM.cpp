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

#include "MatrixNxM.h"
#include "Matrix2x3.h"
#include "Matrix3x2.h"
#include "math.h"

using namespace nspace;
MatrixNxM::MatrixNxM(){
  resize(0,0);

}
/** Standard-Konstruktor: erstellt die Einheitsmatrix
*/
MatrixNxM::MatrixNxM(const int r, const int c):_data(0),_rows(0),_cols(0)
{
  resize(r,c);
}

/** Copy-Konstruktor
  */
MatrixNxM::MatrixNxM (const MatrixNxM& copy):_data(0),_rows(0),_cols(0)
{
  resize(copy._rows, copy._cols);
  memcpy(_data,copy._data,size()*sizeof(Real));
	/*for (int i=0; i < _rows; i++)
	{
		for (int j=0; j < _cols; j++){
			value(i,j)=copy(i,j);
    }
	}*/
}

/** Destruktor
*/
MatrixNxM::~MatrixNxM ()
{ 
 ArrayPool<Real>::freeArray(&_data,size());
  _rows = 0;
	_cols = 0;
}


/** Negation: -m\n
* Negiert alle Elemente der Matrix
*/
MatrixNxM nspace::operator - (const MatrixNxM& a)
{ 
  MatrixNxM m = MatrixNxM(a._rows, a._cols);
  int  sz = a.size();
  for(int i=0; i < sz; i++){
    m._data[i]=-a._data[i];
  }
//   for (int i=0; i < a.rows(); i++){
//     for(int j=0; j < a.cols();j++){
//       m(i,j)=-a(i,j);
//     }
//   }
  return m; 
}

/** Addition: m1 + m2\n
* Elementweise Addition von m1 mit m2
*/
MatrixNxM nspace::operator + (const MatrixNxM& a, const MatrixNxM& b)
{ 
	MatrixNxM m = MatrixNxM(a._rows, a._cols);
  int  sz = a.size();
  for(int i=0; i < sz; i++){
    m._data[i]=a._data[i]+b._data[i];
  }
  /*
	for (int i=0; i < a.rows(); i++){
    for(int j=0; j < a.cols();j++){
      m(i,j)=a(i,j)+b(i,j);
    }
  }*/
  return m; 
}

/** Subtraktion: m1 - m2\n
* Elementweise Subtraktion 
*/
MatrixNxM nspace::operator - (const MatrixNxM& a, const MatrixNxM& b)
{ 
  MatrixNxM m = MatrixNxM(a._rows, a._cols);
  int  sz = a.size();
  for(int i=0; i < sz; i++){
    m._data[i]=a._data[i]-b._data[i];
  }
  /*
  for (int i=0; i < a.rows(); i++){
    for(int j=0; j < a.cols();j++){
      m(i,j)=a(i,j)-b(i,j);
    }
  }*/
  return m; 
}

/** Multiplikation: m1 * m2\n
* Matrixmultiplikation von m1 mit m2
*/
MatrixNxM nspace::operator * (const MatrixNxM& a, const MatrixNxM& b) 
{
	MatrixNxM c = MatrixNxM(a._rows, b._cols);
	for (int i=0; i < a._rows; i++)
	{
		for (int j=0; j < b._cols; j++)
		{
			Real & cij = c(i,j);
      cij= 0.0;
			for (int k=0; k < a._cols; k++)
				cij += a(i,k)*b(k,j);
		}
	}
	return c;
}


/** Multiplikation: d*a\n
* Elementweise Multiplikation einer Matrix mit einer Zahl
*/
MatrixNxM nspace::operator * (const Real d, const MatrixNxM& a)
{
	MatrixNxM m = MatrixNxM(a._rows, a._cols);
	int  sz = a.size();
  for(int i=0; i < sz; i++){
    m._data[i]=d*a._data[i];
  }
  return m;
  /*
  for (int i=0; i < a._rows; i++){
    for(int j=0; j < a._cols; j++){
		  m(i,j) = d*a(i,j);
    }
  }
	return m;
  */
}


/** Transponiert die NxM-Matrix 
*/
MatrixNxM MatrixNxM::transpose () const
{
	MatrixNxM m = MatrixNxM(_cols, _rows);
	for (int i=0; i < _rows; i++)
		for (int j=0; j < _cols; j++)
			m(j,i)= (*this)(i,j);
	return m;
}





/** Stream-Ausgabe der Matrix
  */
std::ostream& nspace::operator << (std::ostream& s, const MatrixNxM& m)
{ 
	for (int i=0; i < m.rows(); i++){
    for(int j = 0; j < m.cols(); j++){
      s << m(i,j);
    }
    s << std::endl;
  }
	return s;
}




/** Setzt alle Elemente auf Null. 
*/
void MatrixNxM::zero()
{
	for (int i=0; i < _rows; i++)
		for (int j=0; j < _cols; j++)
			value(i,j)= 0.0;
}

/** Zuweisung: m1 = m2\n
  * Kopiert die Werte von Matrix m2 in Matrix m1.
  */
MatrixNxM& MatrixNxM::operator = (const MatrixNxM& m)
{ 

  resize(m.rows(), m.cols());

  memcpy(_data,m._data,size()*sizeof(Real));
 /* for (int i=0; i < _rows; i++)
		for (int j=0; j < _cols; j++)
			value(i,j) = m(i,j);*/	
	return *this; 
}

/** Berechnet die Inverse einer Matrix nach Gauss-Jordan. 
  */
bool MatrixNxM::inverse () 
{
	int *colIndex = new int [_rows];
	int *rowIndex = new int [_rows];;
	bool *pivot = new bool [_rows];;

	memset (pivot, 0, _rows * sizeof(bool));

	for (int i = 0; i < _rows; i++) 
	{
		double maxVal = 0.0;
		int row = 0;
		int col = 0;
		bool chk = false;
		for (int j = 0; j < _rows; j++) 
		{
			if (!pivot[j]) 
			{
				for (int k = 0; k < _rows; k++) 
				{
					if (!pivot[k]) 
					{
						double val = fabs (value(j,k));
						if (val > maxVal) 
						{
							maxVal = val;
							row = j;
							col = k;
							chk = true;
						}
					}
				}
			}
		}
		if (!chk) 
			return false;

		pivot[col] = true;

		if (row != col) 
		{
			Real *ptr;
			ArrayPool<Real>::createArray(&ptr,cols());
			memcpy (ptr, &_data[row*cols()], cols() * sizeof (Real));
			memcpy (&_data[row*cols()], &_data[col*cols()], cols() * sizeof (Real));
			memcpy (&_data[col*cols()], ptr, cols() * sizeof(Real));
			ArrayPool<Real>::freeArray(&ptr,cols());
		}

		rowIndex[i] = row;
		colIndex[i] = col;

		double scale = 1.0 /value(col,col);
		value(col,col) = 1.0;
		for (int k = 0; k < _rows; k++)
			value(col,k) *= scale;

		for (int j = 0; j < _rows; j++) 
		{
			if (j != col) 
			{
				scale = value(j,col);
				value(j,col)= 0.0;
				for (int k = 0; k < _rows; k++ )
					value(j,k) -=value(col,k) * scale;
			}
		}
	}

	for (int j = _rows - 1; j >= 0; j--) 
	{
		if (rowIndex[j] != colIndex[j]) 
		{
			for (int k = 0; k < _rows; k++) 
			{
				double val =value(k,rowIndex[j]);
        value(k,rowIndex[j]) = value(k,colIndex[j]);
        value(k,colIndex[j]) = val;
			}
		}
	}

	delete [] colIndex;
	delete [] rowIndex;
	delete [] pivot;

	return true;
}
