#include "tests/symbol.hh"
#include "tests/production.hh"
#include "tests/parser.hh"
#include "tests/parser_topdown.hh"
#include "tests/node.hh"
#include <iostream>

void PrintSignature() {
    std::cout << THE_PROJECT << " " <<
        THE_VERSION  << " (" <<
        THE_BRANCH << ", " <<
        __DATE__ << ", " <<
        __TIME__ << ") [" <<
        THE_BUILDER << ", " <<
        THE_COMPILER << ", " <<
        THE_ASSEMBLER << "] on " <<
        THE_OS << std::endl;
}

int main(int argc, char**args) {
    PrintSignature();
    //TestSymbol();
    //TestProduction();
    //TestParser();
    TestParserTopDown();
    //TestNode();
}
