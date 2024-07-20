#include "Translator.h"
#include "CodeWriter.h"
#include "Error.h"
#include <filesystem>
#include <iostream>

Translator::Translator (std::string inp_files)
: inp_files (inp_files), asmMap ("Data/") {
    if (!std::filesystem::exists (inp_files)) {
        throw Error ("Translator Constructor: File doesn't exist");
    }
    set_output_file_name ();
}

void Translator::translate () {
    std::filesystem::path inp_path (inp_files);
    if (std::filesystem::is_directory (inp_path))
        translate_files ();
    else
        translate_file ();
}

void Translator::translate_file () {
    std::filesystem::path out_path = out_files, in_path = inp_files;
    CodeWriter codeWriter (out_path, asmMap);

    auto path = in_path.stem ().string ();
    if (path.substr (path.find_last_of (".") + 1) != "vm")
        throw Error ("Translator::translate_file:  File is not of type .vm");
    Parser parser (inp_files);
    codeWriter.setParser (parser);
    codeWriter.write ();
    codeWriter.close ();
}

void Translator::translate_files () {
    std::filesystem::path out_path = out_files, in_path = inp_files;
    CodeWriter codeWriter (out_path, asmMap);

    for (const std::filesystem::path& entry :
    std::filesystem::recursive_directory_iterator (inp_files)) {
        if (entry.extension () != ".vm")
            continue;

        Parser parser (entry);
        codeWriter.setParser (parser);
        codeWriter.write ();
    }

    codeWriter.close ();
}

void Translator::set_output_file_name () {
    if (std::filesystem::is_directory (inp_files)) {
        out_files = inp_files.filename ().string ().append (".asm");
    } else {
        out_files = inp_files.stem ().string ().append (".asm");
    }
}

std::string Translator::get_out_file_name () {
    return out_files;
}
