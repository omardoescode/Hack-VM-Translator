#pragma once
#include "AssemblyMap.h"
#include <string>
class Translator {
public:
    Translator (std::string inp_file, std::string out_file);

    void translate ();

private:
    std::string inp_file, out_file;
    AssemblyMap asmMap;
};
