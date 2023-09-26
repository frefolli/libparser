#ifndef LIBPARSER_PARSER_CLR_HH
#define LIBPARSER_PARSER_CLR_HH

#include <libparser/parser.hh>
#include <libparser/node.hh>
#include <libparser/atom.hh>
#include <libparser/list.hh>

template <typename Terminal, typename NonTerminal, typename Lexem>
class ParserCLR : public Parser<Terminal, NonTerminal, Lexem> {
    private:
        bool tryReduce(std::vector<void*>* queue) {
            for (auto production : this->productions) {
                for (auto branch : production.branches) {
                    if (matchBranchToQueue(queue, &branch)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool matchBranchToQueue(std::vector<void*>* queue,
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

        bool compareSymbolAndQueue(void* ptr,
                                   Symbol<Terminal, NonTerminal>& symbol) {
            if (Lexem* lexem = dynamic_cast<Lexem*>(ptr)) {
                if (!symbol.isTerminal)
                    return false;
                return symbol.getTerminal() == lexem->getToken();
            } else if (Node<NonTerminal>* node = dynamic_cast<Node<NonTerminal>*>(ptr)) {
                if (symbol.isTerminal)
                    return false;
                if (node.isAtom())
                    return false;
                List<NonTerminal>* list = (List<NonTerminal>*) node;
                return symbol.getNonTerminal() == list->getHead();
            }
            return false;
        }

    public:
        ParserCLR(std::vector<Production<Terminal, NonTerminal>> grammar) :
            Parser<Terminal, NonTerminal, Lexem>(grammar) {}
        
        List<NonTerminal>* process(NonTerminal target,
                                  typename std::vector<Lexem>::iterator begin,
                                  typename std::vector<Lexem>::iterator end) {
            auto it = begin;
            std::vector<void*> queue = {};
            while (it != end) {
                queue.push_back(*(begin++));
            }
            
            if (queue.size() != 1) {
                for (auto ptr : queue) {
                    if (Lexem* lexem = dynamic_cast<Lexem*>(ptr)) {
                        delete lexem;
                    } else if (Node<NonTerminal>* node = dynamic_cast<Node<NonTerminal>*>(ptr)) {
                        delete node;
                    }
                }
                return nullptr;
            }
            return queue[0];
        }
};

#endif
