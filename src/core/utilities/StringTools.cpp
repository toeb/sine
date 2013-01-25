#include "StringTools.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
using namespace std;
using namespace nspace::stringtools;

StringToken::StringToken(std::istream & stream):stream(stream){}
bool StringToken::next(){
  word=stringtools::nextToken(stream);      
  if(word=="")return false;
  return true;
}
StringToken:: operator bool(){
  return stream.good();
}

string nspace::stringtools::nextToken(std::istream & stream){
  static string newline="\n";
  static string empty="";
      bool stop=false;
      while(!stop){
        char c = stream.peek();
        switch(c){        
        case '\n':      
        case '\r':
          stream.ignore();
          return newline;
        case '\t':  
        case ' ':        
          stream.ignore();
          if(!stream)return empty;
          break;
        default:
          stop = true;
          break;
        };
      }
      string tok;
      stream >> tok;
      return tok;

    }

std::vector<std::string> nspace::stringtools::split(const std::string & str, const char separator){  
  std::vector<std::string> result;
  std::stringstream stream(str);
  std::string item;
  while(getline(stream,item,separator)){
    result.push_back(item);
  }
  return result;
}
std::vector<std::string> nspace::stringtools::split(istringstream & stream){  
  vector<string> tokens;
  copy(istream_iterator<string>(stream),
         istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));
  return tokens;
}
std::vector<std::string> nspace::stringtools::split(const std::string & str){
  istringstream stream(str);
  return split(stream);
}
std::string nspace::stringtools::trim(std::stringstream & stream){      
  return trim(stream.str());

}


std::string nspace::stringtools::trimFront(const std::string & str){
  int front=0;  
  bool isWhitespace;  
  bool allWhitespace=true;
  do{
    isWhitespace=false;
    switch(str[front]){
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        isWhitespace=true;
        
    break;
      default:
        allWhitespace = false;
    } 
    
    front++;
  }
  while(isWhitespace && front < str.size());
  if(allWhitespace)return "";
  return str.substr(front-1);
}


std::string nspace::stringtools::trimBack(const std::string & str){
  
  int back=str.size()-1;
  if(back < 0)return "";
  bool isWhitespace; 
  
  bool allWhitespace=true;
  do{
    isWhitespace=false;
    switch(str[back]){
    case ' ':
    case '\t':
    case '\n':
    case '\r':
    isWhitespace=true;
    break;
    default:
      allWhitespace = false;
    } 

    back--;
  }while(isWhitespace && back >=0); 
  
  if(allWhitespace)return "";
  return str.substr(0,back+2);
}

std::string nspace::stringtools::trim(const std::string & str){
  return trimFront(trimBack(str));

}
bool nspace::stringtools::startsWith(const std::string & subject,const std::string & what){
  if(subject.size()<what.size())return false; 
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

