#pragma once
#include <string>
#include <unordered_map>

class AssemblyMap {
public:
    AssemblyMap (std::string);

    std::string get_command (std::string);

private:
    bool initialize (std::string);

private:
    std::unordered_map<std::string, std::string> map;
};
