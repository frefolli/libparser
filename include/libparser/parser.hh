#ifndef LIBPARSER_PARSER_HH
#define LIBPARSER_PARSER_HH

#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <map>
#include <sstream>
#include <algorithm>

template <typename Terminal, typename NonTerminal, typename Lexem>
class Parser {
    protected:
        std::map<NonTerminal, Production<Terminal, NonTerminal>> productions;

    public:
        Parser(std::vector<Production<Terminal, NonTerminal>> grammar) {
            for (const Production<Terminal, NonTerminal>& production : grammar) {
                productions[production.getLeft()] = production;
            }
            //std::transform(grammar.begin(), grammar.end(), std::inserter(productions, productions.end()),
            //               [](const Production<Terminal, NonTerminal>& prod) { return std::make_pair(prod.getLeft(), prod); });
        }

        std::string toString() {
            std::ostringstream out ("");
            for (auto it = productions.begin(); it != productions.end(); it++) {
                if (it != productions.begin())
                    out << "\n";
                out << it->second.toString();
            }
            return out.str();
        }
};

#endif
