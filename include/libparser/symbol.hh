#ifndef LIBPARSER_SYMBOL_HH
#define LIBPARSER_SYMBOL_HH

#include <ostream>
#include <string>

template <typename Terminal, typename NonTerminal>
struct Symbol {
    union {
        Terminal t;
        NonTerminal nt;
    } value;
    bool isTerminal;

    public:
        Symbol(Terminal t) {
            value.t = t;
            isTerminal = true;
        }

        Symbol(NonTerminal nt) {
            value.nt = nt;
            isTerminal = false;
        }

        std::string toString() const {
            std::ostringstream out ("");
            if (isTerminal)
                out << t;
            else
                out << nt;
            return out.str();
        }

        bool operator!=(Symbol other) {
            return !(this->operator==(other));
        }
        bool operator==(Symbol other) {
            if (isTerminal != other.isTerminal)
                return false;
            if (isTerminal)
                return value.t == other.value.t;
            return value.nt == other.value.nt;
        }
};

#endif
