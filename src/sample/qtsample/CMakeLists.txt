add_executable(qtsample main.cpp)
target_link_libraries(qtsample qtrunner simulationUtilities glrenderers dynamics force geometry urdf multibody math)
project_folder("samples" qtsample )
