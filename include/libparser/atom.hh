#ifndef LIBPARSER_ATOM_HH
#define LIBPARSER_ATOM_HH

#include <libparser/node.hh>

// lexemCount = 1
template <typename NonTerminal>
class Atom : public Node<NonTerminal> {
    private:
        std::string string;
    public:
        Atom(std::string string) :
            string(string) {
            this->lexemCount = 1;
        }
        bool isAtom() const {
            return true;
        }
        bool isList() const {
            return false;
        }
        std::string toString() const {
            return string;
        }
};

#endif
