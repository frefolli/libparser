#include "lexem.hh"

std::ostream& operator<<(std::ostream& out, std::vector<Lexem<Terminal>> lexems) {
    bool first = false;
    out << "{";
    for (const Lexem<Terminal>& lexem : lexems) {
        if (first) {
            first = true;
        } else {
            out << " ";
        }
        out << lexem.toString();
    }
    out << "}";
    return out;
}
