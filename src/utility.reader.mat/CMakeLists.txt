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

find_package(zlib)

include_directories(${ZLIB_INCLUDE_DIRS})
source_group("" FILES ${source})
add_library(utility.reader.mat ${source} CMakeLists.txt)



target_link_libraries(utility.reader.mat utility.reader math.matrix ${ZLIB_LIBRARIES})