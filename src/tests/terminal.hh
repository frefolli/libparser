#ifndef LIBPARSER_TESTS_TERMINAL_HH
#define LIBPARSER_TESTS_TERMINAL_HH

#include <ostream>

enum Terminal {
    IDENTIFIER, INTEGER, ADD, SUB, MUL, DIV, LPAR, RPAR
};

std::ostream& operator<<(std::ostream& out, Terminal terminal);

#endif
