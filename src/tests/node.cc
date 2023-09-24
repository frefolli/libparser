#include "node.hh"
#include "nonterminal.hh"

#include <iostream>
#include <libparser/node.hh>
#include <libparser/atom.hh>
#include <libparser/list.hh>

void TestNode() {
    std::cout << "TestSymbol::START" << std::endl;
    Node<NonTerminal>* node = new List<NonTerminal>(EXPR, {
        new List<NonTerminal>(TERM, {new Atom<NonTerminal>("17")}),
        new Atom<NonTerminal>("*"),
        new List<NonTerminal>(EXPR, {
            new List<NonTerminal>(TERM, {new Atom<NonTerminal>("x")}),
            new Atom<NonTerminal>("-"),
            new List<NonTerminal>(TERM, {new Atom<NonTerminal>("19")})
        })
    });
    std::cout << node->toString() << std::endl;
    delete node;
    std::cout << "TestSymbol::END" << std::endl;
}
