#include <stdio.h>
#include "lexer.h"
extern int braces_count[6];
int main(int argc, char *argv[])
{
    initializeLexer(argv[1]);

    Token token;
    while ((token = getNextToken()).type != UNKNOWN)
    {
        printf("Token: %s, Type: ", token.lexeme);
        switch (token.type)
        {
        case 0:
            printf("KEYWORD\n");
            break;
        case 1:
            printf("OPERATOR\n");
            break;
        case 2:
            printf("SPECIAL_CHARACTER\n");
            break;
        case 3:
            printf("PREPROCESSOR\n");
            break;
        case 4:
            printf("IDENTIFIER\n");
            break;
        case 5:
            printf("CONSTANT\n");
            break;
        case 6:
            printf("CHARCATER_LITERAL\n");
            break;
        case 7:
            printf("STRING_LITERAL\n");
            break;
        }
    }
    if (braces_count[0] < braces_count[1])
    {
        printf("ERROR: { missing\n");
    }
    else if (braces_count[0] > braces_count[1])
    {
        printf("ERROR: } missing\n");
    }
    if (braces_count[2] < braces_count[3])
    {
        printf("ERROR: [ missing\n");
    }
    else if (braces_count[2] > braces_count[3])
    {
        printf("ERROR: ] missing\n");
    }
    if (braces_count[4] < braces_count[5])
    {
        printf("ERROR: ( missing\n");
    }
    else if (braces_count[4] > braces_count[5])
    {
        printf("ERROR: ) missing\n");
    }
    return 0;
}
