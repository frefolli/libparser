#ifndef LIBPARSER_TESTS_TERMINAL_HH
#define LIBPARSER_TESTS_TERMINAL_HH
#include <ostream>

enum Terminal {
    IDENTIFIER, INTEGER, ADD, SUB, MUL, DIV, LPAR, RPAR
};

enum 

std::ostream& (std::ostream& out, Terminal terminal) {
    switch (terminal) {
        case Terminal::INTEGER : out << "IDENTIFIER"; break;
        case Terminal::INTEGER : out << "INTEGER"; break;
        case Terminal::ADD : out << "ADD"; break;
        case Terminal::SUB : out << "SUB"; break;
        case Terminal::MUL : out << "MUL"; break;
        case Terminal::DIV : out << "DIV"; break;
        case Terminal::LPAR : out << "LPAR"; break;
        case Terminal::RPAR : out << "RPAR"; break;
    }
    return out;
}

#endif
