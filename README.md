# Open Discussion on LibParser

## Target

This will probably be a header-only library to let the user free to choose his abstractions.

## Actual Discussion

Parsers have productions in BNF, with Symbols both Terminals and NonTerminals
Basically a BNF, in formal regular expression is something like this: `<non-terminal> := <symbol> ... [| <symbol> ...]*`
The branches can be evaluated from left to right or reverse, it doesn't matter untill it's coherent in the grammar.
First of all we represent Symbols:

```
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

```
struct Production {
  NonTerminal symbol;
  std::vector<std::vector<Symbol>> branches;
}
```

For a Production to be defined as VALID, it SHALL_BE:
- `branches.size() > 0`
- for_each(`branch` : `branches`)
  - `branch.size() > 0`
  - `branch[0] != symbol`

Then the parser is defined as the collection of those Production statements. Since the left symbols are always non terminals we can easely write a map instead of a vector.

```
struct Parser {
  std::map<NonTerminal, Production> productions;
  void process(std::vector<Token>::const_iterator begin,
               std::vector<Token>::const_iterator end,
               NonTerminal target) const;
}
```

There aren't much constraints over a Parser, since the START symbol is given with the input. This is done specifically to have a first type of recursion, so that the START symbol is actually a TARGET symbol.
Obviously if there's no production for that symbol the search will fail, but that's how a grammar works I suppose.

The input is given as a couple of iterators representing the limits of the Token stream. The Token is a generic type passed by template deduction.
The Production could have a similar interface, even if it doesn't recieve the target for obvious reasons. The problem of this architecture tough is circual dependency between Parser and Production, which would need to pass computation to Parser in order to resolve the next symbols.

This could be avoided by letting Parser do all the work and treating the Production as an Open Struct. Nonetheless to avoid leak of pointers or mutable references, we can define some accessors which deliver const references.
