#ifndef LIBPARSER_PARSER_CLR_HH
#define LIBPARSER_PARSER_CLR_HH

#include <libparser/parser.hh>
#include <libparser/node.hh>
#include <libparser/atom.hh>
#include <libparser/list.hh>

template <typename Terminal, typename NonTerminal, typename Lexem>
class ParserCLR : public Parser<Terminal, NonTerminal, Lexem> {
    public:
        ParserCLR(std::vector<Production<Terminal, NonTerminal>> grammar) :
            Parser<Terminal, NonTerminal, Lexem>(grammar) {}
};

#endif
