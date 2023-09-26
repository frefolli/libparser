#include "calc.hh"
#include "terminal.hh"
#include "nonterminal.hh"
#include <liblexer/lexer.hh>
#include <liblexer/lexer_rule.hh>
#include <liblexer/lexem.hh>
#include <libparser/symbol.hh>
#include <libparser/production.hh>
#include <libparser/parser_topdown.hh>
#include <liblexer/lexem.hh>
#include <iostream>

Lexer<Terminal> lexer ({
    {"^[a-zA-Z_][a-zA-Z_0-9]*", Terminal::IDENTIFIER, false},
    {"^[0-9]+", Terminal::INTEGER, false},
    {"^\\+", Terminal::ADD, false},
    {"^\\-", Terminal::SUB, false},
    {"^\\*", Terminal::MUL, false},
    {"^\\\\", Terminal::DIV, false},
    {"^\\(", Terminal::LPAR, false},
    {"^\\)", Terminal::RPAR, false},
    {"^\\s+", Terminal::SPACE, true},
    {"^#[^\\n]+(?:\\n|$)", Terminal::COMMENT, true},
});

ParserTopDown<Terminal, NonTerminal, Lexem<Terminal>> parser ({
    {LINE, {
        {EXPR},
    }},
    {EXPR, {
        {TERM, OP, EXPR},
        {TERM}}},
    {OP, {
        {ADD},
        {SUB},
        {MUL},
        {DIV}
    }},
    {LITERAL, {
        {INTEGER}
    }},
    {TERM, {
        {LITERAL},
        {IDENTIFIER}}}
});

void RunCalc() {
    std::string line;
    std::vector<Lexem<Terminal>> lexems;
    List<Terminal, NonTerminal>* cst = nullptr;
    bool active = true;
    while (active) {
        std::cout << ">> ";
        std::getline(std::cin, line);
        try {
            lexems = lexer.process(line);
            cst = parser.process_symbol(LINE, lexems.begin(), lexems.end());
            if (cst) {
                std::cout << cst->toString() << std::endl;
                delete cst;
            }
        } catch(LexerError<Terminal>& error) {
            std::cout << error.what() << " while processing:" << std::endl;
            std::cout << "\"" << line << "\"" << std::endl;
        }
    }
    std::cout << "safely quitting ..." << std::endl;
}
