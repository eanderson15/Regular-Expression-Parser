
#include <stdio.h>
#include <stdlib.h>

#include "rexp.h"

int main(int argc, char* argv[]) {
	setbuf(stdout, NULL);
	REPL();
}

// loop for input
void REPL(void) {
	char input[100];
	printf("%s\n", "Enter an input (\"quit\" to quit): ");
	// allows for spaces in input
	scanf("%[^\n]%*c", input);
	while (!stringIsQuit(input)) {
		printf("%s\n", "Printing parse tree for regexp input using parsing functions.");
		Tree t1 = parseParsingFunctions(input);
		if (t1 == NULL) {
			printf("%s\n", "Invalid input");
			printf("%s\n", "Enter an input (\"quit\" to quit): ");
			scanf("%[^\n]%*c", input);
			continue;
		} else {
			printTree(t1);
		}
		printf("%s\n", "Printing parse tree for regexp input using a parsing table.");
		ParsingTable table = newParsingTable();
		Tree t2 = parseParsingTable(table, input);
		if (t2 == NULL) {
			printf("%s\n", "Invalid input");
			printf("%s\n", "Enter an input (\"quit\" to quit): ");
			scanf("%[^\n]%*c", input);
			continue;
		} else {
			printTree(t2);
		}
		printf("%s\n", "Printing expression tree for regexp input and the accompanying set of nested expressions.");
		Tree t3 = parseToExpression(t2);
		printTree(t3);
		printExpressionTree(t3);
		printf("%s", "\n");
		freeTree(t1);
		freeTree(t2);
		// don't need to free t3 because t2 is t3
		freeParsingTable(table);
		printf("%s\n", "Enter an input (\"quit\" to quit): ");
		scanf("%[^\n]%*c", input);
	}
}

// checks if string is quit
int stringIsQuit(char* s) {
	char* quit = "quit";
	if (sizeof(quit) != sizeof(s)) return 0;
	for (int i = 0; i < sizeof(s); i++) {
		if (s[i] != quit[i]) return 0;
	}
	return 1;
}

