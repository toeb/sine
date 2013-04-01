set(source 
MatReader.h
MatReader.cpp
MatFile.h
MatFile.cpp
MatCompressedElement.h
MatCompressedElement.cpp
MatElement.h
MatElement.cpp
MatMatrixElement.h
MatMatrixElement.cpp
MatPrimitiveElement.h
MatPrimitiveElement.cpp
MatElementFactory.h
MatElementFactory.cpp
MatElementHeader.h
MatElementHeader.cpp
MatUtilities.h
MatUtilities.cpp
 ../include/utility.reader.mat.h
)

# zlib is needed to decompress matrix data.
find_package(zlib)
if(ZLIB_FOUND)
add_definitions(-DUTILITY_READER_MAT_ZLIB)
else(ZLIB_FOUND)
message("  utility.reader.mat will not be able to decode compressed matlab datatypes because zlib is missing")
endif(ZLIB_FOUND)

include_directories(${ZLIB_INCLUDE_DIRS})
source_group("" FILES ${source})
add_library(utility.reader.mat ${source} CMakeLists.txt)
target_link_libraries(utility.reader.mat utility.reader math.matrix ${ZLIB_LIBRARIES})
