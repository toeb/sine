set(source

)


set(includeSource
  include/json/autolink.h
  include/json/config.h
  include/json/features.h
  include/json/forwards.h
  include/json/json.h
  include/json/reader.h
  include/json/value.h
  include/json/writer.h
)

set(src
json_batchallocator.h
json_internalarray.inl
json_internalmap.inl
json_reader.cpp
json_tool.h
json_value.cpp
json_valueiterator.inl
json_writer.cpp
)
include_directories(include)
set(source ${includeSource} ${src})
add_library(lib_json ${source})
