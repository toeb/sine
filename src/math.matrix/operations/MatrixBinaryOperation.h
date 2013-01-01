#pragma once

/**
 * \brief A macro that defines the methods for binary a matrix operation.
 *        define methods void OPNAME(c,a,b); C OPNAME(c,a,b) auto OPNAME(c,a,b)
 *
 * \param OPNAME  The operation name.
 */
#define BinaryMatrixOperation(OPNAME)\
  template<typename C, typename A, typename B> inline void OPNAME(C & c, const A & a, const B  & b);\
  template<typename C, typename A, typename B> inline C OPNAME(const A & a, const B & b){C c; OPNAME(c,a,b);return c;}\
  template<typename A, typename B> inline auto OPNAME(const A & a, const B & b) -> typename coefficientTypeOfType(typename returnType(typename A,typename B)){return OPNAME<typename coefficientTypeOfType(typename returnType(typename A,typename B)),A,B>(a,b);}

/**
 * \brief A macro that defines binary operation's implementation. 
 *        e.g. BinaryOperationImplementation(subtract){c=a-b;}
 *
 * \param OPNAME  The opname.
 */
#define BinaryOperationImplementation(OPNAME)template<typename C, typename A, typename B> void OPNAME(C & c, const A & a, const B  & b)
