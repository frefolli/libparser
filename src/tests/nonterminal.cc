#include "nonterminal.hh"
#include <ostream>

std::ostream& operator<<(std::ostream& out, NonTerminal nonTerminal) {
    switch (nonTerminal) {
        case NonTerminal::TERM : out << "TERM"; break;
        case NonTerminal::EXPR : out << "EXPR"; break;
        case NonTerminal::LINE : out << "LINE"; break;
        case NonTerminal::OP : out << "OP"; break;
        case NonTerminal::LITERAL : out << "LITERAL"; break;
    }
    return out;
}
