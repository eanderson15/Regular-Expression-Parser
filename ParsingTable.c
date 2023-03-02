
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ParsingTable.h"
#include "Production.h"

struct ParsingTable {
	char** keys;
	Production* productions;
	int** table;
	StrStack stack;
};

// creates a parsing table with information explicitly coded in
ParsingTable newParsingTable(void) {
	ParsingTable this = (ParsingTable) malloc(sizeof(struct ParsingTable));
	createKeysParsingTable(this);
	createProductionsParsingTable(this);
	createTableParsingTable(this);
	this->stack = newStrStack();
	return this;
}

// creates a list of the possible expressions explicitly
void createKeysParsingTable(ParsingTable this) {
	this->keys = (char**) calloc(8, sizeof(char*));
	this->keys[0] = "<E>";
	this->keys[1] = "<ET>";
	this->keys[2] = "<C>";
	this->keys[3] = "<CT>";
	this->keys[4] = "<S>";
	this->keys[5] = "<ST>";
	this->keys[6] = "<F>";
	this->keys[7] = "<L>";
}

// creates a list of possible productions explicitly
void createProductionsParsingTable(ParsingTable this) {
	this->productions = (Production*) calloc(38, sizeof(Production));
	// skips first index
	this->productions[1] = newProduction("<C><ET>");
	this->productions[2] = newProduction("|<E>");
	this->productions[3] = newProduction("<eps>");
	this->productions[4] = newProduction("<S><CT>");
	this->productions[5] = newProduction(".<C>");
	this->productions[6] = newProduction("<eps>");
	this->productions[7] = newProduction("<F><ST>");
	this->productions[8] = newProduction("*<ST>");
	this->productions[9] = newProduction("<eps>");
	this->productions[10] = newProduction("(<E>)");
	this->productions[11] = newProduction("<L>");
	for (int i = 0; i < 26; i++) {
		int c = i + 97;
		char* letter = (char*) calloc(2, sizeof(char));
		letter[0] = c;
		letter[1] = '\0';
		this->productions[i + 12] = newProduction(letter);
		free(letter);
	}
}

// creates the transition table explicitly
void createTableParsingTable(ParsingTable this) {
	this->table = (int**) calloc(8, sizeof(int*));
	for (int i = 0; i < 8; i++) {
		this->table[i] = (int*) calloc(128, sizeof(int));
	}
	for (int i = 0; i < 128; i++) {
		this->table[0][i] = 1;
		this->table[1][i] = 3;
		this->table[2][i] = 4;
		this->table[3][i] = 6;
		this->table[4][i] = 7;
		this->table[5][i] = 9;
		this->table[6][i] = 11;
	}
	this->table[1]['|'] = 2;
	this->table[3]['.'] = 5;
	this->table[5]['*'] = 8;
	this->table[6]['('] = 10;
	for (int i = 97; i < 123; i++) {
		this->table[7][i] = 12 + (i - 97);
	}
}

// frees the parsing table
void freeParsingTable(ParsingTable this) {
	for (int i = 0; i < 8; i++) {
		free(this->table[i]);
	}
	free(this->productions[0]);
	for (int i = 1; i < 38; i++) {
		freeProduction(this->productions[i]);
	}
	free(this->keys);
	free(this->table);
	free(this->productions);
	// only frees pointer to stack, nodes need already be freed because they get popped
	free(this->stack);
	free(this);
}

// finds the index of the matching expression
int findKeyParsingTable(ParsingTable this, char* key) {
	for (int i = 0; i < 8; i++) {
		if (!strcmp(this->keys[i], key)) {
			return i;
		}
	}
	return -1;
}

// checks if current input is space goes to next character
char* spaceParsingTable(char* input) {
	while (*input == ' ') {
		input++;
	}
	return input;
}

// pushes the children of a node onto the stack from right to left
void pushLeftSibling(StrStack stack, Node pushNode) {
	if (getRightSibling(pushNode) != NULL) {
		pushLeftSibling(stack, getRightSibling(pushNode));
	}
	pushStackNode(stack, newStackNode(pushNode));
}

// parses input into tree
// checks initial conditions
Tree parseParsingTable(ParsingTable this, char* input) {
	// checks if all input characters are within language
	int inputLength = (sizeof(*input)/sizeof(input[0]));
	for (int i = 0; i < inputLength; i++) {
		if (!((*input >= 97 && *input <=122) || (*input == 124) || (*input == 46) || (*input == 32) || (*input == 40) || (*input == 41) || (*input == 42))) {
			return NULL;
		}
	}
	return treeParsingTable(this, input);
}

// parses the input string into a tree using the parsing table
Tree treeParsingTable(ParsingTable this, char* input) {
	Tree tree = newTree();
	StackNode sNode = newStackNode(newNode("<E>"));
	// inserts initial node into tree
	insertRootTree(tree, getNodeStackNode(sNode));
	pushStackNode(this->stack, sNode);
	while (!isEmptyStrStack(this->stack)) {
		StackNode nStack = popStackNode(this->stack);
		Node nNode = getNodeStackNode(nStack);
		char* key = getDataStackNode(nStack);
		// if stack pop is an expression
		if (key[0] == '<') {
			// if stack pop is an epsilon then skip
			if (key[1] == 'e') {
				free(nStack);
				continue;
			} else {
				// get index for the proper expression
				int index = findKeyParsingTable(this, key);
				int next = 0;
				// skips any spaces
				input = spaceParsingTable(input);
				int inputIndex = *input;
				// gets production from table
				if (this->table[index][inputIndex] != 0) {
					next = this->table[index][inputIndex];
				} else {
					return NULL;
				}
				// inserts production strings into tree
				for (int i = 0; i < getFactorsProduction(this->productions[next]); i++) {
					char* copy = strCopy(getFactorProduction(this->productions[next], i));
					Node n = newNode(copy);
					free(copy);
					insertNode(nNode, n);
				}
				// pushes production strings onto stack in proper order
				pushLeftSibling(this->stack, getLeftChild(nNode));
			}
		// if terminal
		} else {
			// checks if match, if not return NULL
			for (int i = 0; i < strlen(key); i++) {
				if (key[i] == *input) {
					input++;
					// skips any spaces
					input = spaceParsingTable(input);
				} else {
					return NULL;
				}
			}
		}
		free(nStack);
	}
	// if not at end of input
	if (*input != '\0') return NULL;
	return tree;
}

// returns newly allocated copy of string
char* strCopy(char* input) {
	char* new = (char*) calloc(strlen(input) + 1, sizeof(char));
	for (int i = 0; i < strlen(input) + 1; i++) {
		new[i] = input[i];
	}
	return new;
}



