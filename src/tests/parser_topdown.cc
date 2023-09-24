#include "parser.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <libparser/parser_topdown.hh>
#include <iostream>

void TestParserTopDown() {
    std::cout << "TestParserTopDown::START" << std::endl;
    ParserTopDown<Terminal, NonTerminal> parser ({
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
    std::cout << "TestParserTopDown::END" << std::endl;
}
