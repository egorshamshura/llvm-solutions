cmake_minimum_required(VERSION 3.21)
project(template)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(LLVM REQUIRED)
llvm_map_components_to_libnames(
  LLVM_LIBRARIES
  Core
  ExecutionEngine
  Interpreter
  MC
  MCJIT
  Support
  nativecodegen
)

file(GLOB SOLUTION_SRC src/*.cpp src/*.h src/instruction/*.cpp src/instruction/*.h src/cpu/*.cpp src/cpu/*.h src/lib/*.cpp src/lib/*.h src/parser/*.cpp src/parser/*.h)
file(GLOB TEST_SRC test/*.cpp test/*.h)

add_executable(tests ${TEST_SRC} ${SOLUTION_SRC})
target_link_libraries(tests PRIVATE ${SDL2_LIBRARIES} ${LLVM_LIBRARIES}) 
target_include_directories(tests PRIVATE src test ${SDL2_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS})