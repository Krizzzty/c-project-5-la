#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lexer.h"
extern Token *tokens;
FILE *fptr = NULL;
int braces_count[6]={0};
bool is_Delimiter(char ch)
{
    return (ch == ';' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' ||
            ch == '=' || ch == '!' || ch == '<' || ch == '>' || ch == '(' || ch == ')' || ch == '{' || ch == '}' ||
            ch == '[' || ch == ']' || ch == '|' || ch == '&' || ch == ',');
}
bool is_space(char ch)
{
    return (ch == ' ');
}
static const char *keywords[MAX_KEYWORDS] = {
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct"};

static const char *operators = "+-*/%=!<>|&";
static const char *specialCharacters = ",;{}()[]";
// Function to check if a word is a keyword
bool isKeyword(const char *word)
{
    for (int i = 0; i < MAX_KEYWORDS; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1; // Word is a keyword
        }
    }
    return 0; // Not a keyword
}
void initializeLexer(const char *filename)
{
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Error in opening file\n");
        return;
    }
    printf("File opened successfully\n");
}
bool is_newline(char ch)
{
    return ch == '\n';
}
Token getNextToken()
{
    char ch;
    // static int left=0,right=0;
    Token token;
    int index = 0;
    // skip spaces
    while (is_space((ch = fgetc(fptr))) || is_newline(ch));
    if (ch == EOF)
    {
        strcpy(token.lexeme, "EOF");
        token.type = UNKNOWN;
    }
    else if (ch == '#')
    {
        token.lexeme[index++] = ch;
        char next;
        while ((next = fgetc(fptr)) != EOF)
        {
            if(is_newline(next) && index!=0 && token.lexeme[index-1]!='\\'){
                break;
            }
            token.lexeme[index++] = next;
        }

        token.lexeme[index] = '\0';
        token.type = PREPROCESSOR;
    }
    else if (strchr(operators, ch) != NULL)
    {
        char next;
        token.lexeme[index++] = ch;
        while ((next = fgetc(fptr)) != EOF && strchr(operators, next) != NULL)
        {
            token.lexeme[index++] = next;
        }
        ungetc(next, fptr); // Push back last read non-operator
        token.lexeme[index] = '\0';
        token.type = OPERATOR;
    }
    else if (strchr(specialCharacters, ch) != NULL)
    {
        token.lexeme[index++] = ch;
        token.lexeme[index] = '\0';
        token.type = SPECIAL_CHARACTER;
        if(ch=='{'){
            braces_count[0]++;
        }
        else if(ch=='}'){
            braces_count[1]++;
        }
        else if(ch=='['){
            braces_count[2]++;
        }
        else if(ch==']'){
            braces_count[3]++;
        }
        else if(ch=='('){
            braces_count[4]++;
        }
        else if(ch==')'){
            braces_count[5]++;
        }
    }
    else
    {
        char next;
        token.lexeme[index++] = ch;
        while ((next = fgetc(fptr)) != EOF && strchr(operators, next) == NULL &&
               is_Delimiter(next) == 0 && strchr(specialCharacters, next) == NULL && !is_space(next) && !is_newline(next))
        {
            token.lexeme[index++] = next;
        }
        ungetc(next, fptr); // Push back last read non-operator
        token.lexeme[index] = '\0';
        if (isKeyword(token.lexeme))
        {
            token.type = KEYWORD;
        }
        else if(token.lexeme[0]=='\'' && token.lexeme[strlen(token.lexeme)-1]=='\''  ){
            token.type=CHARACTER_LITERAL;
        }
        else if(token.lexeme[0]=='\"' && token.lexeme[strlen(token.lexeme)-1]=='\"'  ){
            token.type=STRING_LITERAL;
        }
        else if(atoi(token.lexeme)!=0 || ((strlen(token.lexeme)==1 && token.lexeme[0]-'0'==0))){
            token.type=CONSTANT;
        }
        else
        {
            token.type = IDENTIFIER;
        }
    }
    return token;
}