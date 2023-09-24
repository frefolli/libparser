#include "nonterminal.hh"
#include <ostream>

std::ostream& operator<<(std::ostream& out, NonTerminal nonTerminal) {
    switch (nonTerminal) {
        case NonTerminal::TERM : out << "TERM"; break;
        case NonTerminal::EXPR : out << "EXPR"; break;
    }
    return out;
}
