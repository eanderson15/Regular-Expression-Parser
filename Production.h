/*
 * Production.h
 *
 *  Created on: Oct 8, 2020
 *      Author: eric1
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

typedef struct Production* Production;

extern Production newProduction(char* input);
extern int countFactorsProduction(char* input);
extern void freeProduction(Production this);

extern char* getFactorProduction(Production this, int index);
extern int getFactorsProduction(Production this);

#endif /* PRODUCTION_H_ */
