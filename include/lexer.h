#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum TokenType {
    HEADER, // #
    TEXT,   // Regular text
    BOLD,   // **
    ITALIC, // *
    LINK,   // [text](url)
    IMAGE,  // ![alt](url)
    CODE,   // `code`
    NEWLINE, // \n
    EOL,    // \r\n
    EOF     // End of file
};

struct Token {
    TokenType type;
    std::string value;
};
