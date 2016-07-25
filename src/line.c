#include <stdio.h>
#include <stdlib.h>
#include "line.h"

line *newLine(char *s){ //holds info for every line in a song. Always exists within a structure object.

	line *l = (line *) malloc(sizeof(line));
	l->words = (char *) malloc(sizeof(char)*512); 
	l->words = s;
	l->pos = (char *) malloc(sizeof(char)*512);
	
	return l;
}

