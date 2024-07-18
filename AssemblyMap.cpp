#include "AssemblyMap.h"
#include "Error.h"
#include <filesystem>
#include <fstream>
#include <iostream>

AssemblyMap::AssemblyMap (std::string path_name) {
    if (!std::filesystem::exists (path_name) || !initialize (path_name))
        throw Error ("AssemblyMap Constructor: Initialization Failed");
    // for (const auto& [key, val] : map)
    //     std::cout << key << ": " << val << std::endl;
    std::cout << "-- Assembly Map Initialized\n";
}


std::string AssemblyMap::get_command (std::string cmd) {
    return map[cmd];
}

bool AssemblyMap::initialize (std::string path_name) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator (path_name)) {
        if (!entry.is_regular_file ())
            continue;

        std::ifstream file (entry.path ());
        std::stringstream content;

        content << file.rdbuf ();
        map[entry.path ().filename ().stem ().string ()] = content.str ();

        if (file.bad ())
            return false;
    }

    return !map.empty ();
}
