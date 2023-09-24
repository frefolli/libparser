#include "symbol.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <iostream>
#include <libparser/symbol.hh>

void TestSymbol() {
    std::cout << "TestSymbol::START" << std::endl;
    Symbol<Terminal, NonTerminal> A = (Terminal::INTEGER);
    Symbol<Terminal, NonTerminal> B = (NonTerminal::TERM);
    std::cout << "A = " << A.toString() << std::endl;
    std::cout << "B = " << B.toString() << std::endl;
    std::cout << "TestSymbol::END" << std::endl;
}
