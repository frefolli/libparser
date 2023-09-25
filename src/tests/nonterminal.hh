#ifndef LIBPARSER_TESTS_NON_TERMINAL_HH
#define LIBPARSER_TESTS_NON_TERMINAL_HH

#include <ostream>

enum NonTerminal {
    LINE, TERM, EXPR, OP, LITERAL
};

std::ostream& operator<<(std::ostream& out, NonTerminal nonTerminal);

#endif
