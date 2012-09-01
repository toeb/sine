#include "ModelReader.h"

#include <fstream>

using namespace std;
using namespace mbslib;


string ModelReader::readToEnd(istream & instream)const{
  istreambuf_iterator<char> eos;
  string s(std::istreambuf_iterator<char>(instream), eos);  
  return s;
}

bool ModelReader::parseFile(IModelBuilder & builder, const string & filename){
  ifstream s;
  s.open(filename.c_str());
  if(!s){
    cerr << "ModelReader could not open file " << filename << endl;
    return false;
  }
  bool result = parse(builder,s);
  if(!result) cerr << "ModelReader::parseFile:  Could not parse file "<<filename<<endl;
  s.close();
  return result;
}
bool ModelReader::parseString(IModelBuilder & builder, const string &text){
  stringstream s(text);
  bool result = parse(builder,s);
  if(!result) cerr << "ModelReader::parseString could not parse \""<<text<<"\""<<endl;
  return result;
}
