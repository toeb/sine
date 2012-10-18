#include "StringTools.h"

#include <string>
#include <sstream>

using namespace nspace::stringtools;


std::string nspace::stringtools:: operator +(const std::string & a, const std::string & b){
  std::string result = "";
  result.append(a);
  result.append(b);
  return result;
}
std::string nspace::stringtools:: operator +(const std::string &a, const char * b){
  return a+std::string(b);
}
std::string nspace::stringtools::operator +(const char * a, const std::string &b){
  return std::string(a)+b;
}

std::string nspace::stringtools::repeat(const std::string &str, unsigned int n){
  std::stringstream ss;
  for(unsigned int i=0; i < n; i++){
      ss << str;
    }
  return ss.str();
}

std::string nspace::stringtools::replace(std::string  original, const std::string & search, const std::string & replacement){
  if( original.find(search) > original.size())return original;
  return  original.replace(original.find(search), replacement.size()-1, replacement);
}


std::string nspace::stringtools::spaces(unsigned int n){
  return repeat(" ",n);
}
