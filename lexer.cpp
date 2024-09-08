#include "lexer.h"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& sourceCode) : source(sourceCode), position(0), currentChar(source[0]) {}

void Lexer::advance() {
    position++;
    if (position < source.length()) {
        currentChar = source[position];
    } else {
        currentChar = '\0';
    }
}

void Lexer::skipWhitespace() {
    while (currentChar != '\0' && (std::isspace(currentChar) || currentChar == '\n')) {
        if (currentChar == '\n') {

        }
        advance();
    }
}

Token Lexer::identifier() {
    std::string value;
    while (std::isalnum(currentChar) || currentChar == '_') {
        value += currentChar;
        advance();
    }
    if (value == "let") return Token(TokenType::Let);
    if (value == "func") return Token(TokenType::Func);
    if (value == "print") return Token(TokenType::Print);
    return Token(TokenType::Identifier, value);
}

Token Lexer::number() {
    std::string value;
    while (std::isdigit(currentChar)) {
        value += currentChar;
        advance();
    }
    return Token(TokenType::Number, std::stoi(value));
}

Token Lexer::nextToken() {
    while (currentChar != '\0') {
        if (std::isspace(currentChar) || currentChar == '\n') {
            skipWhitespace();
            continue;
        }
        if (std::isalpha(currentChar) || currentChar == '_') return identifier();
        if (std::isdigit(currentChar)) return number();
        if (currentChar == '+') { advance(); return Token(TokenType::Plus); }
        if (currentChar == '-') { advance(); return Token(TokenType::Minus); }
        if (currentChar == '*') { advance(); return Token(TokenType::Multiply); }
        if (currentChar == '/') { advance(); return Token(TokenType::Divide); }
        if (currentChar == '=') { advance(); return Token(TokenType::Assign); }
        if (currentChar == ';') { advance(); return Token(TokenType::Semicolon); }
        if (currentChar == '(') { advance(); return Token(TokenType::LParen); }
        if (currentChar == ')') { advance(); return Token(TokenType::RParen); }
        if (currentChar == '{') { advance(); return Token(TokenType::LBrace); }
        if (currentChar == '}') { advance(); return Token(TokenType::RBrace); }
        if (currentChar == ',') { advance(); return Token(TokenType::Comma); }
        throw std::runtime_error("Unexpected character: " + std::string(1, currentChar));
    }
    return Token(TokenType::EOF_Token);
}
