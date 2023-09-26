#include "lexem.hh"
#include "parser_clr.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <libparser/parser_clr.hh>
#include <liblexer/lexem.hh>
#include <iostream>

void TestParserCLR() {
    std::cout << "# Input Lexem Stream:" << std::endl;
    std::vector<Lexem<Terminal>> input = {
        {"17", INTEGER},
        {"-", SUB},
        {"42", INTEGER},
        {"+", ADD},
        {"value", IDENTIFIER}
    };
    std::cout << input << std::endl << std::endl;

    std::cout << "# Parser Top Down:" << std::endl;
    ParserCLR<Terminal, NonTerminal, Lexem<Terminal>> parser ({
        {EXPR, {
            {TERM, ADD, EXPR},
            {TERM, SUB, EXPR},
            {TERM, MUL, EXPR},
            {TERM, DIV, EXPR},
            {TERM}}},
        {TERM, {
            {INTEGER},
            {IDENTIFIER}}}
    });
    std::cout << parser.toString() << std::endl << std::endl;

    List<Terminal, NonTerminal>* cst = parser.process(EXPR, input.begin(), input.end());
    if (cst) {
        std::cout << "# Concrete Syntax Tree:" << std::endl;
        std::cout << cst->toString() << std::endl;
        delete cst;
    }
}
