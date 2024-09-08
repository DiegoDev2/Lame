#include "parser.h"
#include "lexer.h"
#include <stdexcept>
#include <iostream>
Parser::Parser(Lexer& lexer) : lexer(lexer), currentToken(lexer.nextToken()) {}

void Parser::eat(TokenType type) {
    if (currentToken.type == type) {
        currentToken = lexer.nextToken();
    } else {
        throw std::runtime_error("Unexpected token");
    }
}

void Parser::parse() {
    while (currentToken.type != TokenType::EOF_Token) {
        if (currentToken.type == TokenType::Let) {
            eat(TokenType::Let);
            if (currentToken.type == TokenType::Identifier) {
                std::string varName = currentToken.value;
                eat(TokenType::Identifier);
                if (currentToken.type == TokenType::Assign) {
                    eat(TokenType::Assign);
                    if (currentToken.type == TokenType::Number) {
                        int value = currentToken.intValue;
                        eat(TokenType::Number);
                        if (currentToken.type == TokenType::Semicolon) {
                            eat(TokenType::Semicolon);
                            std::cout << "Variable Declaration: " << varName << std::endl;
                            std::cout << "Value: " << value << std::endl;
                        } else {
                            throw std::runtime_error("Expected semicolon");
                        }
                    } else {
                        throw std::runtime_error("Expected number");
                    }
                } else {
                    throw std::runtime_error("Expected '='");
                }
            } else {
                throw std::runtime_error("Expected identifier");
            }
        } else if (currentToken.type == TokenType::Print) {
            eat(TokenType::Print);
            if (currentToken.type == TokenType::LParen) {
                eat(TokenType::LParen);
                if (currentToken.type == TokenType::Identifier) {
                    std::string varName = currentToken.value;
                    eat(TokenType::Identifier);
                    if (currentToken.type == TokenType::RParen) {
                        eat(TokenType::RParen);
                        if (currentToken.type == TokenType::Semicolon) {
                            eat(TokenType::Semicolon);
                            std::cout << "Print statement: " << varName << std::endl;
                        } else {
                            throw std::runtime_error("Expected semicolon");
                        }
                    } else {
                        throw std::runtime_error("Expected closing parenthesis");
                    }
                } else {
                    throw std::runtime_error("Expected identifier inside parentheses");
                }
            } else {
                throw std::runtime_error("Expected opening parenthesis");
            }
        } else {
            throw std::runtime_error("Unexpected statement");
        }
    }
}
