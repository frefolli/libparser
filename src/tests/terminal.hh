#ifndef LIBPARSER_TESTS_TERMINAL_HH
#define LIBPARSER_TESTS_TERMINAL_HH

#include <ostream>

enum Terminal {
    COMMENT, IDENTIFIER, INTEGER, ADD, SUB, MUL, DIV, LPAR, RPAR, SPACE
};

std::ostream& operator<<(std::ostream& out, Terminal terminal);

#endif
