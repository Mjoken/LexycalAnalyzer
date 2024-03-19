#include "ModulesAndFunc.h"

Analyzer::Analyzer()
{
    this->path = "input.txt";
    this->file.open(this->path);
    if (!this->file.is_open()) {
        throw "File can't be open";
    }
}

Analyzer::Analyzer(std::string path)
{
    this->path = path;
    this->file.open(this->path);
    if (!this->file.is_open()) {
        throw "File can't be open";
    }
}

void Analyzer::set_path(std::string path)
{
    this->path = path;
}

void Analyzer::openfile()
{
    this->file.open(this->path);
    if (!this->file.is_open()) {
        throw "File can't be open";
    }
}

void Analyzer::openfile(std::string path)
{
    this->path = path;
    this->file.open(this->path);
    if (!this->file.is_open()) {
        throw "File can't be open";
    }
}
/*
* if lexem in keyword return keyword else return null
*/
std::string Analyzer::lexem_keyword(std::string lexem)
{
    return *this->lexem.find(lexem);
}
