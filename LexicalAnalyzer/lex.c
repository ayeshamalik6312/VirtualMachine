// Collaborators: Daniel Rojas and Ayesha Malik

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_IDENTIFIER 11
#define MAX_NUMBER 5
char buffer[10000] = {0}; //For reading in
typedef struct token {
    int type;
    char lexeme[MAX_IDENTIFIER + 1];
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

int main(int argc, char* argv[]) {
    // File Management
    char* name = argv[1];

    int size = 0, ch;
    FILE *fp = fopen(name, "r");
    while ((ch = fgetc(fp)) != EOF) {
        buffer[size++] = (char)ch;
    }
    fclose(fp);


    printf("%s", buffer);
    seperateTokens(size);

    return 0;
}


// Helper functions
/// *******This is broken*****************
void seperateTokens(int size) {
  int i = 0;
  while (i < strlen(buffer)) {
      // if its a white space then do nothing its not a lexeme
      if (isWhiteSpace(buffer[i])) {
          i++;
          printf("White Space");
          continue;
      }

      int p, boolean = 0;
      for(p=0; i <= 12; i++)
      {
          if(buffer[i] == specialSymbols[i]) {
              boolean = 1;
              break;
          }
      }

      if (boolean) {
          // add token to list as a special symbol
          i++;
          printf("Special Symbol!");
          continue;
      }

      if (isalnum(buffer[i])) {
          char temp[50];
          int j = i, k = 0;
          while (!isWhiteSpace(buffer[j])) {
              temp[k] = buffer[j];
              j++;
              k++;
          }
          i = j;

          for (int l = 0; l < 14; l++) {
              if (strcmp(temp, reservedWords[l])) {
                  // add token to token list as a reserved words
                  printf("Reserved word!");
                  i++;
                  break;
              }
          }

          // here if its none of the above then store as an identifer and do a length check.

      }
  }
}

/*
 *
 */

int isWhiteSpace(char c) {
    if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
        return 1;
    return 0;
}


void printToken() {

}
