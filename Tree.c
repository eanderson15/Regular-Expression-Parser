
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"

struct Node {
	char* data;
	Node leftChild;
	Node rightSibling;
};

// creates empty Node
Node newNode(char* data) {
	Node this = (Node) malloc(sizeof(struct Node));
	if (this == NULL) {
		return NULL;
	}
	// uniformly uses calloc for each node
	this->data = (char*) calloc(strlen(data) + 1, sizeof(char));
	for (int i = 0; i < strlen(data) + 1; i++) {
		this->data[i] = data[i];
	}
	this->leftChild = NULL;
	this->rightSibling = NULL;
	return this;
}

// frees subtree at Node
void freeNode(Node this) {
	if (this->rightSibling != NULL) {
		freeNode(this->rightSibling);
	}
	if (this->leftChild != NULL) {
		freeNode(this->leftChild);
	}
	free(this->data);
	free(this);
}

// frees the single node independently of its connections
void freeSingleNode(Node this) {
	free(this->data);
	free(this);
}

// returns string data
char* getDataNode(Node this) {
	return this->data;
}

// returns node of left child
Node getLeftChild(Node this) {
	return this->leftChild;
}

// returns node of right sibling
Node getRightSibling(Node this) {
	return this->rightSibling;
}

// inserts the add node as the rightmost child of this node
void insertNode(Node this, Node add) {
	if (this == NULL) {
		return;
	}
	if (this->leftChild == NULL) {
		this->leftChild = add;
	} else {
		if (this->leftChild->rightSibling == NULL) {
			this->leftChild->rightSibling = add;
		} else {
				insertRightNode(this->leftChild->rightSibling, add);
		}
	}
}

// recursive function for inserting node as rightmost child
void insertRightNode(Node this, Node add) {
	if (this == NULL) {
		return;
	}
	if (this->rightSibling != NULL) {
		insertRightNode(this->rightSibling, add);
	} else {
		this->rightSibling = add;
	}
}

struct Tree {
	Node root;
};

// creates empty Tree
Tree newTree(void) {
	Tree this = (Tree) malloc(sizeof(struct Tree));
	this->root = NULL;
	return this;
}

// frees Tree
void freeTree(Tree this) {
	freeNode(this->root);
	free(this);
}

// inserts root node into tree
// if root is not empty, makes old root the left child
void insertRootTree(Tree this, Node new) {
	if (this->root != NULL) {
		Node leftChild = this->root;
		if (new->leftChild != NULL) {
			Node rightSibling = new->leftChild;
			leftChild->rightSibling = rightSibling;
		}
		new->leftChild = leftChild;
		this->root = new;
	} else {
		this->root = new;
	}
}

// returns node with one child node
Node makeNode1(char* data, Node n1) {
	Node n = newNode(data);
	n->leftChild = n1;
	return n;
}

// returns node with two child nodes
Node makeNode2(char* data, Node n1, Node n2) {
	Node n = newNode(data);
	n->leftChild = n1;
	n1->rightSibling = n2;
	return n;
}

// returns node with three child nodes
Node makeNode3(char* data, Node n1, Node n2, Node n3) {
	Node n = newNode(data);
	n->leftChild = n1;
	n1->rightSibling = n2;
	n2->rightSibling = n3;
	return n;
}

// prints tree by printing root
void printTree(Tree this) {
	int indent = 0;
	printNode(this->root, indent);
}

// prints each subtree from node recursively in preorder
void printNode(Node this, int indent) {
	for (int i = 0; i < indent; i++) {
		printf("\t");
	}
	printf("%s\n", this->data);
	indent++;
	if (this->leftChild != NULL) {
		printNode(this->leftChild, indent);
	}
	indent--;
	if (this->rightSibling != NULL) {
		printNode(this->rightSibling, indent);
	}
}

// returns an expression tree from a parse tree
Tree parseToExpression(Tree this) {
	if (this == NULL) {
		return NULL;
	}
	if (this->root == NULL) {
		return NULL;
	}
	if (this->root->leftChild != NULL) {
		// calls recursive function on root
		this->root = nodeToExpression(this->root);
	}
	if (this->root != NULL) {
		// eliminates markers of parenthesized factor
		this->root = eliminateParenthesesExpression(this->root);
	}
	return this;
}

// recursive function that operates on each node of tree
// recursively eliminates nodes that aren't in an expresssion tree
Node nodeToExpression(Node this) {
	// call on left child
	if (this->leftChild != NULL) {
		this->leftChild = nodeToExpression(this->leftChild);
	}
	// call on right sibling
	if (this->rightSibling != NULL) {
		this->rightSibling = nodeToExpression(this->rightSibling);
	}
	// if terminal
	if (this->data[0] != '<') {
		// if left parentheses, keep as marker
		if (this->data[0] == '(') {
			this->leftChild =  this->rightSibling;
			this->rightSibling = NULL;
		// if right parentheses, then eliminate
		} else if (this->data[0] == ')') {
			freeSingleNode(this);
			this = NULL;
		}
	// if non terminal
	} else if (this->data[0] == '<') {
		// if epsilon then eliminate
		if (this->data[1] == 'e') {
			freeSingleNode(this);
			this = NULL;
		// if no connections implies no info connected, then eliminate
		} else if (this->leftChild == NULL) {
			freeSingleNode(this);
			this = NULL;
		// if only has left child
		} else if (this->leftChild->rightSibling == NULL) {
			// pointer to leftChild
			Node p2f = this->leftChild;
			// move data up to this
			free(this->data);
			this->data = this->leftChild->data;
			// move children up
			this->leftChild = this->leftChild->leftChild;
			// free the pointer to leftChild
			free(p2f);
		} else {
			// if right child is more precedent
			if (comparePrecedenceNode(this->leftChild, this->leftChild->rightSibling) < 0) {
				// pointer to right child
				Node p2f = this->leftChild->rightSibling;
				// move data up to this
				free(this->data);
				this->data = this->leftChild->rightSibling->data;
				// move children up
				this->leftChild->rightSibling = this->leftChild->rightSibling->leftChild;
				// free pointer to rightChild
				free(p2f);
			// if left child is more precedent
			} else {
				// saves right child
				Node r = this->leftChild->rightSibling;
				// same process as above
				Node p2f = this->leftChild;
				free(this->data);
				this->data = this->leftChild->data;
				if (this->leftChild->leftChild != NULL) {
					this->leftChild = this->leftChild->leftChild;
				} else {
					this->leftChild = NULL;
				}
				free(p2f);
				// insert right child at end
				insertNode(this, r);
			}
		}
	}
	return this;
}

// returns -1 if right more precedent, 0 if same, 1 if left
// order of precedence (highest to lowest): |, ., *, letter
int comparePrecedenceNode(Node left, Node right) {
	char lr[2] = {left->data[0], right->data[0]};
	int lrPrec[2] = {0, 0};
	// assigns precedence number in array
	for (int i = 0; i < 2; i++) {
		if ((97 <= lr[i]) && (lr[i] <= 122)) {
			lrPrec[i] = 0;
		} else if (lr[i] == 42) {
			lrPrec[i] = 1;
		} else if (lr[i] == 46) {
			lrPrec[i] = 2;
		} else if (lr[i] == 124){
			lrPrec[i] = 3;
		}
	}
	// compares and returns appropriately
	if (lrPrec[0] < lrPrec[1]) {
		return -1;
	} else if (lrPrec[0] > lrPrec[1]) {
		return 1;
	} else {
		return 0;
	}
}

// recursive function to eliminate '(' node that marks a parenthesized expression below
Node eliminateParenthesesExpression(Node this) {
	// calls on left
	if (this->leftChild != NULL) {
		this->leftChild = eliminateParenthesesExpression(this->leftChild);
	}
	// calls on right
	if (this->rightSibling != NULL) {
		this->rightSibling = eliminateParenthesesExpression(this->rightSibling);
	}
	// if finds parentheses, eliminate
	if (this->data[0] == '(') {
		Node p2f = this->leftChild;
		free(this->data);
		this->data = this->leftChild->data;
		if (this->leftChild->rightSibling != NULL) {
			this->rightSibling = this->leftChild->rightSibling;
		}
		if (this->leftChild->leftChild != NULL) {
			this->leftChild = this->leftChild->leftChild;
		} else {
			this->leftChild = NULL;
		}
		free(p2f);
	}
	return this;
}

// prints tree by printing root
void printExpressionTree(Tree this) {
	printExpressionNode(this->root);
}

// prints each subtree from node recursively in preorder
void printExpressionNode(Node this) {
	// variables to help adjust when to print close parentheses
	int printClose = 0;
	int closure = 0;
	if (this->data[0] >= 97 && this->data[0] <= 122) {
		printf("%s%s%s", " (LETTER ", this->data, ") ");
	} else {
		printf("(");
		if (this->data[0] == 42) {
			printf("%s", "CLOSURE");
			closure = 1;
		} else if (this->data[0] == 46) {
			printf("%s", "CONCAT");
			printClose = 1;
		} else if (this->data[0] == 124) {
			printf("%s", "UNION");
			printClose = 1;
		}
	}
	if (this->leftChild != NULL) {
		printExpressionNode(this->leftChild);
		if (closure) {
			printf(")");
		}
	}
	if (printClose) {
		printf(")");
	}
	if (this->rightSibling != NULL) {
		printExpressionNode(this->rightSibling);
	}
}

