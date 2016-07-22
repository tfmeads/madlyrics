#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utilities.h"


void readLinesToStructure(structure *s, char *filename){ //read lines from file into structure object

	FILE *fp;

	int numLines = getNumLines(filename);
	int currLine = 1;

	fp = fopen(filename,"r");
	fprintf(stderr,"Now parsing '%s'\n",filename);

	char *inputLine = malloc(sizeof(char)*256);

	while(fgets(inputLine,512,fp) != NULL){
		addLine(s,newLine(inputLine));
	}

	fclose(fp);
}
