/*
Program: Project 2 for CS211
Name: Clark Chen
NetID: schen237
Class: CS211
*/

#include <stdio.h>
#include <stdlib.h>

// Define boolean value
#define TRUE 1
#define FALSE 0

// Global Variable
int debugMode = FALSE; // Default debugMode == FALSE

// struct for char data
typedef struct StackStruct
{
	char* data;	//Data Array
	int size;	//current allocated space
	int used;	//Number of space used
} Stack;

////////////////////////////////////////////////////////////////
// Determine if this program is under debug Mode or not
void detectDebugMode(int argc, char** argv)
{
	int i;
	for (i = 0; i < argc; i++){
		if ('-' == argv[i][0] && 'd' == argv[i][1]){
			debugMode = TRUE;
		}
	}
}

////////////////////////////////////////////////////////////////
// Init action to allocate space for the char* pointer in Stack
void init (Stack* p)
{
	p->size = 5;
	p->data = (char*) malloc (sizeof(char) * p->size);
	p->used = 0;
}

////////////////////////////////////////////////////////////////
// To grow the char* memory space by 2 char from the previous
// value
void grow (Stack* p)
{
	int i = 0;
	char* tempChar;
	tempChar = (char*) malloc (sizeof(char) * p->size+2);
	for (i = 0; i < p->used; i++)
	{
		tempChar[i] = p->data[i];
	}
	free (p->data);
	p->data = tempChar;
	p->size += 2;

}

////////////////////////////////////////////////////////////////
// To push a new data into the char*, grow memory space if the
// space is running out
void push (Stack* p, char value)
{
	if (p->size == p->used){
		grow(p);
	}
	
	p->data[p->used] = value;
	p->used = p->used + 1;
}

////////////////////////////////////////////////////////////////
// To pop the last data enter into the char* by -1 on the 
// current usage
void pop (Stack* p)
{
	if (p->used != 0){
		p->used = p->used - 1;
	}else{
		printf("There are nothing to be pop!!");
	}
}

////////////////////////////////////////////////////////////////
// lookup what is the last data added to the char*
char top (Stack* p){
	if (p->used != 0){
		return p->data[p->used-1];
	}
	else{
		return '?';
	}
}

////////////////////////////////////////////////////////////////
// Clear data by reset the usage to 0
void clearData (Stack* p){
	p->used = 0;
}

////////////////////////////////////////////////////////////////
// Print out current value stored in the char* (For Debug Use)
void printData (Stack* p){
	int i;
	printf("StackData: ");
	for (i = 0; i < p->used; i++){
		printf("%c ", p->data[i]);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////
// Check if the stack in empty or not
int isEmpty(Stack* p){
	if (p->used == 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

////////////////////////////////////////////////////////////////
// Check if the input value in a open symbol
int isOpenSymbol(char value){
	char symbols[4] = { '(', '{', '[', '<' };
	int i;
	int returnVal = FALSE;
	for (i = 0; i < 4; i++){
		if (symbols[i] == value){
			returnVal = TRUE;
			break;
		}
	}
	return returnVal;
}

////////////////////////////////////////////////////////////////
// Check if the input value in a close symbol
int isCloseSymbol(char value){
	char symbols[4] = { ')', '}', ']', '>' };int i;
        int returnVal = FALSE;
        for (i = 0; i < 4; i++){
                if (symbols[i] == value){
                        returnVal = TRUE;
                        break;
                }
        }
        return returnVal;
}

////////////////////////////////////////////////////////////////
// Check if the input value is a valid symbol
int isSymbol(char value){
        char symbols[8] = { '(', '{', '[', '<', ')', '}', ']', '>' };
        int i;
        int returnVal = FALSE;
        for (i = 0; i < 8; i++){
                if (symbols[i] == value){
                        returnVal = TRUE;
                        break;
                }
        }
        return returnVal;
}

////////////////////////////////////////////////////////////////
// Check if two input symbol match with each other.
int isSymbolMatch(char value1, char value2){
        char symbols[8] = { '(', '{', '[', '<', ')', '}', ']', '>' };
	int i;
        int returnVal = FALSE;
	if (isSymbol(value1) == FALSE || isSymbol(value2) == FALSE){
		return FALSE;
	}
        for (i = 0; i < 4; i++){
                if ((symbols[i] == value1 && symbols[i+4] == value2) || 
		(symbols[i] == value2 && symbols[i+4] == value1)){
                        returnVal = TRUE;
                        break;
                }
        }
        return returnVal;
}

////////////////////////////////////////////////////////////////
// Convert the open symbol to its close symbol
char convertOpenToClose(char value){
	char symbols[8] = { '(', '{', '[', '<', ')', '}', ']', '>' };
	int i;
	for (i = 0; i < 4; i++){
                if (symbols[i] == value){
			return symbols[i+4];
                        break;
                }
        }
}

////////////////////////////////////////////////////////////////
// Convert the close symbol to its open symbol
char convertCloseToOpen(char value){
        char symbols[8] = { '(', '{', '[', '<', ')', '}', ']', '>' };
        int i;
        for (i = 4; i < 8; i++){
                if (symbols[i] == value){
                        return symbols[i-4];
                        break;
                }
        }
}

////////////////////////////////////////////////////////////////
// Print the custom amount of space out
void spaceGenerator(int count){
	int i = 0;
	for (i = 0; i < count; i++){
		printf(" ");
	}
}

////////////////////////////////////////////////////////////////
// Check for quit userinput
int isQuit(char userInput[], int maxNumOfChar){
	int i;
	int qExist = FALSE;
	int notQExist = FALSE;
	for (i = 0; i < maxNumOfChar; i++){
		if (userInput[i] == '\0'){
			break;
		}
		if (userInput[i] == 'q' || userInput[i] == 'Q'){
			qExist = TRUE;
		}else if (isSymbol(userInput[i]))
		{
			notQExist = TRUE;
			break;
		}
	}
	if (debugMode == TRUE){
		printf("Debug-isQuit Func:\n");
		printf("qExist: %d\n", qExist);
		printf("notQExist: %d\n", notQExist);
	}
	if (qExist == TRUE && notQExist == FALSE){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void printArray(char userInput[], int maxNumOfChar){
	int i;
	printf("Input Debug Info: ");
	for (i = 0; i < maxNumOfChar; i++){
		if (userInput[i] == '\0'){
			break;
		}
		printf("[%d] = %c\n", i, userInput[i]);
	}
}

int main(int argc, char** argv){

	int maxNumOfChar = 302; // Max num of input char
	detectDebugMode(argc, argv); // Detect if the program should be in Debug Mode
	char userInput[maxNumOfChar]; // userInput variable
	Stack* inputStack = (Stack*) malloc(sizeof(Stack)); // allocate space for input Stack
	init (inputStack); //allocate space for the char* variable in inputStack
	int i = 0; // Loop Counter
	int toQuit = FALSE; // whether the program should quit
	int isBalanced;	// whether the current userInput is balanced


	while (toQuit == FALSE){
		isBalanced = TRUE; //Default TRUE if no problem found
		fgets (userInput, maxNumOfChar, stdin); // Read in userInput
		// Input Debug Output
		if (debugMode == TRUE){
			printArray(userInput, maxNumOfChar);
		}

		// Check if this line is quit message
		if (isQuit(userInput, maxNumOfChar) == TRUE){
			toQuit = TRUE;
			break;
		}
		for (i = 0; i < maxNumOfChar; i++){
			// Debug Output
			if (debugMode == TRUE){
				printf("\nDebug Info:\nuserInput[%d]: %c\n", i, userInput[i]);
				printf("isBalanced: %d\n", isBalanced);
				printData(inputStack);
			}
			// Check if it's the end of the char*
			if (userInput[i] == '\0'){
				break;
			}

			// Determine if the char is the symbol we are checking
			if(isSymbol(userInput[i]) == TRUE){
				// Debug Output
				if (debugMode == TRUE){
					printf("isSymbol: %d\n", isSymbol(userInput[i]));
				}
	
				
				if (isOpenSymbol(userInput[i]) == TRUE){
					// Debug Output
					if (debugMode == TRUE){
						printf("Push: %c\n", userInput[i]);
					}
					
					// Store value into Stack if is an open Symbol
					push(inputStack, userInput[i]);
				}
				else if (isSymbolMatch(top(inputStack), userInput[i]) == TRUE){
					// Debug Output
					if (debugMode == TRUE){
                                                printf("Pop: %c\n", userInput[i]);
                                        }
					// If userInput is close symbol, and match with the last added value
					pop(inputStack);
				}
				else {
					// Some problem with the new input
					spaceGenerator(i); // To indicate the error position
					// Show the expect symbol for error
                                        if (isOpenSymbol(top(inputStack)) == TRUE){
                                                printf("^ expecting %c\n\n", convertOpenToClose(top(inputStack)));
                                        }

					// Error is missing symbol
					else {
						printf("^ missing %c\n\n", convertCloseToOpen(userInput[i]));
					}

					isBalanced = FALSE; // If any problem occur, the expression is not balance
					break;
				}
			}
		}
		// Final Check
		// Debug Output
		if (debugMode == TRUE){
                	printf("\nFinal Debug Info:\nuserInput[%d]: %c\n", i, userInput[i]);
                	printf("isBalanced: %d\n", isBalanced);
			printf("top(inputStack): %c\n", top(inputStack));
			printf("isEmpty(inputStack): %d\n", isEmpty(inputStack));
			printf("isOpenSymbol(top(inputStack)): %d\n", isOpenSymbol(top(inputStack)));
			printf("toQuit: %d\n", toQuit);
                	printData(inputStack);
        	}

		// If everything match, no remain unmatch value left in the stack
		// then the expression is balanced
		if (isBalanced == TRUE && isEmpty(inputStack) == TRUE){
			printf("Expression is balanced\n\n");
		}
		// Implementation for missing symbol at the end, by checking
		// if the inputStack is not empty
		else if (isBalanced == TRUE){
			spaceGenerator(i);
			printf("^ missing %c\n\n", convertOpenToClose(top(inputStack)));
		}
		clearData(inputStack); // Clear stack data before the next expression read
	}

	return 0;
}
