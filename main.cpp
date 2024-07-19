#include "Error.h"
#include "Translator.h"
#include <filesystem>
#include <iostream>
int main (int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Invalid Input to the file";
        return -1;
    }

    std::filesystem::path inp (argv[1]);

    Translator translator (inp);

    std::cout << "-- Translating to " << translator.get_out_file_name () << "\n";
    translator.translate ();

    return 0;
}
