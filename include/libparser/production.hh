#ifndef LIBPARSER_PRODUCTION_HH
#define LIBPARSER_PRODUCTION_HH

#include <libparser/symbol.hh>
#include <vector>
#include <sstream>
#include <cassert>

template<typename Terminal, typename NonTerminal>
struct Production {
    NonTerminal symbol;
    std::vector<std::vector<Symbol<Terminal, NonTerminal>>> branches;

    void validate() {
#ifdef BAN_LEFT_RECURSIVE
        assert(! symbol.isTerminal);
        assert(branches.size() > 0);
        for (const std::vector<Symbol<Terminal, NonTerminal>>& branch) {
            assert(branch.size() > 0);
            assert(branch[0] != symbol);
        }
#endif
    }
    public:
        Production() {}
        Production(NonTerminal symbol,
                   std::vector<std::vector<Symbol<Terminal, NonTerminal>>> branches) :
            symbol(symbol), branches(branches) {}

        std::string toString() const {
            std::ostringstream out ("");
            out << symbol << " := ";
            for (auto bIt = branches.begin(); bIt != branches.end(); bIt++) {
                if (bIt != branches.begin())
                    out << " | ";
                for (auto sIt = bIt->begin(); sIt != bIt->end(); sIt++) {
                    if (sIt != bIt->begin())
                        out << " ";
                    out << sIt->toString();
                }
            }
            return out.str();
        }

        NonTerminal getLeft() const {
            return symbol;
        }

        std::vector<std::vector<Symbol<Terminal, NonTerminal>>>& getBranches() {
            return branches;
        }
};

#endif
