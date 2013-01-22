#include "PlyReader.h"

#include <utility.reader.h>



using namespace nspace;
using namespace std;



  struct PlyProperty{
    std::string name;
    std::string type;
    std::string indexType;
    std::string itemType;
  };

  struct PlyElement{
    std::vector<PlyProperty*> properties;
    std::string name;
    long instances;
  };
  struct PlyObject{
    std::vector<PlyElement*> elements;
    std::vector<std::string> info;
    std::vector<std::string> comments;

  };


void mapElement(PlyElement &  element, IMeshBuilder & builder, std::istream & stream){
  using namespace std;
  if(element.name=="vertex"){

    Vector3D position;
    for(auto property: element.properties){
      
     // stream >> value;
      if(property->name  =="x"){
        position(0)=parseNext<Real>(stream);
        continue;
      }
      if(property->name=="y"){
        position(1)=parseNext<Real>(stream);
        continue;
      }
      if(property->name=="z"){
        position(2)=parseNext<Real>(stream);
        continue;
      }

      std::string s;
      stream >>s;
      //stringtools::nextDouble(stream);

    }
    builder.position(move(position));
  }else if(element.name=="face"){
    unsigned int indexCount;
    parseNext(indexCount,stream);
   

    MeshFace face;
    face.reserve(indexCount);
    for(int faceIndex = 0; faceIndex < indexCount; faceIndex++){
      
      MeshFaceVertex faceVertex;
      faceVertex.position = parseNext<unsigned int>(stream)+1;             
      face.push_back(faceVertex);
    }
    builder.face(move(face));
  }
}

bool  PlyReader::readMesh(IMeshBuilder & builder){
  using namespace std;
  stringtools::StringToken token(stream());
  PlyObject * object=new PlyObject;
  token.next();
  if(token.word!="ply")return false;
  PlyElement * currentElement=0;
  while(token.next()){
    if(token.word=="")return false;
    if(token.word=="end_header")break;

    if(token.word=="element"){
      currentElement = new PlyElement();
      object->elements.push_back(currentElement);
      token.stream>>currentElement->name;
      token.stream>>currentElement->instances;
      token.next();
      if(token.word!="\n")return false;
    }

    if(token.word=="property"){
      if(!currentElement)return false;
      auto property = new PlyProperty();
      currentElement->properties.push_back(property);
      token.stream>>property->type;
      if(property->type=="list"){
        token.stream>>property->indexType>>property->itemType;
      }
      token.stream>>property->name;
      token.next();
      if(token.word!="\n")return false;
    }
  }

  reportProgress(token.stream.tellg());
  auto elementIterator= object->elements.begin();
  auto end =object->elements.end();
  builder.begin();
  while(elementIterator!=end){
    auto & element=**elementIterator;

    for(int i=0; i < element.instances;i++){
      mapElement(element,builder,token.stream);       
      token.next();
      if(i%1000==0)reportProgress(token.stream.tellg());
      if(token.word!="\n")return false;
    }

    elementIterator++;

    reportProgress(token.stream.tellg());
  }

  builder.end();
}

//what follows is a slew of ideas for parsing a ply file.... 
/*
void plyErrorCallback(p_ply ply, const char * message);
int plyReadCallback(p_ply_argument argument);
namespace nspace{
class PrivatePlyReader : public virtual Log{
private:
PlyReader & _reader;
public:
PrivatePlyReader(PlyReader & reader):_reader(reader){}
void plyError(const char * message){
logError(message);
}
int plyRead(p_ply_argument argument, PlyProperty * prop){
if(_reader.getCancel()){
return 0;
}
auto value = ply_get_argument_value(argument);
long index;
ply_get_argument_element(argument,0,&index);

prop->value(index,value);

return 1;
}

void readObjectInfo(p_ply ply,PlyObject & result){  
//iterate through all object info
if(_reader.getReadObjectInfo()){
const char * objectInfo=0;
while(objectInfo= ply_get_next_obj_info(ply,objectInfo)){
result.info.push_back(objectInfo);
}
}

}
void readComments(p_ply ply,PlyObject & result){
// iterate through all comments
if(_reader.getReadComments()){
const char* comment=0;
while(comment = ply_get_next_comment(ply,comment)){
result.comments.push_back(comment);
}
}
}

bool readMesh(IMeshBuilder & builder){
const char * fn = tmpnam(0);
ofstream outstream(fn);
char c;
while(_reader.stream()){
_reader.stream().get(c);
outstream<<c;
}
outstream.close();


logInfo("opening ply file '"<<fn<<"'");
p_ply ply = ply_open(fn,&plyErrorCallback,0,this);
if(!ply)return false;

// read the header which defines all contained elements of the ply file
auto success = ply_read_header(ply);
if(!success){
logError("could not read ply header");
return false;
}

// create a ply object and obtain a reference for convenience
_reader.setResult(std::shared_ptr<PlyObject>(new PlyObject()));
auto & result = *_reader.getResult();

readObjectInfo(ply,result);

readComments(ply,result);


//iterate all element definitions    
// declarations
p_ply_element element=0;
p_ply_property property=0;    
const char* name;
long instances;
while(element = ply_get_next_element(ply,element)){
success = ply_get_element_info(element,&name,&instances);
if(!success){
logError("could not read element info");
return false;
}
logInfo("'"<<fn<<"' has element: " << name<<" count: "<<instances);
// create a element
auto & plyElement = *new PlyElement(result,name,instances);


//iterate through elements properties
// declarations
property=0;
e_ply_type type,length_type,value_type;
while(property = ply_get_next_property(element,property)){
success = ply_get_property_info(property,&name,&type,&length_type,&value_type);
if(!success){
logError("could not read property info");
return false;          
}
logInfo("  element has "<< name << " "<< type<<" "<<length_type<<" "<<value_type);
//create the property
auto plyProperty =  new PlyProperty(name,plyElement);
if(!plyProperty)return false;
// set read callback
auto p=make_pointer(std::make_pair(this,plyProperty));
ply_set_read_cb(ply,plyProperty->element.name.c_str(),plyProperty->name.c_str(), &plyReadCallback,p,0);
}
}

ply_read(ply);      
ply_close(ply);


auto & obj = *_reader.getResult();

builder.begin();

auto & vertex = *obj["vertex"];

auto & x = *vertex["x"];
auto & y = *vertex["y"];
auto & z = *vertex["z"];

for(long i=0; i < vertex.instances; i++){
Vector3D position(x.values[i].second,y.values[i].second,z.values[i].second);
builder.position(move(position));

}

auto & faces = *obj["face"];

for(long i=0; i < faces.instances; i++){

}



builder.end();

return true;      
}
};
}




PlyElement::PlyElement(PlyObject & object, const std::string & name, long instances):object(object),name(name),instances(instances){
object[name]=std::shared_ptr<PlyElement>(this);
}


PlyProperty::PlyProperty(const std::string & name, PlyElement &  element):name(name),element(element){
element[name]=std::shared_ptr<PlyProperty>(this);
}
void PlyProperty::value(const Index i, double value){values.push_back(std::make_pair(i,value));};





PlyReader::PlyReader(){
reader=new PrivatePlyReader(*this);
setReadComments(true);
setReadObjectInfo(true);
setCancel(false);
}

PlyReader::~PlyReader(){
delete reader;
reader =0;
}
bool PlyReader::readMesh(IMeshBuilder &builder){
return reader->readMesh(builder);
}

void PlyReader::clearResult(){
getResult().reset();
}


PrivatePlyReader * plyGetReader(p_ply ply){
PrivatePlyReader* reader=0;  
ply_get_ply_user_data(ply,(void**)&reader,0);
return reader;
}
template<typename T>
T * plyUserData(p_ply_argument arg){
T * result = 0;
ply_get_argument_user_data(arg,(void**)&result,0);
return result;
}
void plyErrorCallback(p_ply ply, const char * message){
auto reader = plyGetReader(ply);
reader->plyError(message);

}
int plyReadCallback(p_ply_argument argument){
auto p= plyUserData<std::pair<PrivatePlyReader*,PlyProperty*> >(argument);
auto reader = p->first;
auto prop = p->second;
p=0;  
return reader->plyRead(argument,prop);
}

*/

/*



namespace ply2{

struct PlyFiniteStateMachine;

struct PlyState : public ExtendedFiniteState<PlyState,PlyToken&>{
TYPED_OBJECT(PlyState);
SIMPLE_PROPERTY(PlyFiniteStateMachine*, Machine){}
SIMPLE_PROPERTY(PlyObject *, Data){}
SIMPLE_PROPERTY(IMeshBuilder *, Builder){}
public:
PlyState():_Machine(0), _Data(0){}
virtual void registerTransitions(){}
template<typename T> T* state();
std::string token2str(const PlyToken token){
return token.word;
}
}; 

struct PlyFiniteStateMachine : public FiniteStateMachine<PlyState,PlyToken>, private Multiton<PlyState>{
PlyObject & data;
IMeshBuilder & builder;
PlyFiniteStateMachine(PlyObject & object, IMeshBuilder & builder);
template<typename T> T* state(){
return require<T>();
}
void onObjectRegistered(ObjectInstance instance){
instance->setMachine(this);
instance->setData(&data);
instance->setBuilder(&builder);
instance->registerTransitions();
}


};


template<typename T> T* PlyState::state(){
return getMachine()->state<T>();
}
namespace states{
struct ParsingComment:public PlyState{
TYPED_OBJECT(ParsingComment);
public:
ParsingComment():returnState(0){}
State* returnState;
void enter(State* previous){
this->returnState=previous;
}
void leave(State * next){
returnState=0;
}
State * transition(){
return returnState;
}
void consume(Token token){

}

};
struct ParsingHeader : public PlyState{      
TYPED_OBJECT(ParsingHeader);

void registerTransitions(){
registerTransition("comment", state<ParsingComment>());
}
};

struct ParsingProperty : public PlyState{
TYPED_OBJECT(ParsingProperty);
};
struct ParsingElement : public PlyState{
TYPED_OBJECT(ParsingElement);
void registerTransitions(){
registerTransition("property", state<ParsingProperty>());
}
void consume(Token token){

}
};

struct BadFile: public PlyState{
TYPED_OBJECT(BadFile);
};



struct Initial:public PlyState{
TYPED_OBJECT(Initial);

State* transition(Token token){
if(token.word=="ply"){
return state<ParsingHeader>();
}
return state<BadFile>();
}
};
}

PlyFiniteStateMachine::PlyFiniteStateMachine(PlyObject & object, IMeshBuilder & builder):FiniteStateMachine(new states::Initial()),data(object),builder(builder){
registerType(getInitialState());
}
}


struct PlyState  :
public HierarchicalStateMachine<PlyState,PlyToken&>,
private Multiton<PlyState>
{
TYPED_OBJECT(PlyState);
SIMPLE_PROPERTY(IMeshBuilder *, Builder){      
reset();
if(getInitialState())getInitialState()->setBuilder(newvalue);
}
SIMPLE_PROPERTY(PlyObject*, PlyObject){
reset();
if(getInitialState())getInitialState()->setPlyObject(newvalue);
};

public:


PlyState():_Builder(0){}
PlyState(PlyState *initialState):_Builder(0){
registerType(initialState);
setInitialState(initialState);            
setCurrentState(initialState);
}

void enter(State* predecessor){
if(!predecessor)return;
setBuilder(predecessor->getBuilder());
setPlyObject(predecessor->getPlyObject());
onStateEntered();
}
virtual void onStateEntered(){
}



protected:

// gets the singlton instances of state whjich is stored in parent --> toplevel container is only one state
template<typename T> PlyState * state(){
if(!getParentState())return 0;
return getParentState()->require<T>();
}
private:

void  onObjectRegistered(PlyState* state){
state->setParentState(this);
}

};
struct HeaderState;
struct CommentState :public PlyState{
TYPED_OBJECT(CommentState);

bool consume(TokenType token){
std::string line;
std::getline(token.stream,line);
getPlyObject()->comments.push_back(stringtools::trim(line));
return true;
}
State * transition(TokenType token);
};
struct ElementState : public PlyState{
bool consume(TokenType token){
auto & obj = *getPlyObject();
auto element =std::shared_ptr<PlyElement>(new PlyElement(obj));
token.stream>>element->name;
token.stream>>element->instances;
obj.elements.push_back(element);
return true;
}
};

struct PropertyState: public PlyState{

};

struct ListPropertyState{

};
struct PropertyState{

};
struct ReadVertexState: public PlyState{
TYPED_OBJECT(ReadVertexState);

};
struct ReadFaceState: public PlyState{
TYPED_OBJECT(ReadFaceState);

};
struct DataState: public PlyState{    
TYPED_OBJECT(DataState);
DataState():currentIndex(0){
}
long currentIndex;    


std::vector<std::shared_ptr<PlyElement> >::iterator iterator;
virtual void onStateEntered(){
iterator = getPlyObject()->elements.begin();

State * s=0;
if((*iterator)->name=="vertex"){
s = state<ReadVertexState>();
}
if((*iterator)->name=="face"){
s = state<ReadFaceState>();
}

setInitialState(s);

}

State* transition(TokenType token){      




if((*iterator)->name=="vertex"){
return state<ReadVertexState>();
}
if((*iterator)->name=="face"){
return state<ReadFaceState>();
}

if(token.word=="comment"){
return state<CommentState>();
}

}



bool consume(TokenType token){




if(token.word=="\n"){
currentLine++;
}






return true;
}
};
struct InitialHeaderState : public PlyState{
TYPED_OBJECT(InitialHeaderState);

State* transition(TokenType token){      
if(token.word=="element"){
return state<ElementState>();
}
if(token.word=="comment"){
return state<CommentState>();
}
}

};
struct HeaderState : public PlyState{
TYPED_OBJECT(HeaderState);
HeaderState():PlyState(new InitialHeaderState()){}
State* transition(TokenType token){
if(token.word=="end_header"){
return state<DataState>();
}
return this;
}
};


auto CommentState::transition(TokenType token)->State*{
return state<HeaderState>();
}
struct BadFileState : public PlyState{
TYPED_OBJECT(BadFileState);

};
struct PlyInitialState : public PlyState{
TYPED_OBJECT(PlyInitialState);
State * transition(TokenType token){
if(token.word=="ply"){
return state<HeaderState>();
}else{
return state<BadFileState>();
}
}


};
struct PlyStateMachine :public PlyState{    
PlyStateMachine():PlyState(new PlyInitialState()){}





};

*/



/*#pragma once

#include <utility.reader.mesh.h>
#include <map>

namespace nspace{
/*
struct PlyElement;

struct PlyObject:public std::map<std::string,std::shared_ptr<PlyElement> >{
std::vector<std::string> info;
std::vector<std::string> comments;
};

struct PlyProperty;
struct PlyElement:public std::map<std::string,std::shared_ptr<PlyProperty> >{
PlyObject & object;
std::string name;
long instances;
PlyElement(PlyObject & object, const std::string & name, long instances);
};


struct IPlyValue{

typedef size_t Index;
const Index index;
IPlyValue(const Index i):index(i){}
virtual void addValue(const double value)=0;
virtual const double value(const Index j=0)const=0;
virtual void setValue(const double value, const Index j=0)=0;  
virtual bool ready()const=0;
};

struct PlyReadCallback : public IPlyValue{
};

struct  PlyMeshBuilderCallback{
typedef size_t Index;
IMeshBuilder & builder;
virtual void addValue(const double d);
};

struct PlyMeshBuilderVertexCallback : public PlyMeshBuilderCallback{
};






template<typename T>
struct PlyValue :public IPlyValue{
PlyValue(const Index i):IPlyValue(i),ready(false),value(0.0){}
bool ready;
T value;
void addValue(const double value){
this->value = value;
ready=true;
}
const double value(const Index j=0)const{
return value;
}
void setValue(const double value,const Index j=0){
this->value = value;
ready  =true;
}
bool ready()const{
return ready;
}

};
template<typename IndexType=int, typename ValueType=double>
struct PlyList : public IPlyValue{
std::vector<ValueType> elements;
IndexType currentIndex;
int elementCount;
PlyList(const Index i):IPlyValue(i),currentIndex(-1){}
void addValue(const double value){
if(currentIndex < 0){
elementCount = (int)value;
elements.reserve(elementCount);
}else{
elements.push_back(value);
}
currentIndex++;
}
bool ready()const{
return elements.size()==elementCount;
}
const double value(const Index j=0)const{
return elements[j];
}
void setValue(const double value,const Index j=0){
elements[j] =value;
}  
};
struct PlyProperty {
const std::string name;
const std::string type;
PlyElement & element;  
std::vector<IPlyValue*> values;
PlyProperty(const std::string & name,const std::string &  type,PlyElement &  element):name(name),type(type),element(element){    
values.reserve(element.instances);
std::function<IPlyValue*(unsigned int i)> create;
if(type=="list"){
create=[](unsigned int i){return new PlyList<int,double>(i);};
}else{
create=[](unsigned int i){return new PlyValue<double>(i);};
}
for(unsigned int i=0; i < element.instances; i++){
values.push_back(create(i));
}
}
~PlyProperty(){
for(auto value : values){
delete value;
}

}
};



struct PlyCallback : Set<PlyProperty*>{
IMeshBuilder & builder;

PlyCallback(IMeshBuilder & builder):builder(builder){

};
bool addProperty(PlyProperty & property){
return add(&property);
}
void onElementAdded(PlyProperty* property){    
propertyReadyFlags[property]=false;
propertyValues[property] = std::vector<double>();
}
struct PlyPropertyValue{

};
Set<PlyProperty*> properties;  
std::map<PlyProperty*, PlyPropertyValue> propertyValues;

void addValue(PlyProperty & property, double value){
propertyValues[&property].push_back(value);
notifyIfReady();
}
void notifyIfReady(){
typedef std::vector<double> Vec;
if(properties.all([this](PlyProperty* property){ return propertyReadyFlags[property];})){

Vec vec;
properties.reduce(Vec(),[](Vec & 
ready( properties.reduce([this](PlyProperty* property, std::vector<double>& vec){vec.push_back(propertyValues[property]); return vec;}, std::vector<double>());
reset();    
}


}
void reset(){
properties.foreachElement([this](PlyProperty* property){
propertyReadyFlags[property]=false;
});
}

virtual void ready(std::vector<double> values){

}



};

class PrivatePlyReader;

class PlyReader : public MeshReader{
REFLECTABLE_OBJECT(PlyReader);
SUBCLASSOF(MeshReader);

PROPERTY(bool, ReadComments){}
PROPERTY(bool, ReadObjectInfo){}
PROPERTY(bool, Cancel){}
SIMPLE_PROPERTY(std::shared_ptr<PlyObject>, Result){}

friend class PrivatePlyReader;
PrivatePlyReader* reader;
public:
PlyReader();
~PlyReader();
protected:

void clearResult();
bool readMesh(IMeshBuilder & builder);
};


}*/