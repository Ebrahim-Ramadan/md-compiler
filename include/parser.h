

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), current(0) {}
    std::string parse();

private:
    std::vector<Token> tokens;
    size_t current;
};
