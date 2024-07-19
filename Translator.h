#pragma once
#include "AssemblyMap.h"
#include <filesystem>
#include <string>
class Translator {
public:
    Translator (std::string);

    void translate ();

    std::string get_out_file_name ();

private:
    void translate_file ();
    void translate_files ();
    void set_output_file_name ();

private:
    std::filesystem::path inp_files, out_files;
    AssemblyMap asmMap;
};
