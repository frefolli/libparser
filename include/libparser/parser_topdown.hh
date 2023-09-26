#ifndef LIBPARSER_PARSER_TOPDOWN_HH
#define LIBPARSER_PARSER_TOPDOWN_HH

#include <libparser/parser.hh>
#include <libparser/node.hh>
#include <libparser/atom.hh>
#include <libparser/list.hh>

template <typename Terminal, typename NonTerminal, typename Lexem>
class ParserTopDown : public Parser<Terminal, NonTerminal, Lexem> {
    private:
        std::vector<Node<Terminal, NonTerminal>*> process_branch(const std::vector<Symbol<Terminal, NonTerminal>>& branch,
                                          typename std::vector<Lexem>::iterator begin,
                                          typename std::vector<Lexem>::iterator end) const {
            std::vector<Node<Terminal, NonTerminal>*> children = {};
            for (auto it = branch.begin();
                 it != branch.end(); ++it) {
                if (it->isTerminal) {
                    Atom<Terminal, NonTerminal>* child = process_lexem(it->asTerminal(), begin, end);
                    if (!child)
                        return {};
                    begin += child->getLexemCount();
                    children.push_back(child);
                } else {
                    List<Terminal, NonTerminal>* child = process_symbol(it->asNonTerminal(), begin, end);
                    if (!child)
                        return {};
                    begin += child->getLexemCount();
                    children.push_back(child);
                }
            }
            return children;
        }

        Atom<Terminal, NonTerminal>* process_lexem(Terminal target,
                                         typename std::vector<Lexem>::iterator begin,
                                         typename std::vector<Lexem>::iterator end) const {
            if (begin == end)
                return nullptr;
            Lexem& lexem = *begin;
            if (lexem.getToken() == target)
                return new Atom<Terminal, NonTerminal>(lexem.getString(), lexem.getToken());
            return nullptr;
        }

    public:
        ParserTopDown(std::vector<Production<Terminal, NonTerminal>> grammar) :
            Parser<Terminal, NonTerminal, Lexem>(grammar) {}

        List<Terminal, NonTerminal>* process_symbol(NonTerminal target,
                            typename std::vector<Lexem>::iterator begin,
                            typename std::vector<Lexem>::iterator end) const {
            for (auto it = this->productions.at(target).branches.begin();
                 it != this->productions.at(target).branches.end(); ++it) {
                auto result = process_branch(*it, begin, end);
                if (result.size() > 0)
                    return new List<Terminal, NonTerminal>(target, result);
            }
            return nullptr;
        }
};

#endif
