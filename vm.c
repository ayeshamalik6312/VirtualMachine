// Collaborators: Ayesha Malik and Daniel Rojas 

#define ARRAY_SIZE 500 
#include <stdio.h>

// Global Variables 
int BP = 499, SP = 500, PC = 0;
// initalizing all indexes of PAS to 0
int pas[ARRAY_SIZE] = {0}; 

typedef struct InstructionRegister {
    int OP;
    int L;
    int M;
}InstructionRegister; 

// Questions for Monty:
// should instruction register be a struct or seperately stored integers
// can we use global variables (is SP = 500 ok or should it be SP = BP + 1)
// For 'output file' does everything need to be stored in an actual output file 
// or just printed to terminal

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

int main(int argc, char* argv[]) {
    // File.IO stuff
    // Need to change this to reading it in as a command line argument not how it is 
    char fileName[50]; 
    for (int i = 0; i < argc; i++) { 
        strcpy(fileName, argv[i]); 
    }
    
    
    int index = 0;
    FILE *file; 
    file = fopen(fileName, "r");

    while (fscanf(file, "%d", &pas[index]) != EOF) {
        index++;
    }
    fclose(file);

    for (int i = 0; i < index; i++) {
        printf("%d\n", pas[i]);
    }


    // Instruction Cycle
    int flag = 0; 
    InstructionRegister IR; 
    while (!flag) {
        // Fetch
        IR.OP = pas[PC]; 
        IR.L = pas[PC + 1]; 
        IR.M = pas[PC + 2];  
        PC += 3; 

        // Execute 
        if (IR.OP == 1) { 
            // ADD
            // pas[sp + 1] = pas[sp + 1] + pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 2) { 
            // SUB
            // pas[sp + 1] = pas[sp + 1] - pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 3) { 
            // MUL
            // pas[sp + 1] = pas[sp + 1] * pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 4) { 
            // DIV
            // pas[sp + 1] = pas[sp + 1] / pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 5) { 
            // EQL
            // pas[sp + 1] = pas[sp + 1] == pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 6) { 
            // NEQ
            // pas[sp + 1] = pas[sp + 1] != pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 7) { 
            // LSS
            // pas[sp + 1] = pas[sp + 1] < pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 8) { 
            // LEQ
            // pas[sp + 1] = pas[sp + 1] <= pas[sp]
			// sp = sp + 1;
        }
        else if (IR.OP == 9) { 
            // GTR
            // pas[sp + 1] = pas[sp + 1] > pas[sp]
		    // sp = sp + 1;
        }
        else if (IR.OP == 10) { 
            // GEQ
            // pas[sp + 1] = pas[sp + 1] >= pas[sp]
		    // sp = sp + 1;

        }
        else if (IR.OP == 11) { 
            // ODD 
            // pas[sp] = pas[sp] % 2
        }
    }

    // After the fetch-execute cycle is done we need to output it
    
    return 0;
}




