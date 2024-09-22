#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <string>
#include <vector>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::string parseToHtml();

private:
    std::vector<Token> tokens;
    size_t current;

    std::string parseHeader();
    std::string parseText();
    std::string parseBold();
    std::string parseItalic();
    std::string parseLink();
    std::string parseImage();
    std::string parseCode();
    
    Token advance();
    Token peek() const;
    bool isAtEnd() const;
};

#endif // PARSER_H