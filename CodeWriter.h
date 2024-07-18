#pragma once
#include "AssemblyMap.h"
#include "Parser.h"
#include <fstream>
#include <string>
class CodeWriter {
public:
    CodeWriter (std::filesystem::path path, AssemblyMap asmMap);

    void setParser (Parser newParser);

    void write ();

    void close ();

private:
    void writeArithmetic ();
    void writePush ();
    void writePop ();
    void writeFormatted (std::string asmKey, std::string arg);

private:
    std::ofstream file;
    std::string file_name;
    std::filesystem::path path;
    int line;
    Parser parser;
    AssemblyMap asmMap;
};
