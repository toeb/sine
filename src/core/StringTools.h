#pragma once
#include <config.h>
#include <string>
#include <sstream>
namespace nspace{
  namespace stringtools{
    //concatenates to strings
    std::string operator +(const std::string & a, const std::string & b);
    // concatenates a string and a const char *
    std::string operator +(const std::string & a, const char * b);
    // concatenatesa a string and a const char*
    std::string operator +(const char * a, const std::string & b);
    // concatenates  astring and any type of reference using the << operator
    template<typename T> std::string operator +(const std::string & a, const T & t);
    // concatenates  astring and any type of reference using the << operator
    template<typename T> std::string operator +( const T & t,const std::string & a);
    bool contains(const std::string & original, const std::string & search);
    bool containsIgnoreCase(const std::string & original, const std::string & search);
    std::string toLowerCase(const std::string & original);
    std::string toUpperCase(const std::string & original);
    // replaces the search string in original with replacement string
    std::string replace(std::string original, const std::string & search, const std::string & replacement);
    // generates whitespaces
    std::string spaces(unsigned int n);
    // repeats str n times
    std::string repeat(const std::string & str, unsigned int n );
  }
}

//implementation

template<typename T> std::string nspace::stringtools::operator +(const std::string & a, const T & t){
  std::stringstream s;
  s<<a<<t;
  return s.str();
}

template<typename T> std::string nspace::stringtools::operator +( const T & t,const std::string & a){
  return a+t;
}
