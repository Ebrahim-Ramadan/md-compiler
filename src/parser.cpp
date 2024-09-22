#include "parser.h"
#include <sstream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}

std::string Parser::parseToHtml() {
    std::stringstream html;
    while (!isAtEnd()) {
        Token token = advance();
        switch (token.type) {
            case TokenType::HEADER:
                html << parseHeader();
                break;
            case TokenType::TEXT:
                html << parseText();
                break;
            case TokenType::BOLD:
                html << parseBold();
                break;
            case TokenType::ITALIC:
                html << parseItalic();
                break;
            case TokenType::LINK:
                html << parseLink();
                break;
            case TokenType::IMAGE:
                html << parseImage();
                break;
            case TokenType::CODE:
                html << parseCode();
                break;
            case TokenType::NEWLINE:
            case TokenType::EOL:
                html << "<br>";
                break;
            default:
                break;
        }
    }
    return html.str();
}

std::string Parser::parseHeader() {
    int level = tokens[current - 1].value.length(); // Number of '#' characters
    std::string text = advance().value;
    return "<h" + std::to_string(level) + ">" + text + "</h" + std::to_string(level) + ">";
}

std::string Parser::parseText() {
    return tokens[current - 1].value;
}

std::string Parser::parseBold() {
    std::string text = advance().value;
    return "<strong>" + text + "</strong>";
}

std::string Parser::parseItalic() {
    std::string text = advance().value;
    return "<em>" + text + "</em>";
}

std::string Parser::parseLink() {
    size_t textStart = tokens[current - 1].value.find('[') + 1;
    size_t textEnd = tokens[current - 1].value.find(']');
    size_t urlStart = tokens[current - 1].value.find('(') + 1;
    size_t urlEnd = tokens[current - 1].value.find(')');
    
    std::string text = tokens[current - 1].value.substr(textStart, textEnd - textStart);
    std::string url = tokens[current - 1].value.substr(urlStart, urlEnd - urlStart);
    
    return "<a href=\"" + url + "\">" + text + "</a>";
}

std::string Parser::parseImage() {
    size_t altStart = tokens[current - 1].value.find('[') + 1;
    size_t altEnd = tokens[current - 1].value.find(']');
    size_t urlStart = tokens[current - 1].value.find('(') + 1;
    size_t urlEnd = tokens[current - 1].value.find(')');
    
    std::string alt = tokens[current - 1].value.substr(altStart, altEnd - altStart);
    std::string url = tokens[current - 1].value.substr(urlStart, urlEnd - urlStart);
    
    return "<img src=\"" + url + "\" alt=\"" + alt + "\">";
}

std::string Parser::parseCode() {
    return "<code>" + tokens[current - 1].value + "</code>";
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return tokens[current - 1];
}

Token Parser::peek() const {
    if (isAtEnd()) return {TokenType::EOF, ""};
    return tokens[current];
}

bool Parser::isAtEnd() const {
    return current >= tokens.size();
}