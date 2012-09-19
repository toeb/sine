SET(source
./Textiles/TextileModel.h
./Textiles/TextileModel.cpp
./Textiles/TextileAlgorithm.h
./Textiles/TextileAlgorithm.cpp
)
set(simulationSource ${simulationSource} ${source}  )
source_group("simulation\\textiles" FILES ${source})
