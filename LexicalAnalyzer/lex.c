
// Collaborators: Daniel Rojas and Ayesha Malik

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_IDENTIFIER 11
#define MAX_NUMBER 5
char buffer[10000]; //For reading in tokens
typedef struct token {
    int type;
    char lexeme[MAX_IDENTIFIER];
} token;

// Reserved Words
char *reservedWords[] = {
        "const", "var", "procedure", "call", "begin", "end", "if",
        "fi", "then", "else", "while", "do", "read", "write"
};

// Special Symbols
char specialSymbols[] = {
        '+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':'};

// Lexical Conventions
int skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
        multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym =
        12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
        semicolonsym = 18, periodsym = 19, becomessym = 20,
        beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
        callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
        readsym = 32, elsesym = 33;

// should file be read in as an initial arg or like this?

// function definitions:
void seperateTokens();
void printToken();
int isLetter(char c);
int isNum(char c);
int isWhiteSpace(char c);
int isSpecialSymbol(char c);

int main() {
    // File Management
    char name[50]; //Name of input file
    int size = 0;
    printf("Input File Name\t");
    scanf("%s", name);

    FILE *fp = fopen(name, "r");
    while (fscanf(fp, "%s", buffer != EOF)) {
        size++;
    }
    fclose(fp);

    seperateTokens(size);

    return 0;
}


// Helper functions
void seperateTokens(int size) {
  for (int i = 0; i < size; i++)  {
      token t;
      if (isalpha(buffer[i])) {
          // check to see if its an identifier or reserved word
      }
      else if (isdigit(buffer[i])) {
          // check to see if num is valid length
      }
      else if (isWhiteSpace(buffer[i])) {
          // ignore
      }
      else if(isSpecialSymbol(buffer[i])) {

      }
  }
}

int isWhiteSpace(char c) {
    if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
        return 1;
    return 0;
}

int isSpecialSymbol(char c)
{
    int i;
    for(i=0; i <= 12; i++)
    {
        if(c == specialSymbols[i])
            return 1;
    }
    return 0;
}

void printToken() {

}
