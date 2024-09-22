steps on my mind when creating this markdown compiler:
1) the first step is to read the input and break it down into tokens. Tokens can represent headers, links, bold text, and other md elements.
anyawya this would be a nice project structure to startw tih:
```
/md-compiler
    /src
        main.cpp         // contains the main entry point of the program.
        lexer.cpp        // doing the Lexer class (converts markdown text into tokens).
        parser.cpp       // doing the Parser class ( parses tokens into html).
    /include
        lexer.h          // short for lexical analyzer, its main job is to break down the input Markdown text into a series of tokens.
        parser.h         // dpoing the Parser class that parses the tokens.
    CMakeLists.txt (using CMake)
```

2) those tokens can be parsed into html using the parser class.

3) the parser class is a recursive descent parser, meaning that it parses the tokens in the order they are given to.

4) the parser class will return a string containing the html that was generated.
I am thinking of using CMake but i dont know how to tho.