#include "CodeWriter.h"
#include "Error.h"
#include "enums.h"
#include <format>
#include <iostream>
CodeWriter::CodeWriter (const std::filesystem::path path, AssemblyMap asmMap)
: path (path), asmMap (asmMap), file (path), line (-1) {
}
void CodeWriter::setParser (Parser newParser) {
    parser    = newParser;
    file_name = parser.getFileName ();
}

void CodeWriter::write () {

    while (parser.hasMoreCommands ()) {
        std::string instruction = parser.advance ();

        file << "// " << instruction << ", line " << ++line << std::endl;

        // TODO: Continue Building The remaining options
        auto command_type = parser.getCommandType ();
        switch (command_type) {
        case commandType::C_ARITHMETIC: writeArithmetic (); break;
        case commandType::C_PUSH: writePush (); break;
        case commandType::C_POP: writePop (); break;
        case commandType::C_LABEL: writeLabel (); break;
        case commandType::C_IF: writeIfGoto (); break;
        case commandType::C_GOTO: writeIfGoto (); break;
        default: throw Error ("CodeWriter::write: Invalid Command Type");
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
        ;
    case segment::STATIC:
        writeFormatted ("push_static", file_name + "." + std::to_string (parser.arg2 ()));
        break;
    }
}

void CodeWriter::writeFormatted (std::string asmKey, std::string arg) {
    const std::string command = asmMap.get_command (asmKey);
    file << std::vformat (command, std::make_format_args (arg));
}
void CodeWriter::writeLabel () {
    std::cout << parser.arg1 () << std::endl;
    ;
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
