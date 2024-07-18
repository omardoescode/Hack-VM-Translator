#include "Parser.h"
#include "Error.h"
#include "enums.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

Parser::Parser () {
}
Parser::Parser (const std::filesystem::path path) : file_path (path) {
    file_name = file_path.filename ().stem ().string ();
    file_name = file_name.substr (0, file_name.find_last_of ('.'));
    current   = -1;

    readFile ();
}

void Parser::readFile () {
    std::ifstream text_file (file_path);
    std::string line;

    while (std::getline (text_file, line)) {
        if (text_file.bad ())
            throw Error ("Parser::readFile: Error reading file");

        line = cleanString (line);

        if (line.empty ())
            continue;

        commands.push_back (line);
    }
}

std::string Parser::cleanString (std::string text) {
    auto comment = text.find ("//");
    if (comment != std::string::npos)
        text.erase (comment);

    // remove whitespaces
    return removeWhitespaces (text);
}

std::string Parser::removeWhitespaces (std::string text) {
    // remove leading and trailing spaces
    std::regex pattern (R"(^\s+|\s+$)");
    text = std::regex_replace (text, pattern, "");

    // remove double spaces
    pattern = R"(\s+)";
    return std::regex_replace (text, pattern, " ");
}

bool Parser::hasMoreCommands () {
    return (current + 1) < commands.size ();
}

std::string Parser::advance () {
    current++;
    splitCommand ();
    return current_command[0];
}
commandOperation Parser::getOperation () {
    return operationMap[current_command.at (0)];
}
segment Parser::getSegment () {
    return segmentMap[current_command.at (1)];
}
void Parser::splitCommand () {
    current_command.clear ();

    std::string command = commands.at (current);
    std::stringstream splitter (command);
    std::string item;

    for (int i = 0; i < 3; i++) {
        if (std::getline (splitter, item, ' ')) {
            current_command.push_back (item);
        } else {
            // push nothing if no remaining items
            current_command.push_back (std::string ());
        }
    }
}

commandType Parser::getCommandType () {
    std::string command = current_command[0];

    if (commandMap.find (command) != commandMap.end ())
        return commandMap[command];

    // not in commandMap
    return commandType::C_ARITHMETIC;
}


//
std::string Parser::arg1 () {
    if (getCommandType () == commandType::C_ARITHMETIC)
        return current_command[0];
    return current_command[1];
}
int Parser::arg2 () {
    return std::stoi (current_command[2]);
}

std::string Parser::getFileName () {
    return file_name;
}


std::unordered_map<std::string, commandType> Parser::commandMap = {
    { "push", commandType::C_PUSH }, { "pop", commandType::C_POP },
    { "label", commandType::C_LABEL }, { "goto", commandType::C_GOTO },
    { "if-goto", commandType::C_IF }, { "function", commandType::C_FUNCTION },
    { "call", commandType::C_CALL }, { "return", commandType::C_RETURN },
    // The remaining ones are C_ARITHMETIC
};
std::unordered_map<std::string, commandOperation> Parser::operationMap = {
    { "add", commandOperation::ADD },
    { "sub", commandOperation::SUB },
    { "neg", commandOperation::NEG },
    { "eq", commandOperation::EQ },
    { "gt", commandOperation::GT },
    { "lt", commandOperation::LT },
    { "and", commandOperation::AND },
    { "or", commandOperation::OR },
    { "not", commandOperation::NOT },
};
std::unordered_map<std::string, segment> Parser::segmentMap = {
    { "local", segment::LOCAL },
    { "argument", segment::ARGUMENT },
    { "temp", segment::TEMP },
    { "pointer", segment::POINTER },
    { "this", segment::THIS },
    { "that", segment::THAT },
    { "static", segment::STATIC },
    { "constant", segment::CONSTANT },
};
