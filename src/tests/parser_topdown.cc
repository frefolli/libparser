#include "parser_topdown.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <libparser/parser_topdown.hh>
#include <liblexer/lexem.hh>
#include <iostream>

std::ostream& operator<<(std::ostream& out, std::vector<Lexem<Terminal>> lexems) {
    bool first = false;
    out << "{";
    for (const Lexem<Terminal>& lexem : lexems) {
        if (first) {
            first = true;
        } else {
            out << " ";
        }
        out << lexem.toString();
    }
    out << "}";
    return out;
}

void TestParserTopDown() {
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
    ParserTopDown<Terminal, NonTerminal, Lexem<Terminal>> parser ({
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

    List<NonTerminal>* cst = parser.process_symbol(EXPR, input.begin(), input.end());
    if (cst) {
        std::cout << "# Concrete Syntax Tree:" << std::endl;
        std::cout << cst->toString() << std::endl;
        delete cst;
    }
}
