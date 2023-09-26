#ifndef LIBPARSER_PARSER_CLR_HH
#define LIBPARSER_PARSER_CLR_HH

#include <libparser/parser.hh>
#include <libparser/node.hh>
#include <libparser/atom.hh>
#include <libparser/list.hh>
#include <iostream>

template <typename Terminal, typename NonTerminal, typename Lexem>
class ParserCLR : public Parser<Terminal, NonTerminal, Lexem> {
    private:
        bool tryReduce(std::vector<Node<Terminal, NonTerminal>*>* queue) {
            for (auto production : this->productions) {
                for (auto branch : production.branches) {
                    if (matchBranchToQueue(queue, &branch)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool matchBranchToQueue(std::vector<Node<Terminal, NonTerminal>*>* queue,
                                std::vector<Symbol<Terminal, NonTerminal>>* branch) {
            auto qIt = queue->end() - 1;
            auto bIt = branch->end() - 1;
            auto qBegin = queue->begin();
            auto bBegin = branch->begin();
            while(qIt != qBegin && bIt != bBegin) {
                if (! compareSymbolAndQueue(*qIt, *bIt))
                    return false;
                qIt--;
                bIt--;
            }
            return true;
        }

        bool compareSymbolAndQueue(Node<Terminal, NonTerminal>* ptr,
                                   Symbol<Terminal, NonTerminal>& symbol) {
            return false;
        }

    public:
        ParserCLR(std::vector<Production<Terminal, NonTerminal>> grammar) :
            Parser<Terminal, NonTerminal, Lexem>(grammar) {}
        
        List<Terminal, NonTerminal>* process(NonTerminal target,
                                  typename std::vector<Lexem>::iterator begin,
                                  typename std::vector<Lexem>::iterator end) {
            std::cout << "process-target :: " << target << std::endl;
            auto it = begin;
            std::vector<Node<Terminal, NonTerminal>*> queue = {};
            while (it != end) {
                auto lexem = *(it++);
                std::cout << "load-lexem :: " << lexem.toString() << std::endl;
                queue.push_back(new Atom<Terminal, NonTerminal>(lexem.getString(), lexem.getToken()));
            }
            
            if (queue.size() != 1) {
                for (auto node : queue) {
                    std::cout << "purge-node :: " << node->toString() << std::endl;
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
