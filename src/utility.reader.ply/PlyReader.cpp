#include "PlyReader.h"

#include <utility.reader.h>
#include <map>
#include <rply/rply.h>

using namespace nspace;
using namespace std;

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

    bool doRead(){
      const char * fn = "";
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

      auto vertices = result["vertex"].get();
      auto faces = result["face"].get();

      std::vector<double[3]> positions;

      for(int i=0; i < vertices->instances;i++){
        double pos[3];

      }

      ply_close(ply);
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


void PlyReader::clearResult(){
  getResult().reset();
}
bool PlyReader::doRead(){
  return reader->doRead();
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

