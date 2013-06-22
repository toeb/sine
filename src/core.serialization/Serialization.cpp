#include "Serialization.h"

#include <core.serialization/Serializer.h>
#include <core.serialization/Deserializer.h>
using namespace std;
namespace nspace{
  namespace core{
    namespace serialization{

      typedef std::string SerializationFormat;      
      typedef std::shared_ptr<Serializer> SerializerType;
      typedef std::shared_ptr<Deserializer> DeserializerType;

      // returns true iff a serializer exists for the speceified format
      bool serializerExists(const SerializationFormat & format){
        return (bool)serializerFor(format);        
      }

      const std::vector<SerializerType> & serializers(){
        struct instances : public std::vector<SerializerType>{        
          instances(){
            auto type = type_of<Serializer>();
            type->successors().foreachElement([this](const Type* subclass){
              auto instance = subclass->call();
              auto castInstance = instance.cast<Serializer>();
              push_back(castInstance);
            });
          }
        };
        static instances instances;
        return instances;
      }

      //returns the serializer for the specified format
      SerializerType serializerFor(const SerializationFormat & format){
        for(auto it = std::begin(serializers()); it != std::end(serializers()); it++){
          if((*it)->getFormat()==format){
            return *it;
          }
        }
        return SerializerType();
      }
      // serializes the Argument into the output stream using the specified format
      bool serialize(std::ostream  & stream, const Argument & argument, const SerializationFormat  & format){
        auto serializer = serializerFor(format);
        if(!(bool)serializer)return false;
        return serializer->serialize(stream,argument);
      }
      bool serialize(const std::string & str, const Argument & argument, const SerializationFormat& format){
        stringstream stream(str);
        return serialize(stream,argument,format);
      }
      bool serializeToFile(const std::string & filename, const Argument & argument){
        throw new std::exception("not implemented");
        return false;
      }
      bool serializeToFile(const std::string & filename, const Argument & argument, const SerializationFormat & format){        
        std::ofstream stream(filename);
        if(!(bool)stream)return false;
        return serialize(stream,argument,format);
      }
      // returns true if a deserializer exists for the specified format
      bool deserializerExists(const SerializationFormat & format){
        return false;
      }

      const std::vector<DeserializerType> & deserializers(){
        struct instances : public std::vector<DeserializerType>{        
          instances(){
            auto type = type_of<Deserializer>();
            type->successors().foreachElement([this](const Type* subclass){
              auto instance = subclass->call();
              auto castInstance = instance.cast<Deserializer>();
              push_back(castInstance);
            });
          }
        };
        static instances instances;
        return instances;
      }
      // returns a serializer for the specified format 
      DeserializerType deserializerFor(const SerializationFormat & format){        
        for(auto it = std::begin(deserializers()); it != std::end(deserializers()); it++){
          if((*it)->getFormat()==format){
            return *it;
          }
        }
        return DeserializerType();
      }
      // deserializes an argument impling the type from the input data using the serialization format
      Argument deserialize(std::istream & stream,const SerializationFormat & format){
        throw new std::exception("not implemented");
        return Argument();
      }
      // deserializes a
      Argument deserialize(std::istream & stream, const Type * type, const SerializationFormat & format){
        auto deserializer = deserializerFor(format);
        if(!(bool)deserializer)return Argument();
        return deserializer->deserialize(stream,type);
      }
      // deserializes the string passed as first argument into an instance of type using the format
      Argument deserialize(const std::string & serialized, const Type * type, const SerializationFormat & format){
        stringstream stream(serialized);
        return deserialize(stream,type,format);
      }
      // deserializes a file and uses the filename / or content to imply the type
      Argument deserializeFromFile(const SerializationFormat & filename){
        throw new std::exception("not implemented");
        return Argument();
      }
      //deserializes a file into an Argument of type "type" and implies the serialized format
      Argument deserializeFromFile(const std::string & filename, const Type * type){
        throw new std::exception("not implemented");
        return Argument();
      }
      //deserializes a file into an Argument of type "type" and format format
      Argument deserializeFromFile(const std::string & filename, const Type * type, const SerializationFormat & format){
        ifstream stream(filename);
        if(!(bool)stream)return Argument();
        return deserialize(filename,type,format);
      }

    }
  }
}
