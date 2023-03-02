
#include <stdio.h>
#include <stdlib.h>

#include "parsingFunctions.h"

// input through entire file
char* input;

// checks if current input matches the character
int lookahead(char match) {
	return *input == match;
}

// checks if current input is space goes to next character
void spaceParsingFunctions(void) {
	while (*input == ' ') {
		input++;
	}
}

// parses input into a tree using parsing functions
// checks conditions
Tree parseParsingFunctions(char* inp) {
	input = inp;
	// checks if all characters are within language
	int inputLength = (sizeof(*input)/sizeof(input[0]));
	for (int i = 0; i < inputLength; i++) {
		if (!((*input >= 97 && *input <=122) || (*input == 124) || (*input == 46) || (*input == 32) || (*input == 40) || (*input == 41) || (*input == 42))) {
			return NULL;
		}
	}
	// if input is at space, move to next character
	spaceParsingFunctions();
	// starts parsing with E
	Node root = E();
	// if node is null, or input is not at end
	if (root == NULL) return NULL;
	if (*(input + 1) != '\0') {
		freeNode(root);
		return NULL;
	}
	// insert node into tree
	Tree tree = newTree();
	insertRootTree(tree, root);
	return tree;
}

// parsing function for <E> -> <C><ET>
Node E(void) {
	Node cNode = C();
	if (cNode == NULL) return NULL;
	input++;
	spaceParsingFunctions();
	Node etNode = ET();
	if (etNode == NULL) {
		freeNode(cNode);
		return NULL;
	}
	return makeNode2("<E>", cNode, etNode);
}

// parsing fucntion for <ET> -> |<E> or eps
Node ET(void) {
	if (lookahead('|')) {
		input++;
		spaceParsingFunctions();
		Node eNode = E();
		if (eNode == NULL) return NULL;
		return makeNode2("<ET>", newNode("|"), eNode);
	} else {
		input--;
		return makeNode1("<ET>", newNode("<eps>"));
	}
}

// parsing function for <C> -> <S><CT>
Node C(void) {
	Node sNode = S();
	if (sNode == NULL) return NULL;
	input++;
	spaceParsingFunctions();
	Node ctNode = CT();
	if (ctNode == NULL) {
		freeNode(sNode);
		return NULL;
	}
	return makeNode2("<C>", sNode, ctNode);
}

// parsing function for <CT> -> .<C> or eps
Node CT(void) {
	if (lookahead('.')) {
		input++;
		spaceParsingFunctions();
		Node cNode = C();
		if (cNode == NULL) return NULL;
		return makeNode2("<CT>", newNode("."), cNode);
	} else {
		input--;
		return makeNode1("<CT>", newNode("<eps>"));
	}
}

// parsing function for <S> -> <F><ST>
Node S(void) {
	Node fNode = F();
	if (fNode == NULL) return NULL;
	input++;
	spaceParsingFunctions();
	Node stNode = ST();
	if (stNode == NULL) {
		freeNode(fNode);
		return NULL;
	}
	return makeNode2("<S>", fNode, stNode);
}

// parsing function for <ST> -> *<ST> or eps
Node ST(void) {
	if (lookahead('*')) {
		input++;
		spaceParsingFunctions();
		Node stNode = ST();
		if (stNode == NULL) return NULL;
		return makeNode2("<ST>", newNode("*"), stNode);
	} else {
		input--;
		return makeNode1("<ST>", newNode("<eps>"));
	}
}

// parsing function for (<E>) or <L>
Node F(void) {
	if (lookahead('(')) {
		input++;
		spaceParsingFunctions();
		Node eNode = E();
		if (eNode == NULL) return NULL;
		input++;
		spaceParsingFunctions();
		if (!lookahead(')')) {
			freeNode(eNode);
			return NULL;
		}
		return makeNode3("<F>", newNode("("), eNode, newNode(")"));
	} else if (lookahead(')')) {
		return NULL;
	} else {
		Node lNode = L();
		if (lNode == NULL) return NULL;
		return makeNode1("<F>", lNode);
	}
}

// parsing function for <L> -> lowercase letters
Node L(void) {
	char l[] = {*input, '\0'};
	if (!(l[0] >= 97 && l[0] <= 122)) return NULL;
	Node lNode = newNode(l);
	return makeNode1("<L>", lNode);
}


