#include "MtlReader.h"

#include <visualization/Color.h>
#include <visualization/Material.h>

#include <fstream>
using namespace std;
using namespace nspace;

void MtlReader::parseNewMaterial(std::istream &stream){    
  if(!currentMaterial)currentMaterial=std::shared_ptr<Material>(new Material());    
  _materials.push_back(currentMaterial);
  std::string name;
  std::getline(stream,name);
  name=stringtools::trim(name);
  currentMaterial->setMaterialName(name);
}

Color MtlReader::parseColor(std::istream & stream){
  Color c;
  deserialize(c,stream);
  return c;

}


void MtlReader::parseSpecular(std::istream & stream){    
  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  currentMaterial->setSpecular(parseColor(stream));
}
void MtlReader::parseDiffuse(std::istream & stream){

  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  currentMaterial->setDiffuse(parseColor(stream));
}
void MtlReader:: parseAmbient(std::istream & stream){

  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  currentMaterial->setAmbient(parseColor(stream));
}

void MtlReader::parseIlluminationModel(std::istream & stream){
  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  int model;    
  stream >> model;
  if(model<0||model>10)return;
  currentMaterial->setModel((IlluminationModel)model);

}
void MtlReader::parseShininess(std::istream & stream){
  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  Real shininess;
  stream >> shininess;
  currentMaterial->setShininess(shininess);
}
void MtlReader::parseSharpness(std::istream  &stream){
  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  Real sharpness;
  stream>>sharpness;
  logInfo("sharpness is not supported - ignoring");
}
void MtlReader::parseRefractionIndex(std::istream & stream){
  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  Real refractionIndex;
  stream >> refractionIndex;
  if(clamp(refractionIndex,0.001,10.0)){
    logWarning("refraction index was clamped to "<<refractionIndex);
  }

}
void MtlReader::parseDissolve(std::istream & stream){
  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  Real dissolve;
  std::string line ;
  getline(stream,line);

  line = stringtools::trim(line);
  if(stringtools::startsWith(line, "-halo")){
    logInfo("no halo for dissolve possible - ignoring");
    return;
  }
  std::stringstream numberStream(line.substr(0,5));
  //1.0 is opaque and 0.0 is transparent
  stream >> dissolve;

  bool wasClamped =clamp(dissolve,0.0,1.0);
  if(wasClamped)logWarning("dissolve factor was clamped to unit interval");
  currentMaterial->setTransparency(dissolve);
}
void MtlReader::parseTransmissionFilter(std::istream & stream){
  if(!currentMaterial){
    logWarning("no material");
    return;
  }
  Color transmissionFilter = parseColor(stream);

}


MtlReader:: MtlReader():currentMaterial(0){
  parsers["newmtl"] = [this](std::istream & stream){parseNewMaterial(stream);};
  parsers["Ka"] = [this](std::istream & stream){parseAmbient(stream);};
  parsers["Kd"] = [this](std::istream & stream){parseDiffuse(stream);};
  parsers["Ks"] = [this](std::istream & stream){parseSpecular(stream);};
  parsers["Tf"] = [this](std::istream & stream){parseTransmissionFilter(stream);};
  parsers["illum"] = [this](std::istream & stream){parseIlluminationModel(stream);};
  parsers["d"] = [this](std::istream & stream){parseDissolve(stream);};
  parsers["sharpness"] = [this](std::istream & stream){parseSharpness(stream);};
  parsers["Ns"] = [this](std::istream & stream){parseShininess(stream);};
  parsers["Ni"] = [this](std::istream & stream){parseRefractionIndex(stream);};

}
const std::vector<std::shared_ptr<Material> > & MtlReader::Materials(){
  return _materials; 
};
bool MtlReader::doRead(){
  parseLineWise(stream(),parsers,Abort());
  return true;
}