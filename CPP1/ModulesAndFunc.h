#pragma once
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>

enum state_type { START, IDEN, NUM, ASSIGN, ARIFM, COM, CONDITION, ERROR };
enum lexem_type { KEYWORD, IDENTIDICATOR, NUMBER, OPERATOR, SEPARATOR };

class Lexem
{
public:
    int id;
    lexem_type type;
    std::string value;
    Lexem(int id, lexem_type type, std::string value) {
        this->id = id;
        this->type = type;
        this->value = value;
    }
    
};
class Analyzer {
private:
    std::string path;
    std::ifstream file;
    std::multiset<std::string> lexem = { "if", "then", "else", "int", "float"};

public:
    Analyzer();
    Analyzer(std::string path);
    void set_path(std::string path);
    void openfile();
    void openfile(std::string path);
    std::string lexem_keyword(std::string lexem);

    

};
int Analizator(std::string filename, std::vector<Lexem> lexem_table);


