#ifndef COMPILER_CODEGENERATOR_H
#define COMPILER_CODEGENERATOR_H

#include <string>
#include <list>

class CodeSnippet {
public:
    std::string command;
    std::string label;
    std::string firstValue;
    std::string secondValue;
    std::string commentary;
    CodeSnippet *next;

    CodeSnippet(std::string);

    CodeSnippet(int, std::string);

    CodeSnippet(std::string, int);

    CodeSnippet(std::string, std::string);

    CodeSnippet(int, std::string, int);

    CodeSnippet(std::string, int, int);

    CodeSnippet(int, std::string, int, int);
};

class CodeGenerator {
private:
    CodeSnippet *head;

    std::string addSpaces(std::string, int);

public:
    CodeGenerator();

    void insertNode(CodeSnippet *);

    void printList();

    void generateCodeList();

    void generateCode();

    std::list<CodeSnippet> deleteCode();
};


#endif //COMPILER_CODEGENERATOR_H
