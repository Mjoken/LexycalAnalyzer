#pragma once
#include <ctime>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <list>
#include "IdentidicatorTable.h"
#define SIZE_HASHTABLE 10

enum state_type { START, IDEN, NUM, ASSIGN, ARIFM, SPR, COM, CONDITIONS, ERROR };
enum lexem_type { KEYWORD, IDENTIFICATOR, NUMBER, OPERATOR, SEPARATOR, LEXERROR };
//int level = 0;
class Lexem
{
public:
    int id;
    lexem_type type;
    std::string value;
    Lexem() {
        this->id = 0;
        this->value = "";
    }
    Lexem(int id, lexem_type type, std::string value) {
        this->id = id;
        this->type = type;
        this->value = value;
    }
    ~Lexem() {}
};
class Analyzer {
private:
    std::string path;
    std::ifstream file;
    std::multiset<std::string> lexem = { "if", "then", "else", "int", "float", "double"};

public:

    IdentidicatorTable* idenTable = nullptr;

    Analyzer();
    Analyzer(std::string path);
    ~Analyzer();
    void set_path(std::string path);
    void openfile();
    void openfile(std::string path);
    std::string lexem_keyword(std::string lexem);
    bool is_keyword(std::string lexem);
    std::string get_string_type(lexem_type name);
    int Analizator(std::list<Lexem>& lexem_table);
    
};



