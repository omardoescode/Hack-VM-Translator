#pragma once

enum class commandType {
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL
};


enum class commandOperation { ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT };

enum class segment {
    ARGUMENT,
    LOCAL,
    STATIC,
    CONSTANT,
    THIS,
    THAT,
    POINTER,
    TEMP
};
