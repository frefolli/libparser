#include "tests/symbol.hh"
#include "tests/production.hh"
#include "tests/parser.hh"
#include <iostream>

int main(int argc, char**args) {
    std::cout << THE_PROJECT << " " <<
        THE_VERSION  << " (" <<
        THE_BRANCH << ", " <<
        __DATE__ << ", " <<
        __TIME__ << ") [" <<
        THE_BUILDER << ", " <<
        THE_COMPILER << ", " <<
        THE_ASSEMBLER << "] on " <<
        THE_OS << std::endl;
    TestSymbol();
    TestProduction();
    TestParser();
}
