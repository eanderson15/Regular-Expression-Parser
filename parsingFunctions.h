
#ifndef PARSINGFUNCTIONS_H_
#define PARSINGFUNCTIONS_H_

#include "Tree.h"

extern int lookahead(char match);
extern void spaceParsingFunctions(void);

extern Tree parseParsingFunctions(char* data);

extern Node E(void);
extern Node ET(void);
extern Node C(void);
extern Node CT(void);
extern Node S(void);
extern Node ST(void);
extern Node F(void);
extern Node L(void);

#endif /* PARSINGFUNCTIONS_H_ */
