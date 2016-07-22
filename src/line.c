#include <stdio.h>
#include <stdlib.h>
#include "line.h"

line *newLine(char *s){

	line *l = (line *) malloc(sizeof(line));
	l->words = (char *) malloc(sizeof(char)*512); 
	l->words = s;
	l->wordCount = 0;
	l->pos = (char *) malloc(sizeof(char)*512);
	
	return l;
}

