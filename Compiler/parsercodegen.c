// Collaborators: Daniel Rojas and Ayesha Malik

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IDENTIFIER 11
#define MAX_NUMBER 5
#define MAX_SYMBOL_TABLE_SIZE 500

char buffer[10000] = {0}; // For reading in
int cap = 100, structSize = 0;

typedef struct Symbol {
  int kind;                    // const = 1, var = 2, proc = 3
  char lexeme[MAX_IDENTIFIER]; // name up to 11 chars
  int tokenVal;                // number (ASCII value)
  int level;                   // L level
  int addr;                    // M address
  int mark;                    // to indicate unavailable or deleted
} Symbol;

Symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];

// Reserved Words
char *reservedWords[] = {"const", "var", "procedure", "call", "begin",
                         "end",   "if",  "fi",        "then", "else",
                         "while", "do",  "read",      "write"};

// Special Symbols
char specialSymbols[] = {'+', '-', '*', '/', '(', ')', '=',
                         ',', '.', '<', '>', ';', ':', '!'};

// Lexical Conventions
int skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11,
    leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16,
    commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25,
    dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30,
    writesym = 31, readsym = 32, elsesym = 33;

// should file be read in as an initial arg or like this?

// function definitions:
void addStruct(Symbol *t, char lex[], int tokenVal);
void separateTokens(Symbol *t, int size);
void printToken();
int isKeyWord(char word[]);
int isWhiteSpace(char c);
int isSpecialSymbol(char c);
int checkErrors(Symbol *t, int size);
void program();
void block();
void condition();
void expression();
void term();
void factor();
int symbolTableCheck(Symbol *t, int size, char *name, int nameIndex);

int main(int argc, char *argv[]) {

  Symbol *t = malloc(cap * sizeof(Symbol));

  // File Management
  char *name = argv[1];
  int size = 0, ch;
  FILE *fp = fopen(name, "r");
  while ((ch = fgetc(fp)) != EOF) {
    buffer[size++] = (char)ch;
  }
  fclose(fp);

  separateTokens(t, size);

  // Printing token list -- MODIFY TO MATCH OUTPUT
  printf("\nToken List:\n");
  for (int i = 0; i < structSize; i++) {
    printf("%d ", t[i].tokenVal);
    if (t[i].tokenVal == 2) {
      printf("%s ", t[i].lexeme);
    }
    if (t[i].tokenVal == 3) {
      printf("%s ", t[i].lexeme);
    }
  }

  int error = checkErrors(t, size);
  printf("\n");

  // freeing memory at the end
  free(t);
  t = NULL;
  return 0;
}

// Helper functions
/// *******This is not broken =) *****************
void separateTokens(Symbol *t, int size) {
  int i = 0;
  while (i < strlen(buffer)) {
    // first check to see if its a comment.
    if (buffer[i] == '/' && buffer[i + 1] == '*') {
      i += 2; // Move past the "/*"
      // keep iterating until you've skipped over the whole comment
      while (i < strlen(buffer) - 1 &&
             !(buffer[i] == '*' && buffer[i + 1] == '/')) {
        i++;
      }
      i += 2; // Move past the "*/"
      continue;
    }
    // check to see if its other kind of comment
    else if (buffer[i] == '/' && buffer[i + 1] == '/') {
      i++;
      // keep iterating until you've skipped over the whole comment
      while (buffer[i] != '\n' && buffer[i] != '\0') {
        i++;
      }
      continue;
    }
    // check for white spaces
    else if (isWhiteSpace(buffer[i])) {
      i++;
      continue;
    }
    // is it a special symbol? if so add it to token struct array
    else if (isSpecialSymbol(buffer[i])) {
      char c[3] = {'\0'};
      if (buffer[i] == '+') {
        c[0] = buffer[i];
        addStruct(t, c, 4);
      } else if (buffer[i] == '-') {
        c[0] = buffer[i];
        addStruct(t, c, 5);
      } else if (buffer[i] == '*') {
        c[0] = buffer[i];
        addStruct(t, c, 6);
      } else if (buffer[i] == '/') {
        c[0] = buffer[i];
        addStruct(t, c, 7);
      } else if (buffer[i] == '(') {
        c[0] = buffer[i];
        addStruct(t, c, 15);
      } else if (buffer[i] == ')') {
        c[0] = buffer[i];
        addStruct(t, c, 16);
      } else if (buffer[i] == '=') {
        c[0] = buffer[i];
        addStruct(t, c, 9);
      } else if (buffer[i] == ',') {
        c[0] = buffer[i];
        addStruct(t, c, 17);
      } else if (buffer[i] == '.') {
        c[0] = buffer[i];
        addStruct(t, c, 19);
      } else if (buffer[i] == '<') {
        if (buffer[i + 1] == '=') {
          c[0] = buffer[i];
          c[1] = buffer[i + 1];
          addStruct(t, c, 12);
          i++;
        } else if (buffer[i + 1] == '>') {
          c[0] = buffer[i];
          c[1] = buffer[i + 1];
          addStruct(t, c, 10);
          i++;
        } else {
          c[0] = buffer[i];
          addStruct(t, c, 11);
        }
      } else if (buffer[i] == '>') {
        if (buffer[i + 1] == '=') {
          c[0] = buffer[i];
          c[1] = buffer[i + 1];
          addStruct(t, c, 14);
          i++;
        } else {
          c[0] = buffer[i];
          addStruct(t, c, 13);
        }
      } else if (buffer[i] == ';') {
        c[0] = buffer[i];
        addStruct(t, c, 18);
      } else if (buffer[i] == ':' && buffer[i + 1] == '=') {
        c[0] = buffer[i];
        c[1] = buffer[i + 1];
        addStruct(t, c, 20);
        i++;
      } else if (buffer[i] == '!' && buffer[i + 1] == '=') {
        c[0] = buffer[i];
        c[1] = buffer[i + 1];
        addStruct(t, c, 10);
        i++;
      }
      i++;
      continue;
    }

    // is it a number or digit?
    else if (isalnum(buffer[i])) {
      // if so create a temp array to store it
      char temp[50];
      int j = 0;
      // resetting arr val ever time
      memset(temp, '\0', sizeof(temp));
      // iterate through characters until you hit something not a num or letter
      while (isalnum(buffer[i])) {
        temp[j] = buffer[i];
        i++;
        j++;
      }

      temp[j] = '\0';
      // if its longer than 11 digits then print error right away
      if (j > MAX_IDENTIFIER) {
        printf("Error: Name is too long \n");
        break;
      }
      // check if its a key word
      else if (isKeyWord(temp) > 0) {
        int val = 0;
        val = isKeyWord(temp);
        addStruct(t, temp, val);
        continue;
      }
      // is it a number?
      int flag = 0;
      for (int k = 0; k < j; k++) {
        if (!isdigit(temp[k])) {
          flag = 1;
          break;
        }
      }

      // if it is a number but more than 5 digits, print error
      if (flag == 0) {
        if (j > MAX_NUMBER) {
          printf("Error: Number is too long\n");
          break;
        }
        // if it is a number and appropriate length, add it to array
        else {
          addStruct(t, temp, 3);
          continue;
        }
      }
      // if its not a keyword or number its an identifier
      else {
        addStruct(t, temp, 2);
      }
    }
    // if its not a number or letter or special symbol, it's an invalid symbol.
    else {
      printf("Error: invalid symbol\n");
      i++;
      break;
    }
  }
}

/// HELPER FUNCTIONS
// checks for all kinds of white spaces
int isWhiteSpace(char c) {
  if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
    return 1;
  return 0;
}

// special symbol detection
int isSpecialSymbol(char c) {
  for (int i = 0; i < 14; i++) {
    if (c == specialSymbols[i]) {
      return 1;
    }
  }
  return 0;
}

// compares word with keywords, if matched, it returns the lex val.
int isKeyWord(char word[]) {
  if (!strcmp(word, "begin")) {
    return 21;
  } else if (!strcmp(word, "end")) {
    return 22;
  } else if (!strcmp(word, "if")) {
    return 23;
  } else if (!strcmp(word, "then")) {
    return 24;
  } else if (!strcmp(word, "while")) {
    return 25;
  } else if (!strcmp(word, "do")) {
    return 26;
  } else if (!strcmp(word, "call")) {
    return 27;
  } else if (!strcmp(word, "const")) {
    return 28;
  } else if (!strcmp(word, "var")) {
    return 29;
  } else if (!strcmp(word, "procedure")) {
    return 30;
  } else if (!strcmp(word, "write")) {
    return 31;
  } else if (!strcmp(word, "read")) {
    return 32;
  } else if (!strcmp(word, "fi")) {
    return 8;
  } else if (!strcmp(word, "else")) {
    return 33;
  } else {
    return 0;
  }
}

// handles array of structs stuff execpt for initalization and freeing
void addStruct(Symbol *t, char lex[], int tokenVal) {
  if (structSize >= cap) {
    cap *= 2;
    Symbol *temp = realloc(t, cap * sizeof(Symbol));
    t = temp;
  }
  strcpy(t[structSize].lexeme, lex);
  t[structSize].tokenVal = tokenVal;
  printf("%s \t\t", t[structSize].lexeme);
  printf("%d\n", t[structSize].tokenVal);
  structSize++;
}

int checkErrors(Symbol *t, int size) {
  int numVars = 0;
  /// error: program must end with a period
  if (t[structSize - 1].tokenVal != 19) {
    printf("Error: Program ended with %d\n", t[structSize - 1].tokenVal);
    return 0;
  }
  // Parsing through all of the rest of the tokens
  for (int i = 0; i < size; i++) {
    // Check for all const rules
    if (t[i].tokenVal == 28) {
      i++;
      int flag = 1;
      while (flag) {
        if (t[i].tokenVal != 2) {
          printf("Error: const must be followed by an identifier\n");
          return 0;
        } else if (symbolTableCheck(t, size, t[i].lexeme, i) != -1) {
          printf("Error: symbol name has already been declared %s\n",
                 t[i].lexeme);
          return 0;
        } else if (t[i + 1].lexeme[0] != '=') {
          printf("Error: Identifier must be assigned with '=' \n");
          return 0;
        } else if (t[i + 2].tokenVal != 3) {
          printf("Error: Identifier must be followed by an integer value\n");
          return 0;
        }
        i += 3;
        if (t[i].tokenVal == 18) {
          break;
        } else if (t[i].tokenVal != 17) {
          printf(
              "Error: Constants must be separated by ',' and end with ';'\n");
          return 0;
        }
        i++;
      }
    }
    // Check for all var rules
    else if (t[i].tokenVal == 29) {
      i++;
      int flag = 1;
      while (flag) {
        if (t[i].tokenVal != 2) {
          printf("Error: var must be followed by an identifier\n");
          return 0;
        } else if (symbolTableCheck(t, size, t[i].lexeme, i) != -1) {
          printf("Error: variable name has already been delcared %s\n",
                 t[i].lexeme);
          return 0;
        }
        numVars++;
        i++;
        if (t[i].tokenVal == 18) {
          break;
        } else if (t[i].tokenVal != 17) {
          printf(
              "Error: Variables must be separated by ',' and end with ';'\n");
          return 0;
        } else {
          i++;
        }
      }
    }
    // Check read
    else if (t[i].tokenVal == 32) {
      i++;
      if (t[i].tokenVal != 2) {
        printf("Error: read must be followed by an identifier\n");
        return 0;
      }
      i++;
    }
    // STATEMENT
    if (t[i].tokenVal == 2) {
      if (symbolTableCheck(t, size, t[i].lexeme, i) == -1) {
        printf("Error: Undeclared identfier %s\n", t[i].lexeme);
        return 0;
      } else if (t[i + 1].tokenVal != 20) {
        printf("Error: assignment statements must use :=");
        return 0;
      }
    }
    // begin / end check
    else if (t[i].tokenVal == 21) {
      int nested = 1;
      while (i++ < size) {
        if (t[i].tokenVal == 21) {
          nested++;
        } else if (t[i].tokenVal == 22) {
          nested--;
        }
      }
      if (nested != 0) {
        printf("Error: begin must be followed by end\n");
        return 0;
      }
    } // if then handling
    else if (t[i].tokenVal == 23) {
      int nested = 1;
      while (i++ < size) {
        if (t[i].tokenVal == 23) {
          nested++;
        } else if (t[i].tokenVal == 24) {
          nested--;
        }
      }
      if (nested != 0) {
        printf("Error: if must be followed by then\n");
        return 0;
      }
    } else if (t[i].tokenVal == 25) {
      int nested = 1;
      while (i++ < size) {
        if (t[i].tokenVal == 25) {
          nested++;
        } else if (t[i].tokenVal == 26) {
          nested--;
        }
      }
      if (nested != 0) {
        printf("Error: while must be followed by do\n");
        return 0;
      }
    } else if (t[i].tokenVal == 32) {
    } else if (t[i].tokenVal == 31) {
    }
  }
}

int symbolTableCheck(Symbol *t, int size, char *name, int nameIndex) {
  for (int i = 0; i < size; i++) {
    if (strcmp(t[i].lexeme, name) == 0 && i != nameIndex) {
      return i;
    }
  }
  return -1;
}
