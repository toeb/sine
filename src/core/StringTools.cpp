#include "StringTools.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;
using namespace nspace::stringtools;


std::string nspace::stringtools::trim(std::stringstream & stream){      
      std::stringstream result;
      char c;
      while(stream.get(c)){
        switch(c){
        case ' ':
        case '\t':
        case '\n':
        case '\r':
          continue;
        default:
          result<<c;
        };          
      }
      return result.str();
    }
    std::string nspace::stringtools::trim(const std::string & str){
      std::stringstream stream(str);
      return trim(stream);
    }
    bool nspace::stringtools::startsWith(const std::string & subject,const std::string & what){
      if(subject.size()<what.size())return false;
      int i=0;
      for(int i=0; i < what.size(); i++){
        if(what[i]!=subject[i])return false;
      };
      return true;
    }
    bool nspace::stringtools::startWithIgnoreCase(const std::string &subject, const std::string & what){
      auto s =toLowerCase(subject);
      auto w = toLowerCase(what);
      return startsWith(s,w);
    }


std::string nspace::stringtools::toLowerCase(const std::string & original){
  std::string data = original;
  std::transform(data.begin(), data.end(), data.begin(), ::tolower);
  return data;
}
std::string nspace::stringtools::toUpperCase(const std::string & original){
  std::string data = original;
  std::transform(data.begin(), data.end(), data.begin(), ::toupper);
  return data;
}

bool nspace::stringtools::contains(const std::string & original, const std::string & search){
  if( original.find(search) > original.size())return false;
  return true;
}
bool nspace::stringtools:: containsIgnoreCase(const std::string & original, const std::string & search){
  string ori = toLowerCase(original);
  string src = toLowerCase(search);
  if( ori.find(src) > ori.size())return false;
  return true;
}

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