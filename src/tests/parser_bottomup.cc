#include "lexem.hh"
#include "parser_bottomup.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <libparser/parser_bottomup.hh>
#include <liblexer/lexem.hh>
#include <iostream>

void TestParserBottomUp() {
    std::cout << "# Input Lexem Stream:" << std::endl;
    std::vector<Lexem<Terminal>> input = {
        {"17", INTEGER},
        {"-", SUB},
        {"42", INTEGER},
        {"+", ADD},
        {"value", IDENTIFIER}
    };
    std::cout << input << std::endl << std::endl;

    std::cout << "# Parser Bottom Up:" << std::endl;
    ParserBottomUp<Terminal, NonTerminal, Lexem<Terminal>> parser ({
        {EXPR, {
            {EXPR, ADD, EXPR},
            {EXPR, SUB, EXPR},
            {EXPR, MUL, EXPR},
            {EXPR, DIV, EXPR},
            {TERM}}},
        {TERM, {
            {INTEGER},
            {IDENTIFIER}}}
    });
    std::cout << parser.toString() << std::endl << std::endl;

    List<Terminal, NonTerminal>* cst = parser.process_symbol(EXPR, input.begin(), input.end());
    if (cst) {
        std::cout << "# Concrete Syntax Tree:" << std::endl;
        std::cout << cst->toString() << std::endl;
        delete cst;
    }
}
