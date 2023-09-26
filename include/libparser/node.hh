#ifndef LIBPARSER_NODE_HH
#define LIBPARSER_NODE_HH

#include <string>

template <typename Terminal, typename NonTerminal>
class Node {
    protected:
        unsigned int lexemCount = 0;
    public:
        Node() {}
        virtual ~Node() {}
        virtual bool isAtom() const = 0;
        virtual bool isList() const = 0;
        virtual std::string toString() const = 0;
        unsigned int getLexemCount() const {
            return lexemCount;
        }
};

#endif
