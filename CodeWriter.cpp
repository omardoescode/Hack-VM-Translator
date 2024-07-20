#include "CodeWriter.h"
#include "Error.h"
#include "enums.h"
#include <format>
#include <iostream>
#include <string>
CodeWriter::CodeWriter (const std::filesystem::path path, AssemblyMap asmMap)
: path (path), asmMap (asmMap), file (path), line (-1), has_initialized (false) {
}
void CodeWriter::setParser (Parser newParser) {
    parser    = newParser;
    file_name = parser.getFileName ();
}

void CodeWriter::write () {
    if (!has_initialized) {
        has_initialized = true;
        writeInit ();
    }
    while (parser.hasMoreCommands ()) {
        std::string instruction = parser.advance ();

        file << "// " << instruction << ", line " << ++line << std::endl;

        auto command_type = parser.getCommandType ();
        switch (command_type) {
        case commandType::C_ARITHMETIC: writeArithmetic (); break;
        case commandType::C_PUSH: writePush (); break;
        case commandType::C_POP: writePop (); break;
        case commandType::C_LABEL: writeLabel (); break;
        case commandType::C_IF: writeIfGoto (); break;
        case commandType::C_GOTO: writeIfGoto (); break;
        case commandType::C_FUNCTION: writeFunction (); break;
        case commandType::C_RETURN: writeReturn (); break;
        case commandType::C_CALL: writeCall (); break;
        }
    }
}

void CodeWriter::writeArithmetic () {
    switch (parser.getOperation ()) {
    case commandOperation::ADD: file << asmMap.get_command ("add"); break;
    case commandOperation::SUB: file << asmMap.get_command ("sub"); break;
    case commandOperation::NEG: file << asmMap.get_command ("neg"); break;
    case commandOperation::NOT: file << asmMap.get_command ("not"); break;
    case commandOperation::AND: file << asmMap.get_command ("and"); break;
    case commandOperation::OR: file << asmMap.get_command ("or"); break;
    case commandOperation::EQ:
        writeFormatted ("eq", "EQUAL" + std::to_string (line));
        break;
    case commandOperation::GT:
        writeFormatted ("gt", "GREATER" + std::to_string (line));
        break;
    case commandOperation::LT:
        writeFormatted ("lt", "SMALLER" + std::to_string (line));
        break;
    }
}

void CodeWriter::writePush () {
    switch (parser.getSegment ()) {
    case segment::LOCAL:
        writeFormatted ("push_local", std::to_string (parser.arg2 ()));
        break;
    case segment::ARGUMENT:
        writeFormatted ("push_argument", std::to_string (parser.arg2 ()));
        break;
    case segment::THIS:
        writeFormatted ("push_this", std::to_string (parser.arg2 ()));
        break;
    case segment::THAT:
        writeFormatted ("push_that", std::to_string (parser.arg2 ()));
        break;
    case segment::POINTER:
        writeFormatted ("push_pointer", std::to_string (parser.arg2 () + 3));
        break;
    case segment::TEMP:
        writeFormatted ("push_temp", std::to_string (parser.arg2 () + 5));
        break;
    case segment::CONSTANT:
        writeFormatted ("push_constant", std::to_string (parser.arg2 ()));
        break;
    case segment::STATIC:
        writeFormatted ("push_static", file_name + "." + std::to_string (parser.arg2 ()));
        break;
    }
}
void CodeWriter::writePop () {
    switch (parser.getSegment ()) {
    case segment::LOCAL:
        writeFormatted ("pop_local", std::to_string (parser.arg2 ()));
        break;
    case segment::ARGUMENT:
        writeFormatted ("pop_argument", std::to_string (parser.arg2 ()));
        break;
    case segment::THIS:
        writeFormatted ("push_this", std::to_string (parser.arg2 ()));
        break;
    case segment::THAT:
        writeFormatted ("push_that", std::to_string (parser.arg2 ()));
        break;
    case segment::POINTER:
        writeFormatted ("push_pointer", std::to_string (parser.arg2 () + 3));
        break;
    case segment::TEMP:
        writeFormatted ("push_temp", std::to_string (parser.arg2 () + 5));
        break;
    case segment::CONSTANT:
        throw Error ("CodeWriter::writePop: Cannot pop constant at line " +
        std::to_string (line));
        break;
    case segment::STATIC:
        writeFormatted ("push_static", file_name + "." + std::to_string (parser.arg2 ()));
        break;
    }
}

template <typename... Args>
void CodeWriter::writeFormatted (const std::string& asmKey, Args&&... args) {
    const std::string command = asmMap.get_command (asmKey);
    file << std::vformat (command, std::make_format_args (std::forward<Args> (args)...));
}


void CodeWriter::writeFormatted (const std::string& asmKey, std::string args) {
    const std::string command = asmMap.get_command (asmKey);
    file << std::vformat (command, std::make_format_args (args));
}
void CodeWriter::writeLabel () {
    writeFormatted ("label", parser.arg1 ());
}

void CodeWriter::writeGoto () {
    writeFormatted ("goto", parser.arg1 ());
}
void CodeWriter::writeIfGoto () {
    writeFormatted ("if_goto", parser.arg1 ());
}

void CodeWriter::close () {
    file.close ();
}

void CodeWriter::writeInit () {
    file << asmMap.get_command ("init");
}

void CodeWriter::writeCall () {
    std::string return_address =
    current_function_name + "$ret" + std::to_string (call_count++);
    std::string n = std::to_string (parser.arg2 ());
    writeFormatted ("call", return_address, n, current_function_name);
}

void CodeWriter::writeFunction () {
    current_function_name = parser.arg1 ();
    call_count            = 0;
    std::string arg1      = std::to_string (parser.arg2 ());
    writeFormatted ("function", arg1, current_function_name);
}

void CodeWriter::writeReturn () {
    writeFormatted ("return");
}
