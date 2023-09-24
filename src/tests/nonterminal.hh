#ifndef LIBPARSER_TESTS_NON_TERMINAL_HH
#define LIBPARSER_TESTS_NON_TERMINAL_HH

#include <ostream>

enum NonTerminal {
    TERM, EXPR
};

std::ostream& operator<<(std::ostream& out, NonTerminal nonTerminal);

#endif
