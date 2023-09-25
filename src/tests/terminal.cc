#include "terminal.hh"
#include <ostream>

std::ostream& operator<<(std::ostream& out, Terminal terminal) {
    switch (terminal) {
        case Terminal::IDENTIFIER : out << "IDENTIFIER"; break;
        case Terminal::INTEGER : out << "INTEGER"; break;
        case Terminal::ADD : out << "ADD"; break;
        case Terminal::SUB : out << "SUB"; break;
        case Terminal::MUL : out << "MUL"; break;
        case Terminal::DIV : out << "DIV"; break;
        case Terminal::LPAR : out << "LPAR"; break;
        case Terminal::RPAR : out << "RPAR"; break;
        case Terminal::SPACE : out << "SPACE"; break;
        case Terminal::COMMENT : out << "COMMENT"; break;
    }
    return out;
}
