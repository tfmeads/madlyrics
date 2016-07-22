#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utilities.h"
#include "lyrics_io.h"

void readLinesToStructure(structure *s, char *filename, int numLines){ //read lines from file into structure object

	FILE *fp;

	numLines = getNumLines(filename);

	fp = fopen(filename,"r");
	fprintf(stderr,"Now parsing '%s'\n",filename);

	char *inputLine = malloc(sizeof(char)*256);

	while(fgets(inputLine,512,fp) != NULL){
		char *temp = malloc(sizeof(char)*512);
		strcpy(temp,inputLine);
		addLine(s,newLine(temp));
	}

	fclose(fp);
}

void parseLines(structure *s, char *filename, int numLines){ //parses lines in structure object

	FILE *fp;
	char *inputLine = malloc(sizeof(char)*512);
	int currLine = 1;

	for(int i = 0;i<s->lineCount;i++){
		if(s->lines[i]->words[0] != '\n'){
			char *parsed = makeParseable(toLower(s->lines[i]->words));
			fprintf(stderr,"Parsing line %d of %d...\n",currLine,numLines);
			currLine++;
			
			system(parsed);

			fp = fopen("tmp/output.txt","r");
			char *temp = malloc(sizeof(char)*512);
			fgets(inputLine,512,fp);
			strcpy(temp,inputLine);

			s->lines[i]->pos = temp;
			fclose(fp);
		}
	}
}

void writeStructToFile(structure *s, char *filename, int numLines){ //writes structure to .txt file in madlyrics/structs/

	char *path = malloc(sizeof(char)*128);
	strcpy(path,"structs/");
	filename += 8; //removes first 8 chars from filename, which is always "corpora/"
	strcat(path,filename);

	FILE *outputFile = fopen(path,"w");

	char *str = malloc(sizeof(char)*128); //holds data for each word that will be printed to outfile

	for(int i = 0; i<s->lineCount;i++){
		strcpy(str,getPOS(s->lines[i]->pos)); //writes a line of POS info for each line in file
		fprintf(outputFile,"%s\n",str);
	}

	fprintf(stderr,"Saved structure to structs/%s.\n",filename);
	fclose(outputFile);
}
