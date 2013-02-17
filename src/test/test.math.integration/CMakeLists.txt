set(source main.cpp tests.cpp)
add_executable(test.math.integration ${source})
target_link_libraries(test.math.integration core.testing math.integration)
