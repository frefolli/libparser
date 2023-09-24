# Open Discussion on LibParser

## Target

This will probably be a header-only library to let the user free to rely on his owns abstractions.

## Dependencies

The library will depend upon the following INPUT abstractions from the Lexer part:
- `Token`
- `Lexem<Token>`

Eagerly we state `typedef Token Terminal`;

and from those for the Parser part:
- `NonTerminal`

## Actual Discussion

Parsers have productions in BNF, with Symbols both Terminals and NonTerminals. A parser accepts or rejects a stream of Lexems, which contain a string representing a piece of source code for sure, but also Tokens, which are LITERALLY the same thing as Terminals.
Basically a BNF, in formal regular expression is something like this: `<non-terminal> := <symbol> ... [| <symbol> ...]*`.
The branches can be evaluated from left to right or reverse, it doesn't matter untill it's coherent in the grammar.
First of all we represent Symbols:

```c++
union SymbolType {
  NonTerminal symbolNT;
  Terminal symbolT;
}

struct Symbol {
  SymbolType type;
  bool isTerminal;
}
```

Since the union stays in memories as the biggest of the two types declared, these must be chosen wisely.
That reduces the BNF form to this:

```c++
struct Production {
  Symbol symbol;
  std::vector<std::vector<Symbol>> branches;
}
```

For a Production to be defined as VALID, it SHALL_BE:
- `! Symbol.isTerminal`
- `branches.size() > 0`
- for_each(`branch` : `branches`)
  - `branch.size() > 0`
  - `branch[0] != symbol`

Then the parser is defined as the collection of those Production statements. Since the left symbols are always non terminals we can easely write a map instead of a vector.

```c++
struct Parser {
  std::map<NonTerminal, Production> productions;
  void process(std::vector<Lexem>::const_iterator begin,
               std::vector<Lexem>::const_iterator end,
               NonTerminal target) const;
}
```

There aren't much constraints over a Parser, since the START symbol is given with the input. This is done specifically to have a first type of recursion, so that the START symbol is actually a TARGET symbol.
Obviously if there's no production for that symbol the search will fail, but that's how a grammar works I suppose.

The input is given as a couple of iterators representing the limits of the Lexem stream. The Lexem is a generic type passed by template deduction.
The Production could have a similar interface, even if it doesn't recieve the target for obvious reasons. The problem of this architecture tough is circual dependency between Parser and Production, which would need to pass computation to Parser in order to resolve the next symbols.

This could be avoided by letting Parser do all the work and treating the Production as an Open Struct. Nonetheless to avoid leak of pointers or mutable references, we can define some accessors which deliver const references.

## The actual resolution algorithm

First of all it's usefull to define a struct which contains the result of resolution process for a target

```ruby
class Node
    def initialize
        @children = []
        @lexem_count = 0
        @head = nil
    end
end
```

We can split the procedure as such, from generic terms to specific terms:

```ruby
# f : (NonTerminal x Iterator x Iterator) -> Node
def process(target, begin, end)
    for prod in target.prods
        result = process_prod(prod, begin, end)
        if result.ok?
            result.head = target
            return result
        end
    end
    return nil
end
```

We are ready to process each production:

```ruby
# f: ([Symbol] x Iterator x Iterator) -> Node
def process_prod(symbols, begin, end)
    result = Result.new
    for symbol in symbols
        if symbol.terminal?
            child = process_lexem(symbol, begin, end)
            if child.nil?
                return nil
            end
            begin += 1
            result.children.append(child)
            result.lexem_count += 1
        else
            child = process(symbol, begin, end)
            if child.nil?
                return nil
            end
            begin += child.lexem_count
            result.children.append(child)
            result.lexem_count += child.lexem_count
        end
    end
    return result
end
```

Then each individual lexem:

```ruby
# f : (Terminal x Iterator x Iterator) -> Node
def process_lexem(symbol, begin, end)
    if begin == end
        return nil
    end
    lexem = begin.get
    if symbol.type != lexem.token
        return nil
    end
    return lexem
end
```

An user may want to exclude certain symbols (both terminal and non terminals from being appended as children. For this reason it would be great to implement a sort of `ignore` value as done with [liblexer](github.com/frefolli/liblexer), either with production rules or based on the type of Terminal/NonTerminal symbol matched as context free rule.

Also there must be an abstraction to Node for Symbols and Lexems to be mixed as children or head of a Node of CST. This could be done with the same approach of the above abstraction of Terminals and NonTerminals, but mixing unions with recursive structure isn't something that should be done with ease, so instead we're gonna resort on class and, *drumrolls*, pointers. Since at this point we don't need anymore to maintain Token indication, the match string of the Lexem can be extracted in a new abstraction to minify waste of both knowledge and memory (an union must be used).

```c++
class Node {
    protected:
        unsigned int lexemCount = 0;
    public:
        Node();
        virtual Node();
        virtual bool isAtom() = 0;
        virtual bool isList() = 0;
        virtual std::string toString() = 0;
        unsigned int getLexemCount();
};
```

```c++
// lexemCount = 1
class Atom : public Node {
    private:
        std::string string;
    public:
        Atom(std::string string);
        bool isAtom();
        bool isList();
        std::string toString();
};
```

```c++
// lexemCount = sum([node.lexemCount for node in children])
class List : public Node {
    private:
        NonTerminal head;
        std::vector<Node*> children;
    public:
        List();
        bool isAtom();
        bool isList();
        std::string toString();
        void setHead(NonTerminal head);
        void addChild(Node* child);
};
```

They could be structs instead of classes, but since we want to rely on template deduction, this is probably a better approach. We are gonna use a flag attribute instead of `dynamic_cast` though. Finally we should keep in mind that these will be parametric structures against typename `NonTerminal`.

## Compiler Tricks

- `SMART_PRODUCTION_VALIDATION` enables the `Production::validate` member function to validate a production based on assumptions.
