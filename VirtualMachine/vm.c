// Collaborators: Ayesha Malik and Daniel Rojas 

#define ARRAY_SIZE 500 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global Variables 
int BP = 499, SP = 500, PC = 0;
// initalizing all indexes of PAS to 0
int pas[ARRAY_SIZE] = {0}; 

typedef struct InstructionRegister {
    int OP;
    int L;
    int M;
    char opName[10];
}InstructionRegister; 


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

    // file input
    char fileName[50]; 
    for (int i = 0; i < argc; i++) { 
        strcpy(fileName, argv[i]); 
    }
    
    // file management
    int index = 0;
    FILE *file; 
    file = fopen(fileName, "r");

    while (fscanf(file, "%d", &pas[index]) != EOF) {
        index++;
    }
    fclose(file);

    printf("                 PC   BP   SP    stack\n");
    printf("INITIAL VALUES:  %-3d  %-3d  %-3d\n",PC,BP,SP);
    // Instruction Cycle
    int flag = -1, ctr = 0; 
    int testCount = 0;
    InstructionRegister IR;
    IR.OP = 0;
    IR.L = 0;
    IR.M = 0; 


    while (flag != 0) {
        // Fetch
        if (ctr > 0) { 
            printf("    %s   %-3d %-3d %-3d  %-3d  %-3d ",IR.opName,IR.L,IR.M,PC,BP,SP);
        }
        else { 
            printf(" ");
            ctr++; 
        }

        // printing stack 
        for (int i = ARRAY_SIZE - 1; i >= SP; i--)
        {
            if (i == BP && i < ARRAY_SIZE - 4)
            {
                printf("|"); 
            }
            printf("  %d ",pas[i]);
        }     
        printf("\n");
        
        // assigning AR Variables 
        //testCount++;
        IR.OP = pas[PC]; 
        IR.L = pas[PC + 1]; 
        IR.M = pas[PC + 2];  
        PC += 3; 
        // assigning the name of the opcode so its easier to print 
        switch(IR.OP) {
            case 1:
                strcpy(IR.opName, "LIT");
                break;
            case 2: 
                if (IR.M == 0) { 
                    strcpy(IR.opName, "RTN"); 
                } 
                if (IR.M == 1) {
                    strcpy(IR.opName, "ADD"); 
                }
                if (IR.M == 2) {
                    strcpy(IR.opName, "SUB");
                }
                if (IR.M == 3) {
                    strcpy(IR.opName, "MUL");
                }
                if (IR.M == 4) {
                    strcpy(IR.opName, "DIV");
                }
                if (IR.M == 5) {
                    strcpy(IR.opName, "EQL");
                }
                if (IR.M == 6) {
                    strcpy(IR.opName, "NEQ");
                }
                if (IR.M == 7) {
                    strcpy(IR.opName, "LSS");
                }
                if (IR.M == 8) {
                    strcpy(IR.opName, "LEQ");
                }
                if (IR.M == 9) {
                    strcpy(IR.opName, "GTR");
                }
                if (IR.M == 10){
                    strcpy(IR.opName, "GEQ");
                }
                if (IR.M == 11){
                    strcpy(IR.opName, "ODD");
                }  
                break;
            case 3:
                strcpy(IR.opName, "LOD");
                break;
            case 4:
                strcpy(IR.opName, "STO");
                break;
            case 5:
                strcpy(IR.opName, "CAL");
                break;
            case 6:
                strcpy(IR.opName, "INC");
                break;
            case 7:
                strcpy(IR.opName, "JMP");
                break;
            case 8:
                strcpy(IR.opName, "JPC");
                break;
            case 9:
                if (IR.M == 1){
                    strcpy(IR.opName, "SOU");
                }
                if (IR.M == 2) {
                    strcpy(IR.opName, "SIN");
                }
                if (IR.M == 3) {
                    strcpy(IR.opName, "EOP");
                }
            break;  
        }
     
        
        // Execute Cycle
        if (IR.OP == 1) { 
            //LIT OPERATION
            SP--;
            pas[SP] = IR.M;
        }
        else if (IR.OP == 2) { 
            // RTN OPERATION
            if (IR.M == 0)
            {
                SP = BP + 1;
                BP = pas[SP - 2];
                PC = pas[SP - 3];
            }
            if (IR.M == 1)//ADD OP
            {
                pas[SP + 1] = pas[SP + 1] + pas[SP];
                SP++; 
            }
            if (IR.M == 2)//SUB OP
            {
                pas[SP + 1] = pas[SP + 1] - pas[SP];
                SP++;
            }
            if (IR.M == 3)//MUL OP
            {
                pas[SP + 1] = pas[SP + 1] * pas[SP];
                SP++;
            }
            if (IR.M == 4)//DIV OP
            {
                pas[SP + 1] = pas[SP + 1] / pas[SP];
                SP++;
            }
            if (IR.M == 5)//EQL OP
            {
                pas[SP + 1] = pas[SP + 1] == pas[SP];
                SP++;
            }
            if (IR.M == 6)//NEQ OP
            {
                pas[SP + 1] = pas[SP + 1] != pas[SP];
                SP++;
            }
            if (IR.M == 7)//LSS OP
            {
                pas[SP + 1] = pas[SP + 1] < pas[SP];
                SP++;
            }
            if (IR.M == 8)//LEQ OP
            {
                pas[SP + 1] = pas[SP + 1] <= pas[SP];
                SP++;
            }
            if (IR.M == 9)//GTR OP
            {
                pas[SP + 1] = pas[SP + 1] > pas[SP];
                SP++;
            }
            if (IR.M == 10)//GEQ OP
            {
                pas[SP + 1] = pas[SP + 1] >= pas[SP];
                SP++;
            }
            if (IR.M == 11)//ODD OP
            {
                pas[SP] = pas[SP] % 2;
            } 
        } 
        else if (IR.OP == 3) { 
            // LOD OPERATION
            SP--;
            pas[SP] = pas[base(BP,IR.L) - IR.M];
        }
        else if (IR.OP == 4) { 
            // STO OPERATOR
            pas[base(BP,IR.L) - IR.M] = pas[SP];
            SP++;
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
            }
            SP++;      
        }
        else if (IR.OP == 9) { 
            // SYS OPERATIONS
            if (IR.M == 1)
            {
                printf("Output result is: %d\n",pas[SP]);
                SP++;
            }

            if (IR.M == 2)
            {
                SP--;
                printf("Please Enter an Integer: ");
                int i =  0;
                scanf("%d",&i); 
                pas[SP] = i;
            }

            if (IR.M == 3)
            {
                flag = 0;
                printf("    %s   %-3d %-3d %-3d  %-3d  %-3d ",IR.opName,IR.L,IR.M,PC,BP,SP);
                for (int i = ARRAY_SIZE - 1; i >= SP; i--){
                    printf("  %d ",pas[i]);
                }
                printf("\n");
            }   
        }      
    }    
    return 0;
}
