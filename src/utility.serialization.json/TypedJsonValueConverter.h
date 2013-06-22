#pragma once

#include <utility.serialization.json/JsonValueConverter.h>


namespace nspace{
  namespace core{
    namespace serialization{
      // class allows easier implementation of primitve type converters
      template<typename T>
      struct TypedJsonValueConverter : public JsonValueConverter{
        virtual bool canConvert(const Argument & argument)const override;
        virtual Json::Value convert(const Argument & value, SerializationContext & context)const override;
        void typedConvert(Json::Value & result, const T & value,SerializationContext &context)const;
      };
    }
  }
}

/// preprocessor directive for quick implementation
#define DS_TYPED_JSON_VALUE_CONVERTER_FOR(TYPE)\
  template<> void TypedJsonValueConverter<TYPE>::typedConvert(Json::Value & result, const TYPE & value,SerializationContext &context)const



/// implementation

namespace nspace{
  namespace core{
    namespace serialization{
      template<typename T>
      bool TypedJsonValueConverter<T>::canConvert(const Argument & argument)const  {return type_of<T>()==argument.type;}
      template<typename T>
      Json::Value TypedJsonValueConverter<T>::convert(const Argument & value, SerializationContext & context)const  {
        Json::Value result;
        typedConvert(result,value,context);
        return result;
      }
      template<typename T>
      void TypedJsonValueConverter<T>::typedConvert(Json::Value & result, const T & value,SerializationContext &context)const{ result=value;}

    }
  }
}