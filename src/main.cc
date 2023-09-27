#include "tests/parser_bottomup.hh"
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
    TestParserBottomUp();
}
