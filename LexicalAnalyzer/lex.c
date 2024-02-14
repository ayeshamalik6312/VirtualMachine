// Collaborators: Daniel Rojas and Ayesha Malik

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_IDENTIFIER 11
#define MAX_NUMBER 5

char buffer[10000] = {0}; //For reading in
int cap = 100, structSize = 0;

typedef struct Token {
    int tokenVal;
    char lexeme[MAX_IDENTIFIER + 1]; // +1 to account for \0
} Token;

// Reserved Words
char *reservedWords[] = {
        "const", "var", "procedure", "call", "begin", "end", "if",
        "fi", "then", "else", "while", "do", "read", "write"
};

// Special Symbols
char specialSymbols[] = {
        '+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':', '!'};

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
void addStruct(Token* t, char lex[], int tokenVal);
void seperateTokens(Token * t, int size);
void printToken();
int isKeyWord(char word[]);
int isWhiteSpace(char c);
int isSpecialSymbol(char c);

int main(int argc, char* argv[]) {
    Token * t = malloc(cap * sizeof(Token));

    // File Management
    char* name = argv[1];
    int size = 0, ch;
    FILE *fp = fopen(name, "r");
    while ((ch = fgetc(fp)) != EOF) {
        buffer[size++] = (char)ch;
    }
    fclose(fp);

    printf("%s\n", buffer);
    printf ("lex val:  lexeme:   \n");

    seperateTokens(t, size);

    // freeing memory at the end
    free(t);
    t = NULL;
    return 0;
}


// Helper functions
/// *******This is broken*****************
void seperateTokens(Token * t, int size) {
    int i = 0;
    while (i < strlen(buffer)) {
        // first check to see if its a comment.
        if (buffer[i] == '/' && buffer[i + 1] == '*') {
            i+=2; // Move past the "/*"
            // keep iterating until you've skipped over the whole comment
            while (i < strlen(buffer) - 1 && !(buffer[i] == '*' && buffer[i + 1] == '/')) {
                i++;
            }
            i +=2; // Move past the "*/"
            continue;
        }
        // check to see if its other kind of comment
        else if (buffer[i] == '/' && buffer[i + 1] == '/') {
            i++;
            // keep iterating until you've skipped over the whole comment
            while(buffer[i] != '\n' && buffer[i] != '\0') {
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
            }
            else if (buffer[i] == '-') {
                c[0] = buffer[i];
                addStruct(t, c, 5);
            }
            else if (buffer[i] == '*') {
                c[0] = buffer[i];
                addStruct(t, c, 6);
            }
            else if (buffer[i] == '/') {
                c[0] = buffer[i];
                addStruct(t, c, 7);
            }
            else if (buffer[i] == '(') {
                c[0] = buffer[i];
                addStruct(t, c, 15);
            }
            else if (buffer[i] == ')') {
                c[0] = buffer[i];
                addStruct(t, c, 16);
            }
            else if (buffer[i] == '=') {
                c[0] = buffer[i];
                addStruct(t, c, 9);
            }
            else if (buffer[i] == ',') {
                c[0] = buffer[i];
                addStruct(t, c, 17);
            }
            else if (buffer[i] == '.') {
                c[0] = buffer[i];
                addStruct(t, c, 19);
            }
            else if (buffer[i] == '<') {
                if (buffer[i + 1] == '=') {
                    c[0] = buffer[i];
                    c[1] = buffer[i + 1];
                    addStruct(t, c, 12);
                    i++;
                }
                else {
                    c[0] = buffer[i];
                    addStruct(t, c, 11);
                }
            }
            else if (buffer[i] == '>') {
                if (buffer[i + 1] == '=') {
                    c[0] = buffer[i];
                    c[1] = buffer[i + 1];
                    addStruct(t, c, 14);
                    i++;
                }
                else {
                    c[0] = buffer[i];
                    addStruct(t, c, 13);
                }
            }
            else if (buffer[i] == ';') {
                c[0] = buffer[i];
                addStruct(t, c, 18);
            }
            else if (buffer[i] == ':' && buffer[i + 1] == '=') {
                c[0] = buffer[i];
                c[1] = buffer[i + 1];
                addStruct(t, c, 20);
                i++;
            }
            else if (buffer[i] == '!' && buffer[i + 1] == '=') {
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
                temp[j++] = buffer [i++];
            }
            temp[j] = '\0';
            // if its longer than 11 digits then print error right away
            if (j > MAX_IDENTIFIER) {
                printf("Lexical Error: Name too long: %s\n", temp);
                continue;
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
                    printf("Lexical Error: Number too long: %s\n", temp);
                    continue;
                }
                // if it is a number and appropriate length, add it to array
                else {
                    addStruct(t, temp, 3);
                    continue;
                }
            }
            // if its not a number check if it's an invalid symbol.
            // if its not an invalid symbol then add it as an identfier
            else {
                addStruct(t, temp, 2);
            }
        }
        i++;
    }
}

/// HELPER FUNCTIONS
// checks for all kinds of white spaces
int isWhiteSpace(char c) {
    if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
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
   return 0 ;
}

// handles array of structs stuff execpt for initalization and freeing
void addStruct(Token* t, char lex[], int tokenVal)
{
    if (structSize >= cap) {
        cap *= 2;
        Token * temp = realloc(t, cap * sizeof(Token));
        t = temp;
    }
    strcpy(t[structSize].lexeme, lex);
    t[structSize].tokenVal = tokenVal;
    printf("%d \t", t[structSize].tokenVal);
    printf("%s\n", t[structSize].lexeme);
    structSize++;
}

// compares word with keywords, if matched, it returns the lex val.
int isKeyWord(char word[]) {
    if (!strcmp(word, "begin")) {
        return 21;
    }
    else if (!strcmp(word, "end")) {
        return 22;
    }
    else if (!strcmp(word, "if")) {
        return 23;
    }
    else if (!strcmp(word, "then")) {
        return 24;
    }
    else if (!strcmp(word, "while")) {
        return 25;
    }
    else if (!strcmp(word, "do")) {
        return 26;
    }
    else if (!strcmp(word, "call")) {
        return 27;
    }
    else if (!strcmp(word, "const")) {
        return 28;
    }
    else if (!strcmp(word, "var")) {
        return 29;
    }
    else if (!strcmp(word, "procedure")) {
        return 30;
    }
    else if (!strcmp(word, "write")) {
        return 31;
    }
    else if (!strcmp(word, "read")) {
        return 32;
    }
    else if (!strcmp (word, "fi")) {
        return 8;
    }
    else if (!strcmp(word, "else")) {
        return 33;
    }
    else {
        return 0;
    }
}
