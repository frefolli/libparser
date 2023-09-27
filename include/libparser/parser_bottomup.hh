#ifndef LIBPARSER_PARSER_BOTTOMUP_HH
#define LIBPARSER_PARSER_BOTTOMUP_HH

#include <libparser/parser.hh>
#include <libparser/node.hh>
#include <libparser/atom.hh>
#include <libparser/list.hh>
#include <iostream>

template <typename Terminal, typename NonTerminal, typename Lexem>
class ParserBottomUp : public Parser<Terminal, NonTerminal, Lexem> {
    private:
        bool tryReduce(std::vector<Node<Terminal, NonTerminal>*>* queue) {
            for (auto production : this->productions) {
                for (auto branch : production.second.branches) {
                    if (matchBranchToQueue(queue, &branch, production.first)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool matchBranchToQueue(std::vector<Node<Terminal, NonTerminal>*>* queue,
                                std::vector<Symbol<Terminal, NonTerminal>>* branch,
                                NonTerminal target) {
            if (branch->size() == 0 || queue->size() == 0)
                return false;
            if (branch->size() > queue->size())
                return false;

            auto qIt = queue->end() - 1;
            auto bIt = branch->end() - 1;
            auto qBegin = queue->begin() - 1;
            auto bBegin = branch->begin() - 1;
            while(qIt != qBegin && bIt != bBegin) {
                if (! compareSymbolAndQueue(*qIt, *bIt)) {
                    return false;
                }
                qIt--;
                bIt--;
            }
            
            if (bIt == bBegin) {
                auto qEnd = queue->end();
                spliceQueue(target, queue, std::distance(qIt, qEnd) - 1);
                return true;
            }
            return false;
        }

        bool compareSymbolAndQueue(Node<Terminal, NonTerminal>* node,
                                   Symbol<Terminal, NonTerminal>& symbol) {
            if (symbol.isTerminal) {
                if (! node->isAtom()) {
                    return false;
                }
                Atom<Terminal, NonTerminal>* atom = (Atom<Terminal, NonTerminal>*) node; 
                return atom->getTerminal() == symbol.asTerminal();
            } else {
                if (! node->isList()) {
                    return false;
                }
                List<Terminal, NonTerminal>* list = (List<Terminal, NonTerminal>*) node; 
                return list->getHead() == symbol.asNonTerminal();
            }
            return false;
        }

        void spliceQueue(NonTerminal target,
                         std::vector<Node<Terminal, NonTerminal>*>* queue,
                         unsigned int length) {
            std::vector<Node<Terminal, NonTerminal>*> children = {};
            for (unsigned int i = 0; i < length; i++) {
                children.insert(children.begin(), queue->back());
                queue->pop_back();
            }
            queue->push_back(new List<Terminal, NonTerminal>(target, children));
        }

    public:
        ParserBottomUp(std::vector<Production<Terminal, NonTerminal>> grammar) :
            Parser<Terminal, NonTerminal, Lexem>(grammar) {}
        
        List<Terminal, NonTerminal>* process(NonTerminal target,
                                  typename std::vector<Lexem>::iterator begin,
                                  typename std::vector<Lexem>::iterator end) {

            auto it = begin;
            std::vector<Node<Terminal, NonTerminal>*> queue = {};
            while (it != end) {
                while(tryReduce(&queue));
                auto lexem = *(it++);

                queue.push_back(new Atom<Terminal, NonTerminal>(lexem.getString(), lexem.getToken()));
                while(tryReduce(&queue));
            }
            
            if (queue.size() != 1) {
                for (auto node : queue) {
                    delete node;
                }
                return nullptr;
            }

            if (! queue[0]->isList()) {
                delete queue[0];
                return nullptr;
            }

            List<Terminal, NonTerminal>* list = (List<Terminal, NonTerminal>*) queue[0];
            if (list->getHead() != target) {
                delete list;
                return nullptr;
            }

            return list;
        }
};

#endif
