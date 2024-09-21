steps on my mind when creating this markdown compiler:
1) The first step is to read the input and break it down into tokens. Tokens can represent headers, links, bold text, and other md elements.
anyawya this would be a nice project structure to startw tih:
```
/md-compiler
    /src
        main.cpp         // contains the main entry point of the program.
        lexer.cpp        // doing the Lexer class (converts markdown text into tokens).
        parser.cpp       // doing the Parser class ( parses tokens into html).
    /include
        lexer.h          // dpoing the Lexer class and token structures like TokenType and Token.
        parser.h         // dpoing the Parser class that parses the tokens.
    CMakeLists.txt (using CMake)
```