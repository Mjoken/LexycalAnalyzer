#include "Lexer.h"

int main() {
    try {
        std::list<Lexem> table_lexem;
        const std::string filename = "input.txt";
        int count = 0;
        Analyzer lex_analazer(filename);

        if (lex_analazer.Analizator(table_lexem) == 0) {
            std::cout << "Succsess!" << std::endl;
        }
        else {
            std::cout << "Error!" << std::endl;
        }
        if (!table_lexem.empty()) {
            std::cout << "Number\t\tLexem\t\tTypeLexem" << std::endl;
        }
        for (Lexem n: table_lexem)
        {
            
            std::cout << ++count << ":" "\t\t" << n.value << "\t\t" << lex_analazer.get_string_type(n.type) << std::endl;
        }
        return 0;
    }
    catch (const char* error_message) {
        std::cout << "Error:\t" << error_message << std::endl;
        return -1;
    }
}
