/*
 * rexp.h
 *
 *  Created on: Oct 11, 2020
 *      Author: eric1
 */

#ifndef REXP_H_
#define REXP_H_

#include "parsingFunctions.h"
#include "StrStack.h"
#include "ParsingTable.h"

extern void REPL(void);
extern int stringIsQuit(char* s);

#endif /* REXP_H_ */
