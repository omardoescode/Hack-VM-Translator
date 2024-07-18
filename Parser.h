#pragma once
#include "enums.h"
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>

class Parser {
public:
    Parser ();
    Parser (const std::filesystem::path path);

    bool hasMoreCommands ();
    std::string advance ();


    // command types
    commandType getCommandType ();
    commandOperation getOperation ();

    std::string arg1 ();
    segment getSegment ();
    int arg2 ();

    std::string getFileName ();

private:
    void readFile ();
    std::string cleanString (std::string text);
    std::string removeWhitespaces (std::string text);
    void splitCommand ();

private:
    int current;
    std::string file_name;
    std::filesystem::path file_path;
    std::vector<std::string> current_command;
    std::vector<std::string> commands;

    static std::unordered_map<std::string, commandType> commandMap;
    static std::unordered_map<std::string, commandOperation> operationMap;
    static std::unordered_map<std::string, segment> segmentMap;
};
