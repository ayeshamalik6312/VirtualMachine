// Collaborators: Ayesha Malik and Daniel Rojas 

#define ARRAY_SIZE 500 
#include <stdio.h>

// Global Variables 
int BP = 499, SP = 500, PC = 0, OP, L, M;
int pas[500] = {0}; 

typedef struct IR {
    int OP;
    int L;
    int M;
}IR; 

// Questions for Monty:
// should instruction register be a struct or seperately stored integers
// can we use global variables (is SP = 500 ok or should it be SP = BP + 1)

// Base function. Given in program assignment details
int base( int BP, int L) {
        int arb = BP;	// arb = activation record base
        while ( L > 0)     //find base L levels down
        {
            arb = pas[arb];
            L--;
        }
        return arb;
    }


int main() {
    // File.IO stuff
    // Need to change this to reading it in as a command line argument not how it is 
    int index = 0;
    FILE *file; 
    file = fopen("input.txt", "r");

    while (fscanf(file, "%d", &pas[index]) != EOF) {
        index++;
    }
    fclose(file);

    for (int i = 0; i < index; i++) {
        printf("%d\n", pas[i]);
    }


    // Instruction Cycle
    /* IR.OP <- pas[pc]
     * IR.L <- pas[pc + 1]
     * IR.M <- pas[pc + 2]
     *
     */
    return 0;
}




