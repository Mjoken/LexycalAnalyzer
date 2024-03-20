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

Analyzer::~Analyzer()
{
    if (this->file.is_open()) {
        this->file.close();
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

std::string Analyzer::get_string_type(lexem_type name)
{
    {
        switch (name)
        {
        case KEYWORD:
            return "KEYWORD";
        case IDENTIFICATOR:
            return "IDENTIFICATOR";
        case NUMBER:
            return "NUMBER";
        case OPERATOR:
            return "OPERATOR";
        case SEPARATOR:
            return "SEPARATOR";
        default:
            return "default";
        }
    }
}

int Analyzer::Analizator(std::vector<Lexem> &lexem_table)
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
    std::string lexem(" ");

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
            }
                if (cur_sym == 'X' || cur_sym == 'V' || cur_sym == 'I') {
                    state = NUM;
                }
                else if (((cur_sym >= 'A') && (cur_sym <= 'Z')) 
                        || ((cur_sym >= 'a') && (cur_sym <= 'z')) 
                        || (cur_sym == '_')) {
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
        // end of CASE START
        case IDEN:
        //CASE IDEN
            lexem = "";
            lexem += cur_sym;

            cur_sym = this->file.get();
            number_symbol++;

            while ((((cur_sym >= 'A') && (cur_sym <= 'Z'))
                || ((cur_sym >= 'a') && (cur_sym <= 'z'))
                || (cur_sym == '_'))) {
                
                if (lexem.length() > 64) break;
                lexem += cur_sym;
                cur_sym = this->file.get();
            }

            if (lexem.length() > 64) break;
            
            *(lexem.end()-1) = '\0';

            if (is_keyword(lexem))
                cur_lexem.type = KEYWORD;
            else
                cur_lexem.type = IDENTIFICATOR;

            if (flag_id_with_number == true)
            {
                cur_lexem.value = buff_id_with_number;
                cur_lexem.value += lexem;

                flag_id_with_number = false;
                buff_id_with_number = "";
            }
            else
            {
                cur_lexem.value = lexem;
            }

            lexem_table.push_back(cur_lexem);

            state = START;
            break;
        // end of CASE IDEN
        case NUM:
            
            lexem = "";
            lexem += cur_sym;

            cur_sym = this->file.get();
            number_symbol++;

            while (cur_sym == 'X' || cur_sym == 'V' || cur_sym == 'I')
            {
                if (lexem.length() > 64) break;
                
                *(lexem.end() - 1) = cur_sym;
                lexem += cur_sym;
                cur_sym = this->file.get();
            }

            if (lexem.length() > 64) break;

            *(lexem.end() - 1) = '\0';

            cur_lexem.type = NUMBER;
            cur_lexem.value = lexem;

            if (((cur_sym >= 'A') && (cur_sym <= 'Z')) ||
               ((cur_sym >= 'a') && (cur_sym <= 'z')) ||
               (cur_sym == '_')) {
                    state = IDEN;
                    flag_id_with_number = true;
                    buff_id_with_number = lexem;
                    break;
            }

            lexem_table.push_back(cur_lexem);
            state = START;

            break;

        case ASSIGN:
            cur_sym = this->file.get();
            number_symbol++;

            if (cur_sym == '=')
            {
                cur_lexem.type = OPERATOR;
                cur_lexem.value = ":=";

                lexem_table.push_back(cur_lexem);

                cur_sym = this->file.get();
                number_symbol++;

                state = START;
            }
            else
                state = ERROR;
        break;

        case SPR:
            cur_lexem.type = SEPARATOR;

            cur_lexem.value = cur_sym;

            lexem_table.push_back(cur_lexem);

            cur_sym = this->file.get();
            number_symbol++;

            state = START;

        break;

        case CONDITIONS:
        
            if (cur_sym == '=' || cur_sym == '!')
            {
                cur_lexem.type = OPERATOR;
                cur_lexem.value = cur_sym;

                cur_sym = this->file.get();
                number_symbol++;

                if (cur_sym != '=')
                {
                    state = ERROR;
                    break;
                }

                lexem_table.push_back(cur_lexem);
            }
            else if ((cur_sym == '<') || (cur_sym == '>'))
            {
                cur_lexem.type = OPERATOR;

                cur_lexem.value = cur_sym;

                cur_sym = this->file.get();
                number_symbol++;

                lexem_table.push_back(cur_lexem);

                state = START;
            }

            break;
        case ARIFM:

            cur_lexem.type = OPERATOR;

            cur_lexem.value = cur_sym;

            cur_sym = this->file.get();
            number_symbol++;

            if (cur_sym == '*' || cur_sym == '/')
            {
                state = COM;
                break;
            }

            lexem_table.push_back(cur_lexem);

            state = START;

            break;
        case COM:
            
            if (cur_sym == '*')
            {
                cur_sym = this->file.get();

                while (true)
                {
                    while (cur_sym != '*')
                    {
                        if (cur_sym == '\n')
                        {
                            number_line++;
                            number_symbol = 0;
                        }

                        cur_sym = this->file.get();
                        number_symbol++;
                    }

                    cur_sym = this->file.get();
                    number_symbol++;

                    if (cur_sym == '\n')
                    {
                        number_line++;
                        number_symbol = 0;
                    }

                    if (cur_sym == '/') break;

                    cur_sym = this->file.get();
                    number_symbol++;
                }
            }
            // Маленький комментарий
            else
            {
                while (cur_sym != '\n' && !this->file.eof())
                {
                    cur_sym = this->file.get();
                    number_symbol++;
                }

                number_line++;
                number_symbol = 0;

            }

            state = START;
            cur_sym = this->file.get();
            number_symbol++;

            break;
        case ERROR:

            std::cout << "Error in the line:" << number_line << "   number symbol:" << number_symbol << std::endl;

            state = START;

            while ((cur_sym != ' ') && (cur_sym != '\t') && (cur_sym != '\n'))
            {
                if (cur_sym == '\n')
                {
                    number_line++;
                    number_symbol = 0;
                }

                cur_sym = this->file.get();
                number_symbol++;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
