#include "parser.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <libparser/parser.hh>
#include <iostream>

void TestParser() {
    std::cout << "TestParser::START" << std::endl;
    Parser<Terminal, NonTerminal> parser ({
        {NonTerminal::EXPR, {
            {NonTerminal::TERM},
            {Terminal::LPAR, NonTerminal::EXPR, Terminal::RPAR},
            {NonTerminal::EXPR, Terminal::ADD, NonTerminal::EXPR},
            {NonTerminal::EXPR, Terminal::SUB, NonTerminal::EXPR},
            {NonTerminal::EXPR, Terminal::MUL, NonTerminal::EXPR},
            {NonTerminal::EXPR, Terminal::DIV, NonTerminal::EXPR}}},
        {NonTerminal::TERM, {
            {Terminal::INTEGER},
            {Terminal::IDENTIFIER}}}
    });
    std::cout << parser.toString() << std::endl;
    std::cout << "TestParser::END" << std::endl;
}
