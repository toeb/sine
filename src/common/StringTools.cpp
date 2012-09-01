#include "StringTools.h"



using namespace std::extensions;

std::string std::extensions:: operator +(const std::string & a, const std::string & b){
  std::string result = "";
  result.append(a);
  result.append(b);
  return result;
}
std::string std::extensions:: operator +(std::string a, const char * b){
  return a+std::string(b);
}
std::string std::extensions::operator +(const char * a, std::string b){
  return std::string(a)+b;
}