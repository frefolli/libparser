#ifndef LIBPARSER_PARSER_HH
#define LIBPARSER_PARSER_HH

#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <map>
#include <sstream>
#include <algorithm>

template <typename Terminal, typename NonTerminal>
struct Parser {
    std::map<Symbol<Terminal, NonTerminal>, Production<Terminal, NonTerminal>> productions;

    public:
        Parser(std::vector<Production<Terminal, NonTerminal>> v) {
            std::transform(v.begin(), v.end(), std::inserter(productions, productions.end()),
                           [](const Production<Terminal, NonTerminal>& prod) { return std::make_pair(prod.getLeft(), prod); });
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
