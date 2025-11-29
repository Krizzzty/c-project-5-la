#ifndef LEXER_H
#define LEXER_H

#define MAX_KEYWORDS 20
#define MAX_TOKEN_SIZE 100
#include <stdbool.h>
typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    PREPROCESSOR,
    IDENTIFIER,
    CONSTANT,
    CHARACTER_LITERAL,
    STRING_LITERAL,
    UNKNOWN
} TokenType;

typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;

void initializeLexer(const char* filename);
Token getNextToken();
void categorizeToken(Token* token);
bool isKeyword(const char* str);
int isOperator(const char* str);
int isSpecialCharacter(char ch);
int isConstant(const char* str);
int isIdentifier(const char* str);

#endif
