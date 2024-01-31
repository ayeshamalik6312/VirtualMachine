// Collaborators: Ayesha Malik and Daniel Rojas 

#define ARRAY_SIZE 500 
#include <stdio.h>
#include <string.h>

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
    while (!flag) {//Switch or if statements are fine ?
        // Fetch
        IR.OP = pas[PC]; 
        IR.L = pas[PC + 1]; 
        IR.M = pas[PC + 2];  
        PC += 3; 

        // Execute 
        if (IR.OP == 1) { 
            //LIT OPERATION
            SP--;
            pas[SP] = IR.M;
        }
        else if (IR.OP == 2) { 
            // RTN OPERATION
            if (IR.M == 0)
            {
                SP = BP - 1;
                BP = pas[SP - 2];
                PC = pas[SP - 3];
            }

            if (IR.M == 1)//ADD OP
            {
                pas[SP - 1] = pas[SP - 1] + pas[SP];
                SP--; 
            }

            if (IR.M == 2)//SUB OP
            {
                pas[SP - 1] = pas[SP - 1] - pas[SP];
                SP--;
            }

            if (IR.M == 3)//MUL OP
            {
                pas[SP - 1] = pas[SP - 1] * pas[SP];
                SP--;
            }

            if (IR.M == 4)//DIV OP
            {
                pas[SP - 1] = pas[SP - 1] / pas[SP];
                SP--;
            }

            if (IR.M == 5)//EQL OP
            {
                pas[SP - 1] = pas[SP - 1] == pas[SP];
                SP--;
            }

            if (IR.M == 6)//NEQ OP
            {
                pas[SP - 1] = pas[SP - 1] != pas[SP];
                SP--;
            }

            if (IR.M == 7)//LSS OP
            {
                pas[SP - 1] = pas[SP - 1] < pas[SP];
                SP--;
            }

            if (IR.M == 8)//LEQ OP
            {
                pas[SP - 1] = pas[SP - 1] <= pas[SP];
                SP--;
            }

            if (IR.M == 9)//GTR OP
            {
                pas[SP - 1] = pas[SP - 1] > pas[SP];
                SP--;
            }

            if (IR.M == 10)//GEQ OP
            {
                pas[SP - 1] = pas[SP - 1] >= pas[SP];
                SP--;
            }

            if (IR.M == 11)//ODD OP
            {
                pas[SP] = pas[SP] % 2;
            }
            

        }else if (IR.OP == 3) { 
            // LOD OPERATION
            SP--;
            pas[SP] = pas[base(BP,IR.L) - IR.M];
        }
        else if (IR.OP == 4) { 
            // STO OPERATOR
            pas[base(BP,IR.L) - IR.M] = pas[SP];
            SP--;
        }
        else if (IR.OP == 5) { 
            // CAL OPERATION
            pas[SP - 1] = base(BP,IR.L); //ESTABLISH STATIC LINK
            pas[SP - 2] = BP; //ESTABLISH DYNAMIC LINK
            pas[SP - 3] = PC; // RETURN ADDRESS
            BP = SP - 1;
            PC = IR.M;
        }
        else if (IR.OP == 6) { 
            // INC OPERATION
            SP = SP - IR.M;
        }
        else if (IR.OP == 7) { 
            // JMP OPERATION
            PC = IR.M;
        }
        else if (IR.OP == 8) { 
            // JPC OPERATION
            if (pas[SP] == 0)
            {
                PC = IR.M;
                SP++;
            }
            
        }
        else if (IR.OP == 9) { 
            // SYS OPERATIONS
            if (IR.M == 1)
            {
                printf("%d",pas[SP]);
                SP++;
            }

            if (IR.M == 2)
            {
                SP--;
                printf("Please Enter an Integer: ");
                scanf("%c", &pas[SP]); //HANDLE CHAR TO INT CONVERSION ?*****
            }

            if (IR.M == 3)
            {
                flag = 0;
            }
            
        }
        
    }

    // After the fetch-execute cycle is done we need to output it
    
    return 0;
}




