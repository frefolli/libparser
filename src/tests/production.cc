#include "production.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <iostream>

void TestProduction() {
    std::cout << "TestProduction::START" << std::endl;
    Production<Terminal, NonTerminal> prod (NonTerminal::EXPR, {
        {NonTerminal::TERM},
        {Terminal::LPAR, NonTerminal::EXPR, Terminal::RPAR},
        {NonTerminal::EXPR, Terminal::ADD, NonTerminal::EXPR},
        {NonTerminal::EXPR, Terminal::SUB, NonTerminal::EXPR},
        {NonTerminal::EXPR, Terminal::MUL, NonTerminal::EXPR},
        {NonTerminal::EXPR, Terminal::DIV, NonTerminal::EXPR}
    });
    std::cout << prod.toString() << std::endl;
    std::cout << "TestProduction::END" << std::endl;
}
