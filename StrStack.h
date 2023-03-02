/*
 * StrStack.h
 *
 *  Created on: Oct 2, 2020
 *      Author: eric1
 */

#ifndef STRSTACK_H_
#define STRSTACK_H_

#include "Tree.h"

typedef struct StackNode* StackNode;

extern StackNode newStackNode(Node data);
extern void freeStackNode(StackNode this);
extern char* getDataStackNode(StackNode this);
extern Node getNodeStackNode(StackNode this);

typedef struct StrStack* StrStack;

extern StrStack newStrStack(void);
extern void freeStrStack(StrStack this);

extern void pushStack(StrStack this, Node data);
extern void pushStackNode(StrStack this, StackNode n);
extern StackNode popStackNode(StrStack this);
extern int isEmptyStrStack(StrStack this);

#endif /* STRSTACK_H_ */
