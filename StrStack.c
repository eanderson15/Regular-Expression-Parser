
#include <stdio.h>
#include <stdlib.h>

#include "StrStack.h"

struct StackNode {
	StackNode next;
	Node data;
};

// returns a new node
StackNode newStackNode(Node data) {
	StackNode this = (StackNode) malloc(sizeof(struct StackNode));
	if (this == NULL) {
		return NULL;
	}
	this->data = data;
	this->next = NULL;
	return this;
}

// frees node and stack under node
void freeStackNode(StackNode this) {
	if (this->next != NULL) {
		freeStackNode(this->next);
		free(this->next);
	}
	free(this);
}

// returns string in data node
char* getDataStackNode(StackNode this) {
	return getDataNode(this->data);
}

// returns node from data node
Node getNodeStackNode(StackNode this) {
	return this->data;
}

struct StrStack {
	StackNode head;
};

// returns empty stack
StrStack newStrStack(void) {
	StrStack this = (StrStack) malloc(sizeof(struct StrStack));
	if (this == NULL) {
		return NULL;
	}
	this->head = NULL;
	return this;
}

// frees stack
void freeStrStack(StrStack this) {
	if (this->head != NULL) {
		freeStackNode(this->head);
	}
	free(this);
}

// inserts data onto top of stack
void pushStack(StrStack this, Node data) {
	if (this == NULL) {
		return;
	}
	if (this->head == NULL) {
		this->head = newStackNode(data);
	} else {
		StackNode newHead = newStackNode(data);
		newHead->next = this->head;
		this->head = newHead;
	}
}

// inserts node onto top of stack
void pushStackNode(StrStack this, StackNode n) {
	if (this == NULL) {
		return;
	}
	if (this->head == NULL) {
		this->head = n;
	} else {
		n->next = this->head;
		this->head = n;
	}
}

// pops head node from stack
StackNode popStackNode(StrStack this) {
	if (this == NULL) {
		return NULL;
	}
	if (this->head == NULL) {
		return NULL;
	} else {
		StackNode n = this->head;
		this->head = this->head->next;
		return n;
	}
}

// returns true if stack is empty
int isEmptyStrStack(StrStack this) {
	if(this == NULL) {
		return 1;
	}
	if (this->head == NULL) {
		return 1;
	} else {
		return 0;
	}
}
