#include "Translator.h"
#include <iostream>
int main (int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Invalid Input to the file";
        return -1;
    }

    std::string inp = argv[1], out;
    if (argc == 3)
        out = argv[3];
    else
        out = inp.substr (0, inp.size () - 3) + ".asm";

    Translator translator (inp, out);

    std::cout << "-- Translating to " << out << "\n";
    translator.translate ();

    return 0;
}
