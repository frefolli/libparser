#ifndef LIBPARSER_TESTS_NON_TERMINAL_HH
#define LIBPARSER_TESTS_NON_TERMINAL_HH

#include <ostream>

enum NonTerminal {
    TERM, EXPR
};

std::ostream& (std::ostream& out, NonTerminal nonTerminal) {
    switch (nonTerminal) {
        case NonTerminal::TERM : out << "TERM"; break;
        case NonTerminal::EXPR : out << "EXPR"; break;
    }
    return out;
}

#endif
