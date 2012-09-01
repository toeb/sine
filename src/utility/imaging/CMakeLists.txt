set(imagingSource
	./Image.h
	./Image.cpp
	./ImageLoader.h
	./ImageLoader.cpp
)
set(pngSource
	./png/PngLoader.h
	./png/PngLoader.cpp
)

source_group("src" FILES imagingSource)
source_group("src\\png" FILES pngSource)
add_library(imaging ${imagingSource} ${pngSource} CMakeLists.txt)
target_link_libraries(imaging core lodepng math logging)
project_folder("visualization" imaging)