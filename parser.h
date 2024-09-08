#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <string>

class Parser {
public:
    Parser(Lexer& lexer);
    void parse();

private:
    void eat(TokenType type);

    Lexer& lexer;
    Token currentToken;
};

#endif // PARSER_H
