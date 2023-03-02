
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Production.h"

struct Production {
	char** prod;
	int factors;
};

Production newProduction(char* input) {
	Production this = (Production) malloc(sizeof(struct Production));
	// count of number of factors in production
	this->factors = countFactorsProduction(input);
	this->prod = (char**) calloc(this->factors, sizeof(char*));
	int factorIndex = 0;
	for (int i = 0; i < strlen(input); i++) {
		// if terminal
		if (input[i] != '<') {
			// allocates space for one letter string
			this->prod[factorIndex] = (char*) calloc(2, sizeof(char));
			this->prod[factorIndex][0] = input[i];
			this->prod[factorIndex][1] = '\0';
			factorIndex++;
		// if non terminal
		} else {
			// finds index of end of factor
			int j = i;
			while (input[j] != '>') {
				j++;
			}
			// allocates difference between current input index and end of factor
			this->prod[factorIndex] = (char*) calloc(j - i + 2, sizeof(char));
			int k = 0;
			// until end of factor
			for (; i <= j; i++, k++) {
				this->prod[factorIndex][k] = input[i];
			}
			this->prod[factorIndex][k] = '\0';
			i--;
			factorIndex++;
		}
	}
	return this;
}

// returns count of the number of factors in the production
int countFactorsProduction(char* input) {
	int factor = 0;
	for (int i = 0; i < strlen(input); i++) {
		// if terminal add one
		if (input[i] != '<') {
			factor++;
		// if terminal
		} else {
			// add one and go to end of factor
			factor++;
			while (input[i] != '>') {
				i++;
			}
		}
	}
	return factor;
}

// frees the production
void freeProduction(Production this) {
	for (int i = 0; i < this->factors; i++) {
		free(this->prod[i]);
	}
	free(this->prod);
	free(this);
}

// returns the string factor in the production at the given index
char* getFactorProduction(Production this, int index) {
	return this->prod[index];
}

// returns the number of factors
int getFactorsProduction(Production this) {
	return this->factors;
}
