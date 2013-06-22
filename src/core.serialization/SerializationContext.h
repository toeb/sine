#pragma once
#include <map>
#include <memory>
#include <core.reflection.h>
#include <core.task/ProgressReporter.h>
namespace nspace{

  namespace core{
    namespace serialization{
      // serialization context helps managing the serialization of an object graph
      //currently only by managing object identity
      class SerializationContext{
        reflect_type(SerializationContext);
        int idCounter;
        std::map<void*, int> pointerIds;
        typedef std::shared_ptr<ProgressReporter> reflect_property(ProgressReporter);

      public:
        void incrementTotalProgress(int count=1);
        void incrementProgress(int count=1);
        SerializationContext();
        // returns the id for a raw pointer and 0 if no id is assigned 
        int getId(void* ptr);
        // returns the id for a shared pointer and 0 if no id is assigned 
        int getId(std::shared_ptr<void> ptr);
        // returns the id for a raw pointer and if no id is assigned it will be created
        int requireId(void* ptr);
        // returns the id for a shared pointer and if no id is assigned it will be created
        int requireId(std::shared_ptr<void> ptr);
      };

    }
  }

}