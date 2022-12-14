#ifndef COMPILER_LEXICALANALYSER_H
#define COMPILER_LEXICALANALYSER_H

#include <string>
#include "linkedList.h"
#include "semanticAnalyser.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

extern char character;

bool isSpace();

bool isCommentary();

bool isDigit();

bool isLetter();

bool isUnderscore();

bool isArithmeticOperator();

bool isRelationalOperator();

bool isPunctuation();

void jumpSpaces(FILE *file);

bool jumpLastSpaces(FILE *file);

void jumpComentary(FILE *file, Ui::MainWindow *);

bool jumpLastComentary(FILE *file, Ui::MainWindow *);

Node handleDigit(FILE *file, Ui::MainWindow *);

Node handleIdAndSpecialWord(FILE *file, Ui::MainWindow *);

Node handleAttribution(FILE *file);

Node handleArithmeticOperator(FILE *file);

Node handleRelationalOperator(FILE *file);

Node handlePunctuation(FILE *file);

Node getToken(FILE *file, Ui::MainWindow *);

bool getLastToken(FILE *file, Ui::MainWindow *);

#endif //COMPILER_LEXICALANALYSER_H
