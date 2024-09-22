#include "lexer.h"

Lexer::Lexer(const std::string& input) : input(input), position(0) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (!isAtEnd()) {
        //helper method that checks if the lexer has reached the end of the input or ont (iam jsut new in cpp)
        skipWhitespace();
        if (isAtEnd()) break;

        char current = peek();
        switch (current) {
            case '#':
                tokens.push_back(handleHeader());
                break;
            case '*':
            case '_':
                tokens.push_back(handleBoldOrItalic());
                break;
            case '[':
            case '!':
                tokens.push_back(handleLinkOrImage());
                break;
            case '`':
                tokens.push_back(handleCode());
                break;
            case '\n':
                tokens.push_back(createToken(TokenType::NEWLINE, "\n"));
                advance();
                break;
            case '\r':
                if (peek() == '\n') {
                    tokens.push_back(createToken(TokenType::EOL, "\r\n"));
                    advance();
                    advance();
                } else {
                    tokens.push_back(handleText());
                }
                break;
            default:
                tokens.push_back(handleText());
                break;
        }
    }
    tokens.push_back(createToken(TokenType::EOF, ""));
    return tokens;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return input[position];
}

char Lexer::advance() {
    return input[position++];
}

bool Lexer::isAtEnd() const {
    return position >= input.length();
}

Token Lexer::createToken(TokenType type, const std::string& value) {
    return {type, value};
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peek()) && peek() != '\n' && peek() != '\r') {
        advance();
    }
}


Token Lexer::handleHeader() {
    std::string value;
    while (peek() == '#') {
        value += advance();
    }
    return createToken(TokenType::HEADER, value);
}

Token Lexer::handleText() {
    std::string value;
    // just continue untill next special char is met (or newline)
    while (!isAtEnd() && peek() != '\n' && peek() != '\r' && peek() != '*' && peek() != '_' && peek() != '[' && peek() != '`') {
        value += advance();
    }
    return createToken(TokenType::TEXT, value);
}

Token Lexer::handleBoldOrItalic() {
    char marker = advance(); // * or _
    if (peek() == marker) {
        advance();
        return createToken(TokenType::BOLD, std::string(2, marker));
    }
    return createToken(TokenType::ITALIC, std::string(1, marker));
}

Token Lexer::handleLinkOrImage() {
    bool isImage = false;
    if (peek() == '!') {
        isImage = true;
        advance();
    }
    
    std::string value = "[";
    advance(); 
    
    while (!isAtEnd() && peek() != ']') {
        value += advance();
    }
    
    if (isAtEnd()) return createToken(TokenType::TEXT, value);
    
    value += advance(); 
    
    if (peek() == '(') {
        value += advance(); 
        
        while (!isAtEnd() && peek() != ')') {
            value += advance();
        }
        
        if (!isAtEnd()) {
            value += advance(); 
        }
    }
    
    return createToken(isImage ? TokenType::IMAGE : TokenType::LINK, value);
}

Token Lexer::handleCode() {
    std::string value;
    advance(); 
    
    while (!isAtEnd() && peek() != '`') {
        value += advance();
    }
    
    if (!isAtEnd()) {
        advance(); 
    }
    
    return createToken(TokenType::CODE, value);
}