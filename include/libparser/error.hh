#ifndef LIBPARSER_ERROR_HH
#define LIBPARSER_ERROR_HH

#include <stdexcept>
#include <string>

template <typename Terminal, typename NonTerminal, typename Lexem>
class ParserError : public std::runtime_error {
    private:
        std::string message;
    public:
        ParserError(std::string message) : std::runtime_error("") {
            this->message = "Parser Error" + message;
        }
        const char* what() {
            return this->message.c_str();
        }
};

#endif
