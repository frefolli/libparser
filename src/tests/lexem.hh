#ifndef LIBPARSER_TESTS_LEXEM_HH
#define LIBPARSER_TESTS_LEXEM_HH
#include <ostream>
#include <vector>
#include "terminal.hh"
#include <liblexer/lexer.hh>

std::ostream& operator<<(std::ostream& out, std::vector<Lexem<Terminal>> lexems);

#endif
