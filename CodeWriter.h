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

    // Writes the bootstrap assembly instruction that effect het bootstrap code tah tinitialzies the VM. This code must be placed at the beginning of the .asm file
    void writeInit ();

    void close ();

private:
    void writeArithmetic ();
    void writePush ();
    void writePop ();
    void writeLabel ();
    void writeGoto ();
    void writeIfGoto ();
    void writeCall ();
    void writeFunction ();
    void writeReturn ();


    template <typename... Args>
    void writeFormatted (const std::string& asmKey, Args&&... args);
    void writeFormatted (const std::string& asmKey, std::string args);


private:
    std::ofstream file;
    std::string file_name;
    std::filesystem::path path;
    int line;
    Parser parser;
    AssemblyMap asmMap;
    bool has_initialized;

    // Function Parameters
    std::string current_function_name;
    int call_count;
};
