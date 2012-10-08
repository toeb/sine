set(imagingSource
	./Image.h
	./Image.cpp
	./ImageLoader.h
	./ImageLoader.cpp
	./Pixel.h
	./Pixel.cpp
)
set(pngSource
	./png/PngLoader.h
	./png/PngLoader.cpp
)

source_group("src" FILES imagingSource)
source_group("src\\png" FILES pngSource)
add_library(utility.imaging ${imagingSource} ${pngSource} CMakeLists.txt)
target_link_libraries(utility.imaging simulation lodepng math simulation.logging)