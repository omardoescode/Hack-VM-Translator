cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 23)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
project(translator LANGUAGES CXX)
set (SOURCES AssemblyMap.cpp Parser.cpp CodeWriter.cpp Translator.cpp)
set (HEADERS AssemblyMap.h Parser.h CodeWriter.h Translator.h)
set (TESTS Tests/Tester.h Tests/Tester.cpp Tests/AssemblyMapTests.h Tests/ParserTests.h Tests/CodeWriterTests.h Tests/TranslatorTests.h)

add_executable(translator main.cpp ${SOURCES} ${HEADERS})
add_executable(translator_tests Tests/main.cpp ${SOURCES} ${HEADERS} ${TESTS})

target_include_directories(translator PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(translator_tests PUBLIC ${PROJECT_SOURCE_DIR})
