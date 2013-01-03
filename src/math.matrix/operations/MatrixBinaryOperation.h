#pragma once


#define NamedCoefficientAliasForType(TYPE, ALIAS) typedef typename coefficientTypeOfType(TYPE) ALIAS;
#define NamedCoefficientAliasForInstance(INSTANCE,ALIAS) NamedCoefficientAliasForType(typename decltype(INSTANCE), ALIAS);
#define NamedIndexAliasForType(TYPE, ALIAS)  typedef typename indexTypeOfType(TYPE) ALIAS;
#define NamedIndexAliasForInstance(INSTANCE,ALIAS) NamedIndexAliasForType(typename decltype(INSTANCE),ALIAS);
#define IndexAliasForType(TYPE) NamedIndexAliasForType(TYPE, Index)
#define IndexAliasForInstance(INSTANCE) NamedIndexAliasForInstance(INSTANCE, Index)
#define CoefficientAliasForType(TYPE) NamedCoefficientAliasForType(TYPE,Coefficient)
#define CoefficientAliasForInstance(INSTANCE) NamedCoefficientAliasForInstance(INSTANCE,Coefficient)
#define CoefficientAndIndexAliasForType(TYPE) IndexAliasForType(TYPE) CoefficientAliasForType(TYPE)
#define CoefficientAndIndexAliasForInstance(INSTANCE) IndexAliasForInstance(TYPE) CoefficientAliasForInstance(TYPE)


#define IndexArgument(MATRIXTYPE) const typename indexTypeOfType(MATRIXTYPE) &

#define matrixForEachRow(MATRIX)\
  NamedIndexAliasForInstance(MATRIX,RowIndex)\
  RowIndex rowCount = rows(MATRIX);\
  for(RowIndex i =0; i < rowCount; i++)

#define matrixForEachColumn(MATRIX)\
  NamedIndexAliasForInstance(MATRIX,ColIndex)\
  ColIndex colCount = cols(MATRIX);\
  for(ColIndex j = 0; j < colCount; j++)

#define matrixForEach(MATRIX)\
  IndexAliasForInstance(MATRIX);\
  Index rowCount= rows(MATRIX);\
  Index colCount= cols(MATRIX);\
  for(Index i = 0; i < rowCount; i++)\
    for(Index j =0; j < colCount; j++)

/**
 * \brief A macro that defines binary matrix operations with a return type other than returnType(A,B)
 *        the methods will be called <OPNAME>
 *        @TODO: Not every implementation should have an InPlace method.
 *
 * \param OPNAME      The operations name. 
 * \param RETURNTYPE  The return type.
 */
#define BinaryMatrixOperationOtherReturnType(OPNAME,RETURNTYPE)\
  template<typename C, typename A, typename B> inline void OPNAME(C & c, const A & a, const B  & b);\
  template<typename C, typename A, typename B> inline C OPNAME(const A & a, const B & b){C c; OPNAME(c,a,b);return c;}\
  template<typename A, typename B> inline auto OPNAME(const A & a, const B & b) -> typename RETURNTYPE{return OPNAME<typename RETURNTYPE,A,B>(a,b);}\
  template<typename A, typename B> inline void OPNAME##InPlace(A & a,const B&b){OPNAME(a,a,b);}


#define UnaryMatrixOperationOtherReturnType(OPNAME,RETURNTYPE)\
  template<typename A,typename B> inline void OPNAME(B & b, const A & a);\
  template<typename A,typename B> inline B OPNAME(const A & a){B b; OPNAME(b,a); return b;}\
  template<typename A> inline auto OPNAME(const A & a)->typename RETURNTYPE{return OPNAME<typename RETURNTYPE,A,B>(a);}\
  template<typename A> inline void OPNAME##InPlace(A & a){OPNAME(a,a);}

#define NullaryMatrixOperation(OPNAME)\
  template<typename A> inline void OPNAME(A&a);\
  template<typename A> inline A OPNAME(){A a; OPNAME(a); return a;}

#define NullaryOperationImplementation(OPNAME) template<typename A> inline void OPNAME(A&a)

#define MatrixOperation(NAME) OperationMatrix##NAME
#define MatrixOperationClass(NAME) class MatrixOperation(NAME)
#define MatrixOperationMethod public: static inline void operation


/**
 * \brief A macro that defines the methods for binary a matrix operation.
 *        define methods void OPNAME(c,a,b); C OPNAME(c,a,b) auto OPNAME(c,a,b)
 *
 * \param OPNAME  The operation name.
 */
#define BinaryMatrixOperation(OPNAME) BinaryMatrixOperationOtherReturnType(OPNAME,returnType(A,B))

/**
 * \brief A macro that defines binary operation's implementation. 
 *        e.g. BinaryOperationImplementation(subtract){c=a-b;}
 *
 * \param OPNAME  The opname.
 */
#define BinaryOperationImplementation(OPNAME)template<typename C, typename A, typename B> void OPNAME(C & c, const A & a, const B  & b)


#define UnaryMatrixOperation(OPNAME) UnaryMatrixOperationOtherReturnType(OPNAME,A)

#define UnaryOperationImplementation(OPNAME)template<typename A,typename B> void OPNAME(B & b, const A & a)