#pragma once
#include "../Parser.h"
#include <iostream>
bool TestParserReader () {
    std::string file_name = "./Test.vm";

    Parser parser (file_name);
    while (parser.hasMoreCommands ()) {
        parser.advance ();
        std::cout << "-- " << parser.arg1 () << " " << std::endl;
    }

    return true;
}
