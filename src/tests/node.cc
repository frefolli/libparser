#include "node.hh"
#include "terminal.hh"
#include "nonterminal.hh"

#include <iostream>
#include <libparser/node.hh>
#include <libparser/atom.hh>
#include <libparser/list.hh>

void TestNode() {
    std::cout << "TestSymbol::START" << std::endl;
    Node<Terminal, NonTerminal>* node = new List<Terminal, NonTerminal>(EXPR, {
        new List<Terminal, NonTerminal>(TERM, {new Atom<Terminal, NonTerminal>("17", INTEGER)}),
        new Atom<Terminal, NonTerminal>("*", MUL),
        new List<Terminal, NonTerminal>(EXPR, {
            new List<Terminal, NonTerminal>(TERM, {new Atom<Terminal, NonTerminal>("x", IDENTIFIER)}),
            new Atom<Terminal, NonTerminal>("-", SUB),
            new List<Terminal, NonTerminal>(TERM, {new Atom<Terminal, NonTerminal>("19", INTEGER)})
        })
    });
    std::cout << node->toString() << std::endl;
    delete node;
    std::cout << "TestSymbol::END" << std::endl;
}
