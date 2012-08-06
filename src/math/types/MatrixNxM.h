/*
 * nspace - Impulse-Based Dynamic Simulation Library
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
#pragma once

#include <common/Config.h>
#include <math/types/Matrix.h>
#include <math/types/VectorND.h>
#include <common/patterns/ArrayPool.h>

namespace nspace
{
  template<typename T, int RowCount, int ColumnCount>
  class StaticMatrix : public Matrix<T>{
  protected:
    T _data[RowCount*ColumnCount];
    inline Real & value(int i, int j){
      return _data[index(i,j)];
    }
    inline const Real & value(int i, int j)const{
      return _data[index(i,j)];
    }
  public:
    //rule of three
    StaticMatrix(const StaticMatrix<T,RowCount,ColumnCount> & orig){
      *this=orig;
    }
    StaticMatrix<T,RowCount,ColumnCount> & operator=(const StaticMatrix<T,RowCount,ColumnCount> & orig ){
      memcpy(data(),orig.data(),dataByteSize());
        return *this;
    }
    StaticMatrix(){}
    ~StaticMatrix(){}
    inline size_t dataByteSize()const{
      return RowCount*ColumnCount*sizeof(T);
    }
    inline int index(int i, int j)const{return i* ColumnCount+j;}
    inline T & operator()(int i, int j){return _data[index(i,j)]; }
    inline const T & operator()(int i, int j)const{return _data[index(i,j)]; }
    inline int rows()const{return RowCount;}
    inline int cols()const{return ColumnCount;}
    T * data(){return &_data[0];}
    const T * data()const{return &_data[0];}    
  };


  template<typename T>
  class DynamicMatrix  : public Matrix<T>{
  protected:
    T * _data;
    int _rows;
    int _cols;
    inline Real & value(int i, int j){
      return _data[index(i,j)];
    }
    inline const Real & value(int i, int j)const{
      return _data[index(i,j)];
    }
  public:

    DynamicMatrix(const DynamicMatrix<T> & orig):_data(0),_rows(0),_cols(0){
      resize(orig.rows(),orig.cols(),false);
      memcpy(data(),orig.data(),dataByteSize());
    }

    ~DynamicMatrix(){
      ArrayPool<T>::freeArray(&_data,size());
      _rows = 0;
      _cols = 0;
    }
    DynamicMatrix():_rows(0),_cols(0),_data(0){resize(0,0);};
    inline size_t dataByteSize()const{
      return _rows*_cols*sizeof(T);
    }
    DynamicMatrix<T> & operator=(const DynamicMatrix<T> & orig ){
      memcpy(data(),orig.data(),dataByteSize());
      return *this;
    }
    void resize(int n, int m, bool setToZero=true){
      if(_rows==n && _cols==m)return;

      ArrayPool<T>::freeArray(&_data,size());
      _rows = n;
      _cols=m;
      ArrayPool<T>::createArray(&_data,size());

      _rows = n;
      _cols =m;
      if(setToZero) memset(_data,0,dataByteSize());
    }
  inline int index(int i, int j)const{return i* _cols+j;}
  inline T & operator()(int i, int j){return _data[i* _cols+j]; }
  inline const T & operator()(int i, int j)const{return _data[i* _cols+j]; }

  inline int rows()const{return _rows;}
  inline int cols()const{return _cols;}
  T * data(){return _data;}
  const T * data()const{return _data;}
  };
  
	/** MatrixNxM ist eine Klasse für Berechnungen mit einer nxm Matrix, wie z.B. Addition, Multiplikation,...
	  \author Jan Bender
	  */
	class MatrixNxM : public DynamicMatrix<Real>
	{
  private:
//     Real * _data;
//     /** Zeilenvektoren der 2x2 Matrix */
// 
//     /* Anzahl Zeilen */
//     int _rows;
//     /* Anzahl Spalten */
//     int _cols;

	public:
    inline int size()const{return _rows*_cols;}
    void setZero(){
      memset(_data,0,sizeof(Real)*size());
      /*for(int i=0; i < rows(); i++){
        for(int j=0; j < cols(); j++){
          value(i,j)=0.0;
        }
      }*/
    }
    

    //returns the frobenius norm
    Real norm(){

      Real sum=0;
      for(int i=0;i<_rows;i++){
        for(int j=0; j < _cols; j++){
          sum+=value(i,j)*value(i,j);
        }
      }
      return sqrt(sum);
    }
	public:
    MatrixNxM(){}    
    MatrixNxM(const int rows, const int cols);
// 		MatrixNxM (const MatrixNxM& copy);
// 		~MatrixNxM();

		friend MatrixNxM operator - (const MatrixNxM& a);						// -m1
		friend MatrixNxM operator + (const MatrixNxM& a, const MatrixNxM& b);	// m1 + m2
		friend MatrixNxM operator - (const MatrixNxM& a, const MatrixNxM& b);	// m1 - m2
		friend MatrixNxM operator * (const MatrixNxM& a, const MatrixNxM& b);	// a * b
		friend MatrixNxM operator * (const Real d, const MatrixNxM& a);		// d * a
    friend MatrixNxM operator * (const MatrixNxM & a, const Real d){return d*a;}
    friend MatrixNxM operator / (const MatrixNxM & a, const Real d){return (1.0/d)*a;}
		MatrixNxM& operator = (const MatrixNxM& m);

		friend VectorND operator * (const VectorND& v, const MatrixNxM& m);
    
    
		VectorND& operator [] ( int i);							// Zugriff per Index
		const VectorND& operator [] ( int i) const;
		

		friend std::ostream& operator << (std::ostream& s, const MatrixNxM& m);	// Streamausgabe



		MatrixNxM transpose() const;									
		void zero ();
		bool inverse ();

		friend class VectorND;
	};
}




