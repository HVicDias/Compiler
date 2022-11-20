#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <string>

class SymbolNode {
public:
    std::string identifier;
    std::string scope;
    std::string type;
    int lineNo;
    int label;
    int memoryAllocation;
    SymbolNode *next;

    SymbolNode(std::string, std::string, std::string, int, int, int);

    SymbolNode();
};

class SymbolList {
public:
    SymbolNode *symbolNode;

    SymbolList();

    void insertNode(std::string, std::string, std::string, int, int, int);

    void printList();

    void deleteNode(int);
};

class SymbolListNode : public SymbolList {
public:
    SymbolListNode *previous;

    std::string layerName;

    SymbolNode headNode;

    explicit SymbolListNode(std::string, std::string, std::string, std::string, int, int, int);
};

class SymbolTable {
public:
    SymbolListNode *symbolListNode;

    SymbolTable();

    void insertSymbol(std::string, std::string, std::string, int, int, int);

    void downLayer(std::string, std::string, std::string, std::string, int, int, int);

    SymbolNode *searchSymbol(std::string);

    SymbolNode *searchLocalSymbol(std::string);

    SymbolNode *searchScopeSymbol(std::string, std::string);

    SymbolNode changeHeadNodeLabel(int, std::string);

    void printList();

    int deleteLayer();
};

#endif //COMPILER_SYMBOLTABLE_H
