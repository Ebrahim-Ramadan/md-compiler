#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <string>

int main() {
    std::string markdown;
    std::string line;
    
    std::cout << "type your md text (press Ctrl+D on a new line to finish):\n";
    while (std::getline(std::cin, line)) {
        markdown += line + "\n";
    }
    
    Lexer lexer(markdown);
    std::vector<Token> tokens = lexer.tokenize();
    
    Parser parser(tokens);
    std::string html = parser.parseToHtml();
    
    std::cout << "\nGenerated HTML:\n" << html << std::endl;
    
    return 0;
}