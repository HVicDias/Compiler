#include <string>
#include <iostream>
#include <utility>
#include "symbolTable.h"

SymbolNode::SymbolNode() {
    identifier = "";
    scope = "";
    type = "";
    lineNo = -1;
    next = nullptr;
}

// Parameterised Constructor
SymbolNode::SymbolNode(std::string identifier, std::string scope, std::string type, int lineNo) {
    this->identifier = std::move(identifier);
    this->scope = std::move(scope);
    this->type = std::move(type);
    this->lineNo = lineNo;
    this->next = nullptr;
}

SymbolList::SymbolList() { symbolNode = nullptr; }

void SymbolList::deleteNode(int nodeIndex) {
    SymbolNode *currentNode = symbolNode, *auxList = nullptr;
    int ListLen = 0;

    if (symbolNode == nullptr) {
        std::cout << "List empty." << std::endl;
        return;
    }

    while (currentNode != nullptr) {
        currentNode = currentNode->next;
        ListLen++;
    }

    if (ListLen < nodeIndex) {
        std::cout << "Index out of range" << std::endl;
        return;
    }

    currentNode = symbolNode;

    if (nodeIndex == 1) {
        symbolNode = symbolNode->next;
        delete currentNode;
        return;
    }

    while (nodeIndex-- > 1) {
        auxList = currentNode;
        currentNode = currentNode->next;
    }

    auxList->next = currentNode->next;

    delete currentNode;
}

void SymbolList::insertNode(std::string identifier, std::string scope, std::string type, int lineNo) {
    auto *newNode = new SymbolNode(std::move(identifier), std::move(scope), std::move(type), lineNo);

    if (symbolNode == nullptr) {
        symbolNode = newNode;
        return;
    }

    SymbolNode *auxNode = symbolNode;
    while (auxNode->next != nullptr) {
        auxNode = auxNode->next;
    }

    // Insert at the last.
    auxNode->next = newNode;
}

void SymbolList::printList() {
    SymbolNode *auxNode = symbolNode;

    // Check for empty list.
    if (symbolNode == nullptr) {
        std::cout << "List empty" << std::endl;
        return;
    }

    std::cout << "Identifier" << "\tScope" << "\tType" << "\tLineNumber" << std::endl;
    while (auxNode != nullptr) {
        std::cout << auxNode->identifier << " : " << auxNode->scope << " : " << auxNode->type << " : "
                  << auxNode->lineNo
                  << std::endl;
        auxNode = auxNode->next;
    }
}

SymbolListNode::SymbolListNode(std::string layerName, std::string identifier, std::string scope, std::string type,
                               int lineNo)
        : SymbolList() {
    previous = nullptr;
    this->layerName = layerName;
    symbolNode = new SymbolNode(identifier, scope, type, lineNo);
}

SymbolTable::SymbolTable() {
    symbolListNode = nullptr;
}

void SymbolTable::insertSymbol(std::string identifier, std::string scope, std::string type, int lineNo) {
    if (symbolListNode != nullptr) {
        symbolListNode->insertNode(identifier, scope, type, lineNo);
    } else {
        std::cout << "SymbolTable Head is null" << std::endl;
        exit(1);
    }
}

void
SymbolTable::downLayer(std::string layerName, std::string identifier, std::string scope, std::string type, int lineNo) {
    SymbolListNode *newNode = new SymbolListNode(layerName, identifier, scope, type, lineNo);
    newNode->previous = symbolListNode;
    symbolListNode = newNode;
}

SymbolNode *SymbolTable::searchSymbol(std::string lexema) {
    SymbolListNode *currentNode = symbolListNode;
    SymbolNode *currentSymbol;

    if (currentNode == nullptr) {
        std::cout << "SymbolTable Head is null" << std::endl;
        exit(1);
    }

    while (currentNode != nullptr) {
        currentSymbol = currentNode->symbolNode;

        while (currentSymbol != 0) {
            if (currentSymbol->identifier == lexema) {
                return currentSymbol;
            }
            currentSymbol = currentSymbol->next;
        }

        currentNode = currentNode->previous;
    }

    return nullptr;
}

SymbolNode *SymbolTable::searchScopeSymbol(std::string lexema, std::string scope) {
    SymbolListNode *currentNode = symbolListNode;
    SymbolNode *currentSymbol;

    if (currentNode == nullptr) {
        std::cout << "SymbolTable Head is null" << std::endl;
        exit(1);
    }

    while (currentNode != nullptr) {
        currentSymbol = currentNode->symbolNode;

        if (currentNode->layerName == scope) {
            while (currentSymbol != 0) {
                if (currentSymbol->identifier == lexema) {
                    return currentSymbol;
                }
                currentSymbol = currentSymbol->next;
            }
            return nullptr;
        }

        currentNode = currentNode->previous;
    }

    return nullptr;
}

SymbolNode *SymbolTable::searchLocalSymbol(std::string lexema) {
    SymbolListNode *currentNode = symbolListNode;
    SymbolNode *currentSymbol;

    if (currentNode == nullptr) {
        std::cout << "SymbolTable Head is null" << std::endl;
        exit(1);
    }

    currentSymbol = currentNode->symbolNode;


    while (currentSymbol != 0) {
        if (currentSymbol->identifier == lexema) {
            return currentSymbol;
        }
        currentSymbol = currentSymbol->next;
    }
    return nullptr;
}

void SymbolTable::printList() {
    SymbolListNode *auxNode = symbolListNode;
    int leafs = 0;

    // Check for empty list.
    if (symbolListNode == nullptr) {
        std::cout << "Empty Tree" << std::endl;
        return;
    }

    std::cout << "\nCurrent Head: " << auxNode->layerName << std::endl;
    std::cout << "\nHead Info:  " << auxNode->symbolNode->identifier << " : " << auxNode->symbolNode->scope << " : "
              << auxNode->symbolNode->type << " : " << auxNode->symbolNode->lineNo << std::endl;
    while (auxNode != nullptr) {
        auxNode->printList();
        std::cout << "\nHead Info " << auxNode->symbolNode->identifier << " : " << auxNode->symbolNode->scope << " : "
                  << auxNode->symbolNode->type << " : " << auxNode->symbolNode->lineNo << std::endl;
        auxNode = auxNode->previous;
        leafs++;
    }
}

void SymbolTable::deleteLayer() {
    SymbolListNode *currentNode = symbolListNode;

    if (currentNode == nullptr) {
        std::cout << "List empty." << std::endl;
        return;
    }

    symbolListNode = symbolListNode->previous;
    delete currentNode;
}
