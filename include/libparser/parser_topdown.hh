#ifndef LIBPARSER_PARSER_TOPDOWN_HH
#define LIBPARSER_PARSER_TOPDOWN_HH

#include <libparser/parser.hh>

template <typename Terminal, typename NonTerminal>
class ParserTopDown : public Parser<Terminal, NonTerminal> {
    public:
        ParserTopDown(std::vector<Production<Terminal, NonTerminal>> grammar) :
            Parser<Terminal, NonTerminal>(grammar) {}
};

#endif
