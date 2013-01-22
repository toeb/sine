/**
 * Copyright (C) 2013 Tobias P. Becker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the  rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * More information at: https://dslib.assembla.com/
 *
 */
#define IGNOREFILE
#ifndef IGNOREFILE
// to use matrix functionality include math.matrix.h
#include <math.matrix.h>

using namespace std;

// First of I will define two Matrix classes that are very simple.  maybe a bit too simple.

/**
* \brief Float 2x2 Matrix.
*/
struct float2x2{
  float a11; float a12;
  float a21; float a22;
};

/**
* \brief Float 2x1 Matrix
*/
struct float2x1{
  float a11; 
  float a21; 
};

// to enable access to these two matrix type alot of template specializations have to be declared
// however for basic types (ie types that do not need to be partially specialized) you
// can easily define all the template specializations via the DeclareMatrixType macro.
// 
// always be sure to declare the specializations in nspace.

namespace nspace{
  //                matrix type    index type  coefficient type  row count   column count
  DeclareMatrixType(float2x1,      int,        float,            return 2,   return 1){
    // code for accessing a reference to matrix at index (i,j)
    if(j!=0)throw "illegal column";
    if(i >1)throw "illegal row";
    if(i==0)return matrix.a11;
    return matrix.a21;
  }


  DeclareMatrixType(float2x2, int, float, return 2, return 2){
    int ij = i*2+j;
    switch(ij){
    case 0:return matrix.a11;
    case 1:return matrix.a12;
    case 2:return matrix.a21;
    case 3:return matrix.a22;
      default: throw "illegal index";
    }
  }


}

template<typename MatrixType>
void printMatrix(const MatrixType & matrix){
  for(int i=0; i < nspace::rows(matrix); i++){
    for(int j=0; j < nspace::cols(matrix); j++){
      // coefficient(matrix,i,j) returns the value or a reference to the matrix' (i,j)th coefficient
      cout << nspace::coefficient(matrix,i,j)<< " ";
    }
    cout <<endl;
  } 
}


/**
* \brief Reflects a matrix.  
*        this prints some information about the matrix to cout
*
* \tparam  typename MatrixType Type of the matrix.
* \param matrix  The matrix.
*/
template<typename MatrixType>
void reflectMatrix(const MatrixType & matrix){
  // isScalarMatrix returns information if the matrix is in fact just a scalar type
  cout << " is scalar: " << nspace::isScalarMatrix(matrix)<<endl;
  // rowTraits returns what traits the rows have (are they fixed size, unknown, dynamic sized or even infinite)
  nspace::DimensionTraits rowTraits = nspace::rowTraits(matrix);
  nspace::DimensionTraits columnTraits = nspace::columnTraits(matrix);

  if(rowTraits == nspace::Fixed || rowTraits == nspace::Dynamic){  
    //rows(matrix) returns the number of rows the matrix has
    cout << " row count: "<< nspace::rows(matrix)<<" "<< (rowTraits==nspace::Fixed?"(fixed)":"(dynamic)" ) << endl;
  }else{
    cout << " row count: "<< (rowTraits==nspace::Infinite?"(infinite)":"(unknown)")<<endl;
  }
  if(columnTraits == nspace::Fixed || columnTraits == nspace::Dynamic){  
    // cols(matrix) returns the number of cols the matrix has
    cout << " col count: "<< nspace::cols(matrix) <<" "<< (columnTraits==nspace::Fixed?"(fixed)":"(dynamic)") << endl;
  }else{
    cout << " col count: "<< (columnTraits==nspace::Infinite?"(infinite)":"(unknown)")<<endl;
  }

  cout << endl;
  cout << "coefficients:"<<endl;
 printMatrix(matrix);
  cout <<endl;
}

int main(){
  float2x2 myFirstCustomMatrix={2.0f,1.0f,-1.0f,3.0f};
  cout << "float2x2" <<endl;
  reflectMatrix(myFirstCustomMatrix);

  float2x1 mySecondCustomMatrix={2.0f, 323.0f};
  cout << "float2x1"<<endl;
  reflectMatrix(mySecondCustomMatrix);
  
  // now you can use the full range of actions on these matrices
  auto cosinusOfMatrix = nspace::elementWiseCosinus(mySecondCustomMatrix);
  printMatrix(cosinusOfMatrix);
  
  auto doubleOfMatrix = nspace::add(myFirstCustomMatrix,myFirstCustomMatrix);
  printMatrix(doubleOfMatrix);
  
  // there are some other types of matrices that are already specialized.  
  // e.g. 
  //  - Eigen matrices,
  //  - my own implementation 
  //  - std::vector s
  //  - as well as fixed/dynamic arrays 
  
  //the matrix N-ary operations are defined for any type combination
  // so one can, for example, assign any type of matrix to any other 
  // type.
  double arrayMatrix2x2[2][2];
  nspace::assignMatrix(arrayMatrix2x2,myFirstCustomMatrix);

  cout<< "two dimensional array"<<endl;
  printMatrix(arrayMatrix2x2);

  // or perform any type of operation...
  auto result = nspace::multiply(myFirstCustomMatrix,arrayMatrix2x2);
  cout <<"resulting matrix"<<endl;
  printMatrix(result);

  result = nspace::elementWiseCosinus(result);
  printMatrix(result);


  //... on multiple matices
  return 0;
}
#else

int main(){return 0;}

#endif
