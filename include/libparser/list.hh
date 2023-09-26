#ifndef LIBPARSER_LIST_HH
#define LIBPARSER_LIST_HH

#include <vector>
#include <sstream>
#include <libparser/node.hh>

// lexemCount = sum([node.lexemCount for node in children])
template <typename Terminal, typename NonTerminal>
class List : public Node<Terminal, NonTerminal> {
    private:
        NonTerminal head;
        std::vector<Node<Terminal, NonTerminal>*> children;
    public:
        List(NonTerminal head,
             std::vector<Node<Terminal, NonTerminal>*> children) :
            head(head), children(children) {
            for (const Node<Terminal, NonTerminal>* child : children) {
                this->lexemCount += child->getLexemCount();
            }
        }
        ~List() {
            for (const Node<Terminal, NonTerminal>* child : children) {
                if (child)
                    delete child;
            }
        }
        bool isAtom() const {
            return false;
        }
        bool isList() const {
            return true;
        }
        std::string toString() const {
            std::ostringstream out ("");
            out << "(" << head;
            for (const Node<Terminal, NonTerminal>* child : children) {
                out << " " << child->toString();
            }
            out << ")";
            return out.str();
        }
        NonTerminal getHead() const {
            return head;
        }
};

#endif
