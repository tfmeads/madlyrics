#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structure.h"
#include "utilities.h"
#include "lyrics_io.h"

//Contains functions pertaining to file i/o


void readLinesToStructure(structure *s, char *filename, int numLines){ //reads untagged lines from file into structure object

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

void parseLines(structure *s, char *filename, int numLines){ //tags untagged lines in structure object by feeding them into Parsey McParseFace

	FILE *fp;
	char *inputLine = malloc(sizeof(char)*512);
	int currLine = 1;

	for(int i = 0;i<s->lineCount;i++){
		if(s->lines[i]->words[0] != '\n'){
			char *parsed = makeParseable(toLower(s->lines[i]->words));
			fprintf(stderr,"Parsing line %d of %d...\n",currLine,numLines);
			currLine++;
			
			system(parsed);

			fp = fopen("tmp/output.txt","r"); //if you change the location or name in this file, make sure to also change the corresponding
			char *temp = malloc(sizeof(char)*512); //entry in models/syntaxnet/syntaxnet/models/parsey_mcparseface/context.pbtxt
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

void updatePosLists(structure *s){ //checks if each word/POS combination is present in POS lists found in madlyrics/lists, updates corresponding list
				   // if not present.

	char *path = malloc(sizeof(char)*128);
	char **wordsArr = malloc(sizeof(char *)*64);
	char *word = malloc(sizeof(char )*256);

	FILE *dest;
	int i = 0;
	int newEntries = 0;

	while(s->lines[i] != NULL){
		
		wordsArr = strToArr(removeUnderscores(s->lines[i]->pos)); // evenly sized array with format (word) (pos)
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
		i++;
	}

	if(newEntries > 0){
		fprintf(stderr,"Updated POS Lists with %i new terms.\n",newEntries);
	}
	else{
		fprintf(stderr,"No new terms were added to POS lists.\n");
	}
}

void findRhymeScheme(structure *s, char *filename){
	
	char **currentLine = malloc(sizeof(char *)*64);
	char **wordsArr = malloc(sizeof(char *)*128);

	int size = 0;
	int capacity = 128;

	int i = 0;

	while(s-> lines[i] != NULL){

		currentLine = strToArr(removeUnderscores(s->lines[i]->pos));
		
		int j = 0;

		while(currentLine[j] != NULL){
			if(!isInCharArr(wordsArr,currentLine[j],size) && !ispunct(currentLine[j][strlen(currentLine[j])-1])){
				wordsArr[size] = malloc(sizeof(char)*128);
				strcpy(wordsArr[size],currentLine[j]);
				size++;
			}
			if(size == capacity){
				wordsArr = realloc(wordsArr,sizeof(char *)*(capacity *2));
				capacity *= 2;
			}
			
			j += 2;
		}
		i++;
	}
	

	char **rhymeArr = malloc(sizeof(char *)* size);

	int k = 0;

	while(wordsArr[k] != NULL){
		rhymeArr[k] = malloc(sizeof(char)*256);
		strcpy(rhymeArr[k],getRhymeId(wordsArr[k]));
		fprintf(stderr,"%s %s\n",wordsArr[k],rhymeArr[k]);
		k++;
	} 
}
	


char *getRhymeId(char *str){ //gets rhyme ID from madlyrics/dicts/editedRhymeDict.csv that corresponds to given word

	FILE *fp = fopen("dicts/editedRhymeDict.csv","r");

	char **results = malloc(sizeof(char *)*32);
	int size = 0;
	char *temp = malloc(sizeof(char)*256);
	char *curr = malloc(sizeof(char)*256);

	while(fgets(temp, 128,fp) != NULL){
		if(strstr(temp,toUpper(str)) != NULL){ // if match is found
			strcpy(curr,getWordFromDictEntry(temp));
			if(strcmp(toUpper(str),curr) == 0){ //if word entry matches str exactly
				results[size] = malloc(sizeof(char)*256);
				strcpy(results[size],getRhymeIdFromDictEntry(temp));
				size++;
			}
		}
	}

	fclose(fp);
	
	//printCharArr(results);
	if(results[0] != NULL){
		return results[rand() % (sizeof(results) / sizeof(results[0]))]; //returns random entry in array
	}
	else{
		return "?";
	}

}	
