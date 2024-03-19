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

bool Analyzer::is_keyword(std::string lexem)
{
    return !(this->lexem.find(lexem) == this->lexem.end());
}

int Analyzer::Analizator(std::vector<Lexem> lexem_table)
{   
    // Для вывода сообщения, о расположение ошибки
    int number_line = 1;
    int number_symbol = 0;

    // Переменные, для того, чтобы корректно обрабатывать лексемы 
    // начинающие с римских цифр, являющиемися идентификаторами
    bool flag_id_with_number = false;
    std::string buff_id_with_number = "";

    // Текущий обрабатываемый символ
    char cur_sym;

    // текущая лексема
    Lexem cur_lexem;
    
    if (!this->file.is_open()) {
        throw "File don't open";
        return -1;
    }

    state_type state = START;

    cur_sym = this->file.get();
    number_symbol++;
    while(!this->file.eof()) {
        switch (state)
        {
        case START:
        //CASE START
            while ((cur_sym == ' ') || (cur_sym == '\t') || cur_sym == '\n') {
                if (cur_sym == '\n') {
                    number_line++;
                    number_symbol = 0;
                }
                cur_sym = this->file.get();
                number_symbol++;
                if (cur_sym == 'X' || cur_sym == 'V' || cur_sym == 'I') {
                    state = NUM;
                }
                else if (((cur_sym >= 'A') && (cur_sym <= 'Z')) || ((cur_sym >= 'a') && (cur_sym <= 'z')) || (cur_sym == '_')) {
                    state = IDEN;
                }
                else if (cur_sym == '+' || cur_sym == '-' || cur_sym == '*' ||
                    cur_sym == '/' || cur_sym == '%')
                {
                    state = ARIFM;
                }
                else if (cur_sym == ':')
                {
                    state = ASSIGN;
                }
                else if (cur_sym == '(' || cur_sym == ')' || cur_sym == ';' ||
                    cur_sym == '{' || cur_sym == '}')
                {
                    state = SPR;
                }
                else if (cur_sym == '<' || cur_sym == '>' || cur_sym == '=' ||
                    cur_sym == '!')
                {
                    state = CONDITIONS;
                }
                else
                {
                    state = ERROR;
                }
                break;
            }
        // end of CASE START
        case IDEN:

            int size_iden;

            size_iden = 0;

            char lexem_iden[32];

            lexem_iden[size_iden] = cur_sym;
            size_iden++;

            cur_sym = this->file.get();
            number_symbol++;

        }
    }
}
