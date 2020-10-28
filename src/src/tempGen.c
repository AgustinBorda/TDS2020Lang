#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../headers/tempGen.h"

int var = 0;


int intLength(int n) {
	int count = 1;
	if(n<0) {
		count++;
	}
	while(n/10!=0) {
		n = n/10;
		count++;
	}
	return count;
}

char* genTemp() {
	char* res = malloc(sizeof(char)*(5+intLength(var)));
	*res = '\0';
	sprintf(res,"t%d",var);
	var++;
	return res;	
}
