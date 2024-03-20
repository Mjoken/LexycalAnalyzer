#include "ModulesAndFunc.h"

int main() {
    try {
        std::vector<Lexem> table_lexem;
        const std::string filename = "input.txt";

        Analyzer lex_analazer(filename);

        if (lex_analazer.Analizator(table_lexem) == 0) {
            std::cout << "Succsess!" << std::endl;
        }
        else {
            std::cout << "Error!" << std::endl;
        }
        std::cout << "Number\t\tLexem\t\tTypeLexem" << std::endl;
        for (size_t i = 0; i < table_lexem.size(); i++)
        {
            std::cout << (i + 1) << ":" "\t\t" << table_lexem[i].value << "\t\t" << lex_analazer.get_string_type(table_lexem[i].type) << std::endl;;
        }
        return 0;
    }
    catch (const char* error_message) {
        std::cout << "Error:\t" << error_message << std::endl;
        return -1;
    }
}
