/*
 * parsingTable.h
 *
 *  Created on: Oct 2, 2020
 *      Author: eric1
 */

#ifndef PARSINGTABLE_H_
#define PARSINGTABLE_H_

#include "Tree.h"
#include "StrStack.h"

typedef struct ParsingTable* ParsingTable;

extern ParsingTable newParsingTable(void);
extern void createKeysParsingTable(ParsingTable this);
extern void createProductionsParsingTable(ParsingTable this);
extern void createTableParsingTable(ParsingTable this);
extern void freeParsingTable(ParsingTable this);

extern int findKeyParsingTable(ParsingTable this, char* key);
extern char* spaceParsingTable(char* input);
extern void pushLeftSibling(StrStack stack, Node pushNode);

extern Tree parseParsingTable(ParsingTable this, char* input);
extern Tree treeParsingTable(ParsingTable this, char* input);

extern char* strCopy(char* input);

#endif /* PARSINGTABLE_H_ */
