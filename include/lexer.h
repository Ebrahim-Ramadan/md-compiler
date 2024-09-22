#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
    HEADER,  // #
    TEXT,    // regular txt
    BOLD,    // **
    ITALIC,  // *
    LINK,    // [txt](url)
    IMAGE,   // ![alt](url)
    CODE,    // `code`
    NEWLINE, // \n
    EOL,     // \r\n
    EOF      // End Of File
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t position;

    char peek() const;
    char advance();
    bool isAtEnd() const;
    Token createToken(TokenType type, const std::string& value);
    void skipWhitespace();
    Token handleHeader();
    Token handleText();
    Token handleBoldOrItalic();
    Token handleLinkOrImage();
    Token handleCode();
};

#endif // LEXER_H