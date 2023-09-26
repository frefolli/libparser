#ifndef LIBPARSER_ATOM_HH
#define LIBPARSER_ATOM_HH

#include <libparser/node.hh>

// lexemCount = 1
template <typename Terminal, typename NonTerminal>
class Atom : public Node<Terminal, NonTerminal> {
    private:
        std::string string;
        Terminal terminal;
    public:
        Atom(std::string string,
             Terminal terminal) :
            string(string), terminal(terminal) {
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
        Terminal getTerminal() const {
            return terminal;
        }
};

#endif
