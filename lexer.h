#ifndef LEXER_H
#define LEXER_H

#include <string>

// Define los diferentes tipos de tokens
enum class TokenType {
    Let, Func, Print, Identifier, Number, Plus, Minus, Multiply, Divide, Assign,
    Semicolon, LParen, RParen, LBrace, RBrace, Comma, EOF_Token
};

// Clase Token para representar los diferentes tipos de tokens
class Token {
public:
    Token(TokenType type, const std::string& value = "") : type(type), value(value) {}
    Token(TokenType type, int value) : type(type), intValue(value) {}

    TokenType type;
    std::string value;
    int intValue = 0;
};

class Lexer {
public:
    Lexer(const std::string& sourceCode);
    Token nextToken();
private:
    void advance();
    void skipWhitespace();
    Token identifier();
    Token number();
    std::string source;
    size_t position;
    char currentChar;
};

#endif // LEXER_H
