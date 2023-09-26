#include "parser_clr.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <libparser/parser_clr.hh>
#include <iostream>

void TestParserCLR() {
    std::cout << "TestParserCLR::START" << std::endl;
    ParserCLR<Terminal, NonTerminal, int> parser ({
        {EXPR, {
            {TERM},
            {LPAR, EXPR, RPAR},
            {EXPR, ADD, EXPR},
            {EXPR, SUB, EXPR},
            {EXPR, MUL, EXPR},
            {EXPR, DIV, EXPR}}},
        {TERM, {
            {INTEGER},
            {IDENTIFIER}}}
    });
    std::cout << parser.toString() << std::endl;
    std::cout << "TestParserCLR::END" << std::endl;
}
