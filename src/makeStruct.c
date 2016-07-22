#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "utilities.h"


int main(int argc,char **argv){
	
	//generate song structure file

	structure *s = newStructure();

	FILE *fp;
	
	int numLines = getNumLines(argv[1]);
	int currLine = 1;

	fp = fopen(argv[1],"r");
	fprintf(stderr,"Now parsing '%s'\n",argv[1]);

	char *inputLine = malloc(sizeof(char)*512) ;

	while(fgets(inputLine,512,fp) != NULL){
		char *temp = malloc(sizeof(char)*512);
		strcpy(temp,inputLine);
		addLine(s,newLine(temp));
	}
		
	fclose(fp);
	
	for(int i = 0;i<s->lineCount;i++){
		if(s->lines[i]->words[0] != '\n'){
		char * parsed = makeParseable(toLower(s->lines[i]->words));
		fprintf(stderr,"Parsing line %d of %d...\n",currLine,numLines);
		currLine++;
		system(parsed);

		fp = fopen("tmp/output.txt","r");
		fgets(inputLine,512,fp);
		char *temp = malloc(sizeof(char)*512);
		strcpy(temp,inputLine);

		s->lines[i]->pos = temp;
		fclose(fp);
		}
	}

	
	

	char *path = malloc(sizeof(char)*128);
	strcpy(path,"structs/");
	argv[1] += 8; // removes first 8 chars from path, which is always "corpora/"
	strcat(path,argv[1]);

	FILE *outputFile = fopen(path,"w");
	
	char *str = malloc(sizeof(char)*128); //holds data for each word that will be printed to outfile

	for(int j = 0; j<s->lineCount;j++){
		strcpy(str,getPOS(s->lines[j]->pos)); //writes a line of POS info for each line in file
		fprintf(outputFile,"%s\n",str);
	}
	fprintf(stderr,"Saved structure to structs/%s.\n",argv[1]);
	fclose(outputFile);

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

