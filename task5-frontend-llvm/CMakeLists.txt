cmake_minimum_required(VERSION 3.21)
project(template)

LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(LLVM REQUIRED)
find_package(GTest REQUIRED)

set(ANTLR4CPP_JAR_LOCATION ${PROJECT_SOURCE_DIR}/thirdparty/antlr/antlr-4.13.2-complete.jar)
include( ExternalAntlr4Cpp )
include_directories( ${ANTLR4CPP_INCLUDE_DIRS} )
link_directories( ${ANTLR4CPP_LIBS} )
message(STATUS "Found antlr4cpp libs: ${ANTLR4_LIB_DIR} and includes: ${ANTLR4_INCLUDE_DIR} ")

# Call macro to add lexer and grammar to your build dependencies.
antlr4cpp_process_grammar(demo hw5
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/SimpleLangLexer.g4
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar/SimpleLangParser.g4)
# include generated files in project environment
include_directories(${antlr4cpp_include_dirs_hw5})

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

file(GLOB SOLUTION_SRC 
src/*.cpp src/*.h 
src/lib/*.cpp src/lib/*.h 
src/visitor/*.cpp src/visitor/*.h)

file(GLOB TEST_SRC test/test_grammar/*.cpp)
add_executable(tests ${TEST_SRC} ${SOLUTION_SRC} ${antlr4cpp_src_files_hw5})
add_dependencies(tests antlr4cpp antlr4cpp_generation_hw5)
target_link_libraries(tests PRIVATE ${SDL2_LIBRARIES} ${LLVM_LIBRARIES} antlr4-runtime GTest::gtest GTest::gtest_main) 
target_include_directories(tests PRIVATE src test ${SDL2_INCLUDE_DIRS} ${LLVM_INCLUDE_DIRS})