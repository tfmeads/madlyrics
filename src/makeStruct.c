#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utilities.h"
#include "lyrics_io.h"

int main(int argc,char **argv){
	
	//generate song structure file

	structure *s = newStructure();
	int numLines = getNumLines(argv[1]);

	readLinesToStructure(s,argv[1],numLines);

	parseLines(s,argv[1],numLines);

	writeStructToFile(s,argv[1],numLines);
	
	char * path = malloc(sizeof(char)*128);
	char **wordsArr = malloc(sizeof(char *)*64);
	char *word = malloc(sizeof(char *)*256);

	FILE *dest;
	int k = 0;
	int newEntries = 0;

	while(s->lines[k] != NULL){
		wordsArr = strToArr(removeUnderscores(s->lines[k]->pos)); //evenly sized array with format (word) (pos)
		int l = 0;
		while(wordsArr[l] != NULL){
			strcpy(word,wordsArr[l]);
			if(isAlnum(word)){	
			strcpy(path,"lists/"); 
			strcat(path,cleanStr(wordsArr[l+1]));
			strcat(path,".txt");
			if(!isInFile(word,path)){
				dest = fopen(path,"a");
				fprintf(dest,"%s\n",word);
				fclose(dest);
				newEntries++;
			}
			}
			l+=2;
		}
		k++;
	}

	if(newEntries > 0){	
	fprintf(stderr,"Updated POS Lists with %i new terms.\n",newEntries);	
	}
	else{
	fprintf(stderr,"No new terms were added to POS Lists.\n");
	}




	return 0; 
}

