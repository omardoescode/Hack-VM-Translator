#include "Translator.h"
#include "CodeWriter.h"
#include <iostream>

Translator::Translator (std::string inp_file, std::string out_file)
: inp_file (inp_file), out_file (out_file), asmMap ("Data/") {
}

void Translator::translate () {
    std::filesystem::path out_path = out_file, in_path = inp_file;
    CodeWriter codeWriter (out_path, asmMap);

    Parser parser (inp_file);
    codeWriter.setParser (parser);
    codeWriter.write ();
    codeWriter.close ();
}
